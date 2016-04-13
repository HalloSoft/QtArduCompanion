#include "fdevice.h"


#include <QDebug>

#include "util.h"


using namespace qfirmata;

FDevice::FDevice(QString serialPortName, int baudrate)
{
    _deviceName = "QfDevice";

    _bufferToParse = (quint8*) malloc(4096);

    if (serialPortName.isEmpty())
    {
        QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
        serialPortName = list.value(0).portName();
    }

    _serialPort = new QSerialPort(); // Cleanup????
    Q_CHECK_PTR(_serialPort);

    _serialPort->setBaudRate(baudrate);
    _serialPort->setPort(QSerialPortInfo(serialPortName));

    bool isConnected = false;                                                               Q_UNUSED(isConnected);
    isConnected = connect(_serialPort, SIGNAL(readyRead()),   this, SLOT(processSerial())); Q_ASSERT(isConnected);
    isConnected = connect(this,        SIGNAL(deviceReady()), this, SLOT(initialize()));    Q_ASSERT(isConnected);
    isConnected = connect(_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SIGNAL(error(QSerialPort::SerialPortError)));
    Q_ASSERT(isConnected);

}

bool FDevice::connectDevice(QString portName)
{
    if(!portName.isEmpty())
        _serialPort->setPortName(portName);

    _connected = _serialPort->open(QIODevice::ReadWrite);

    if (_connected)
        emit messageFired(_deviceName, QString("Com-Port: %1").arg(_serialPort->portName()));
    else
        emit messageFired(_deviceName, "Device not connected!");

    emit connectionStatusChanged();

    return _connected;
}

void FDevice::disconnectDevice()
{
    _serialPort->close();
    _connected = false;
    _ready = false;

    emit connectionStatusChanged();
}

void FDevice::initialize()
{
    requestCapabilities();
    reportPins();
}

void FDevice::reportFirmware()
{
    QByteArray sendCommand;
    sendCommand.append(COMMAND_START_SYSEX);
    sendCommand.append(COMMAND_REPORT_FIRMWARE);
    sendCommand.append(COMMAND_END_SYSEX);

    _serialPort->write(sendCommand);
    _serialPort->flush();
}

// This informs if a pin can be analog, digital in/out, servo or what (I think);
void FDevice::requestCapabilities()
{
    QByteArray sendCommand;
    sendCommand.append(COMMAND_START_SYSEX);
    sendCommand.append(COMMAND_ANALOG_MAPPING_QUERY); // read analog to pin # info
    sendCommand.append(COMMAND_END_SYSEX);
    sendCommand.append(COMMAND_START_SYSEX);
    sendCommand.append(COMMAND_CAPABILITY_QUERY); // read capabilities
    sendCommand.append(COMMAND_END_SYSEX);

    _serialPort->write(sendCommand);
    _serialPort->flush();
}

// Check what the hell makes the REPORT_ANALOG / REPORT_DIGITAL
// Maybe it says the device to constantly send information about this pins?
void FDevice::reportPins()
{
    char* buffer = (char*) malloc(2);

    for (int i = 0; i < 16; i++)
    {
        buffer[0] = COMMAND_REPORT_ANALOG | i;
        buffer[1] = 1;

        QByteArray s = QByteArray(buffer, 2);
        _serialPort->write(s);
        _serialPort->flush();
    }

    for (int i = 0; i < 2; i++)
    {
        buffer[0] = COMMAND_REPORT_DIGITAL | i;
        buffer[1] = 1;

        QByteArray s = QByteArray(buffer, 2);
        _serialPort->write(s);
        _serialPort->flush();
     }
}

// Check what the hell makes the PIN_STATE_QUERY
// Similar to the previous one? Im not using it now
void FDevice::requestInputs()
{
    for (int pin = 0; pin < 128; pin++)
    {
        char* buffer = (char*) malloc(4);

        buffer[0] = COMMAND_START_SYSEX;
        buffer[1] = COMMAND_PIN_STATE_QUERY;
        buffer[2] = pin;
        buffer[3] = COMMAND_END_SYSEX;

        QByteArray s = QByteArray(buffer, 4);

        _serialPort->write(s);
        _serialPort->flush();
    }
}

void FDevice::pinMode(int pin, int mode)
{

    char* buffer = (char*) malloc(3);
    buffer[0] = COMMAND_SET_PIN_MODE;
    buffer[1] = pin;
    buffer[2] = mode;
    QByteArray s = QByteArray(buffer, 3);

    _serialPort->write(s);
    _serialPort->flush();
}

bool FDevice::available()
{
    return _connected && _ready;
}

FDevice::ConnectionStatus FDevice::connectionStaus() const
{
    ConnectionStatus status = Disconnected;

    if(_connected)
        status = Connected;

    if(_connected && _ready)
        status = Ready;

    return status;
}

bool FDevice::digitalRead(int pin)
{
    return _digitalInputData[pin];
}

void FDevice::digitalWrite(int pin, int value)
{
    int portNumber = (pin >> 3) & 0x0F;
    Q_ASSERT_X(portNumber < DIGITALOUTPUTDATALENGTH, "digitalWrite", "bufferOverflow");

    if (value == 0)
         _digitalOutputData[portNumber] &= ~(1 << (pin & 0x07));
    else
         _digitalOutputData[portNumber] |= (1 << (pin & 0x07));

    QByteArray sendCommand;
    sendCommand.append(COMMAND_DIGITAL_MESSAGE | portNumber);
    sendCommand.append(_digitalOutputData[portNumber] & 0x7F);
    sendCommand.append(_digitalOutputData[portNumber] >> 7);

    _serialPort->write(sendCommand);
    _serialPort->flush();
}

int FDevice::analogRead(int pin)
{
    return _analogInputData[pin - 14];
}

void FDevice::analogWrite(int pin, int value)
{
    //this->pinMode(pin, PINMODE_PWM);

    char* buffer = (char*) malloc(3);
    buffer[0] = COMMAND_ANALOG_MESSAGE | (pin & 0x0F);
    buffer[1] = value & 0x7F;
    buffer[2] = value >> 7;

    QByteArray s = QByteArray(buffer, 3);
    //qDebug() << s;

    _serialPort->write(s);
    //qDebug() << serial->bytesToWrite();
    _serialPort->flush();

}

void FDevice::setServo(int pin, int value)
{
    //this->pinMode(pin, PINMODE_PWM);

    this->analogWrite(pin, value);

}

void FDevice::I2CRequest(int addr, int data[], int mode)
{
    char* buffer = (char*) malloc(5 + sizeof(data) * 2);

    int addr_mode;
    if (addr < 0xFF)
        addr_mode = 0x20;                          // 7 bits mode
    else
        addr_mode = 0x20;                       // 10 bits mode

    int pos = 0;
    buffer[pos++] = COMMAND_START_SYSEX;
    buffer[pos++] = COMMAND_I2C_REQUEST;
    buffer[pos++] = addr & 0xFF;                // the lsb of the address (full address for 7bits address, the most common)
    buffer[pos] = (addr & 0x380) >> 7;          // get the 3 msb for the addres in the case of 10bits i2c mode
    qDebug() << "b1: " << toBinary(buffer[pos]);
    buffer[pos] = buffer[pos] || addr_mode;     // add the addr mode to the byte
    qDebug() << "b2: " << toBinary(buffer[pos]);
    buffer[pos] = buffer[pos] || (mode << 2);   // add the read/write mode into position
    qDebug() << "b3: " << toBinary(buffer[pos]) << " / mode: " << toBinary(mode) << " / mode << 2: " << toBinary(0xFF) << "   ";
    pos++;

    for (quint32 i; i < sizeof(data) / sizeof(data[0]); i += 2)
    {
        buffer[pos++] = data[i] & 0x0F;
        buffer[pos++] = (data[i + 1] & 0xF0) >> 8;
    }

    buffer[pos++] = COMMAND_END_SYSEX;

    QByteArray s = QByteArray(buffer, pos);
    //qDebug() << s;

    _serialPort->write(s);
    //qDebug() << serial->bytesToWrite();
    _serialPort->flush();

    qDebug() << "";
    qDebug() << "Envio I2C Request:";

    for (int i = 0; i < s.size(); i++)
    {
        qDebug() << toBinary(s[i]) << "   " << hex << buffer[i];
    }
}

void FDevice::I2CConfig(int pinState, int delay)
{
    char* buffer = (char*) malloc(6);

    int pos = 0;
    buffer[pos++] = COMMAND_START_SYSEX;
    buffer[pos++] = COMMAND_I2C_CONFIG;
    buffer[pos++] = pinState;
    buffer[pos++] = delay & 0xFF;
    buffer[pos++] = delay >> 7;
    buffer[pos++] = COMMAND_END_SYSEX;

    qDebug() << "Envio I2C Config:";

    QByteArray s = QByteArray(buffer, pos);
    //qDebug() << s;

    _serialPort->write(s);
    //qDebug() << serial->bytesToWrite();
    _serialPort->flush();

    for (int i = 0; i < s.size(); i++)
    {
        qDebug() << toBinary(s[i]) << "   " << hex << buffer[i];
    }
}

void FDevice::processSerial()
{
    if(!_serialPort)
    {
        emit messageFired(_deviceName, "Serial port isn't there anymore, happy debugging!");
        return;
    }

    QByteArray seriaPortLine = _serialPort->readAll();

    //qDebug() << "Data read:" <<  hex << seriaPortLine;

    Q_ASSERT_X(seriaPortLine.length() <= 4096, "processSerial", "Bufferoverflow");

    for (int i = 0; i < seriaPortLine.length(); i++)
    {
        quint8 currentByte = seriaPortLine.at(i);
        quint8 msn = currentByte & 0xF0;

        if (msn == COMMAND_ANALOG_MESSAGE || msn == COMMAND_DIGITAL_MESSAGE || currentByte == COMMAND_REPORT_VERSION)
        {
            _parserCommandLenght = 3;
            _parserReceivedCount = 0;
        }
        else if (msn == COMMAND_REPORT_ANALOG || msn == COMMAND_REPORT_DIGITAL)
        {
            _parserCommandLenght = 2;
            _parserReceivedCount = 0;
        }
        else if (currentByte == COMMAND_START_SYSEX)
        {
            _parserCommandLenght = 4096;
            _parserReceivedCount = 0;
        }
        else if (currentByte == COMMAND_END_SYSEX)
        {
            _parserCommandLenght = _parserReceivedCount + 1;
        }
        else if (currentByte & 0x80)
        {
            _parserCommandLenght = 1;
            _parserReceivedCount = 0;
        }


        //qDebug() << "Constructing command... " << parserReceivedCount + 1 << "  /  " << parserCommandLenght;


        if (_parserReceivedCount <= _parserCommandLenght)
        {
            _bufferToParse[_parserReceivedCount] = currentByte;
            _parserReceivedCount++;

            if (_parserReceivedCount == _parserCommandLenght)
            {
                _receiving = false;
                parseBuffer();
                _parserReceivedCount = _parserCommandLenght = 0;
            }
        }
        else if (_parserReceivedCount >= _parserCommandLenght - 1)
        {
            _receiving = false;
            _parserReceivedCount = _parserCommandLenght = 0;
        }
    }
}

void FDevice::parseBuffer()
{

    quint8 cmd = (_bufferToParse[0] & 0xF0);

    if (cmd == COMMAND_ANALOG_MESSAGE && _parserReceivedCount == 3)
    {
            int analog_ch = (_bufferToParse[0] & 0x0F);
            int analog_val = _bufferToParse[1] | (_bufferToParse[2] << 7);

            Q_ASSERT_X(analog_ch < ANALOGINPUTDATALENGTH, "parseBuffer", "BuffereOverflow (_analogInputData)");

            _analogInputData[analog_ch] = analog_val;

    }
    else if (cmd == COMMAND_DIGITAL_MESSAGE && _parserReceivedCount == 3)
    {
            int port_num = (_bufferToParse[0] & 0x0F);
            int port_val = _bufferToParse[1] | (_bufferToParse[2] << 7);
            int pin = port_num * 8;

            for (int mask=1; mask & 0xFF; mask <<= 1, pin++)
            {
                bool val = (port_val & mask) ? true : false;
                if(pin < DIGITALINPUTDATALENGTH)
                    _digitalInputData[pin] = val;
            }

    }
    else if (_bufferToParse[0] == COMMAND_START_SYSEX && _bufferToParse[_parserReceivedCount - 1] == COMMAND_END_SYSEX)
    {
        qDebug("Sysex");
        emit messageFired(_deviceName, "SysEx");

        if (_bufferToParse[1] == COMMAND_REPORT_FIRMWARE)
        {
            char name[140];
            int len = 0;

            for (int i = 4; i < _parserReceivedCount - 2; i += 2)
            {
                    name[len++] = (_bufferToParse[i] & 0x7F) | ((_bufferToParse[i+1] & 0x7F) << 7);
            }

            name[len++] = '-';
            name[len++] = _bufferToParse[2] + '0';
            name[len++] = '.';
            name[len++] = _bufferToParse[3] + '0';
            name[len++] = 0;
            _firmataName = name;

            emit messageFired("SysEx", QString("Firmata-Version: %1").arg(_firmataName));

            _ready = true;
            emit deviceReady();
            emit connectionStatusChanged();
        }
        else if (_bufferToParse[1] == COMMAND_CAPABILITY_RESPONSE)
        {
                /*
                int pin, i, n;
                for (pin=0; pin < 128; pin++)
                {
                        pin_info[pin].supported_modes = 0;
                }
                for (i=2, n=0, pin=0; i<parse_count; i++)
                {
                        if (parse_buf[i] == 127)
                        {
                                pin++;
                                n = 0;
                                continue;
                        }
                        if (n == 0) {
                                // first byte is supported mode
                                pin_info[pin].supported_modes |= (1<<parse_buf[i]);
                        }
                        n = n ^ 1;
                }
                // send a state query for for every pin with any modes

                requestInputs();

                for (pin=0; pin < 128; pin++) {
                        uint8_t buf[512];
                        int len=0;
                        if (pin_info[pin].supported_modes)
                        {
                                buf[len++] = START_SYSEX;
                                buf[len++] = PIN_STATE_QUERY;
                                buf[len++] = pin;
                                buf[len++] = END_SYSEX;
                        }
                        port.Write(buf, len);
                        tx_count += len;
                }
                */
        }
        else if (_bufferToParse[1] == COMMAND_ANALOG_MAPPING_RESPONSE)
        {
            qDebug() << "COMMAND_ANALOG_MAPPING_RESPONSE";
                /*
                int pin=0;
                for (int i=2; i<parse_count-1; i++)
                {
                        pin_info[pin].analog_channel = parse_buf[i];
                        pin++;
                }
                return;
                */
        }
        else if (_bufferToParse[1] == COMMAND_PIN_STATE_RESPONSE && _parserReceivedCount >= 6)
        {
            qDebug() << "COMMAND_PIN_STATE_RESPONSE";
                /*
                int pin = parse_buf[2];
                pin_info[pin].mode = parse_buf[3];
                pin_info[pin].value = parse_buf[4];
                if (parse_count > 6) pin_info[pin].value |= (parse_buf[5] << 7);
                if (parse_count > 7) pin_info[pin].value |= (parse_buf[6] << 14);
                add_pin(pin);
                */
        }
        //elseif (parserBuffer[1] == COMMAND_)
        else
        {
            qDebug() << "Sysex command not recognized: " << hex << _bufferToParse[1];
        }
    }
    else
    {
        qDebug() << "Command not recognized: " << hex << _bufferToParse[0] << "(" << dec << _parserReceivedCount << " parameters)";

        for (int i = 0; i < _parserReceivedCount; i++)
        {
            qDebug() << _bufferToParse[i] << " / " << hex << _bufferToParse[i];
        }
    }

    //qDebug() << "Command completed!!";
}

