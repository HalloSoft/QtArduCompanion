#ifndef FDEVICE_H
#define FDEVICE_H

/*
 * Originaliy from: https://github.com/dh1tw/firmatator
 */
#include "qfirmata_global.h"

#include <QObject>
//#include <stdint.h>

#include <QSerialPort>
#include <QSerialPortInfo>

#define ANALOGINPUTDATALENGTH   10
#define DIGITALINPUTDATALENGTH  10
#define DIGITALOUTPUTDATALENGTH 10
namespace qfirmata
{
class FDevice : public QObject
{
    Q_OBJECT

public:
    enum ConnectionStatus
    {
        Disconnected, Connected, Ready
    };

    FDevice(QString serialPortName = QString(), int _baud_rate = 57600);
    bool connectDevice(QString portName = QString()); // TODO: maybe const
    void disconnectDevice();

    bool             available();
    ConnectionStatus connectionStaus() const;

    void reportFirmware();
    void requestCapabilities();
    void reportPins();
    void requestInputs();

    void pinMode(int pin, int mode);
    bool digitalRead(int pin);
    void digitalWrite(int pin, int value);
    int  analogRead(int pin);
    void analogWrite(int pin, int value);
    void setServo(int pin, int value);
    void I2CRequest(int addr, int data[], int mode);
    void I2CConfig(int pinState, int delay);

    QString deviceName() const {return _deviceName;}
    void setDeviceName(const QString deviceName) {_deviceName = deviceName;}


    // Firmata protocol constants
    static const int MAX_DATA_BYTES                  = 32;
    static const int PINMODE_INPUT                   = 0;
    static const int PINMODE_OUTPUT                  = 1;
    static const int PINMODE_ANALOG                  = 2;
    static const int PINMODE_PWM                     = 3;
    static const int PINMODE_SERVO                   = 4;
    static const int PINMODE_SHIFT                   = 5;
    static const int PINMODE_I2C                     = 6;

    static const int DIGITAL_LOW                     = 0;
    static const int DIGITAL_HIGH                    = 1;

    static const int I2C_MODE_7_BITS                 = 0;
    static const int I2C_MODE_10_BITS                = 1;

    static const int I2C_MODE_WRITE                  = 0;
    static const int I2C_MODE_READ_ONCE              = 1;
    static const int I2C_MODE_READ_CONSTINOUSLY      = 2;
    static const int I2C_MODE_READ_STOP              = 3;

    static const quint8 COMMAND_REPORT_VERSION          = 0xF9; // report firmware version
    static const quint8 COMMAND_SYSTEM_RESET            = 0xFF; // reset from MIDI
    static const quint8 COMMAND_SET_PIN_MODE            = 0xF4; // set a pin to INPUT/OUTPUT/PWM/etc
    static const quint8 COMMAND_DIGITAL_MESSAGE         = 0x90; // send data for a digital port
    static const quint8 COMMAND_ANALOG_MESSAGE          = 0xE0; // send data for an analog pin (or PWM)
    static const quint8 COMMAND_REPORT_ANALOG           = 0xC0; // enable analog input by pin #
    static const quint8 COMMAND_REPORT_DIGITAL          = 0xD0; // enable digital input by port
    static const quint8 COMMAND_SERVO_CONFIG            = 0x70; // set the parameters for a servo pin (max and min pulse, max and min angle)

    static const quint8 COMMAND_START_SYSEX             = 0xF0; // start a MIDI SysEx message
    static const quint8 COMMAND_END_SYSEX               = 0xF7; // end a MIDI SysEx message

    static const quint8 COMMAND_I2C_REQUEST             = 0x76;
    static const quint8 COMMAND_I2C_REPLY               = 0x77;
    static const quint8 COMMAND_I2C_CONFIG              = 0x78;
    static const quint8 COMMAND_I2C_SAMPLING_INTERVAL   = 0x7A;

    static const quint8 COMMAND_PIN_MODE_QUERY          = 0x72; // ask for current and supported pin modes
    static const quint8 COMMAND_PIN_MODE_RESPONSE       = 0x73; // reply with current and supported pin modes
    static const quint8 COMMAND_PIN_STATE_QUERY         = 0x6D;
    static const quint8 COMMAND_PIN_STATE_RESPONSE      = 0x6E;
    static const quint8 COMMAND_CAPABILITY_QUERY        = 0x6B;
    static const quint8 COMMAND_CAPABILITY_RESPONSE     = 0x6C;
    static const quint8 COMMAND_ANALOG_MAPPING_QUERY    = 0x69;
    static const quint8 COMMAND_ANALOG_MAPPING_RESPONSE = 0x6A;
    static const quint8 COMMAND_REPORT_FIRMWARE         = 0x79;


public slots:


signals:

    void deviceReady();
    void digitalInputChanged();
    void connectionStatusChanged();
    void messageFired(const QString& category, const QString& message);
    void error(QSerialPort::SerialPortError error);

private slots:
    void initialize();
    void processSerial();

private:
    void parseBuffer();

    // Firmata protocol vars
    QString     _firmataName;
    QString     _deviceName;
    bool        _ready {false};
    int         _majorVersion;
    int         _minorVersion;

    // Inputs / outputs status
    int  _analogInputData[ANALOGINPUTDATALENGTH];
    bool _digitalInputData[DIGITALINPUTDATALENGTH];
    int  _digitalOutputData[DIGITALOUTPUTDATALENGTH];


    // Serial connection vars
    QSerialPort* _serialPort;
    bool         _connected {false};
    int          _baud_rate;
    quint8*      _bufferToParse;
    int          _parserCommandLenght;
    int          _parserReceivedCount;
    bool         _receiving;           // TODO: check this variable and its usage

};
} // namespace

#endif // FDEVICE_H
