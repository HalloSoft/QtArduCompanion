/*
 * Firmata is a generic protocol for communicating with microcontrollers
 * from software on a host computer. It is intended to work with
 * any host computer software package.
 *
 * To download a host software package, please clink on the following link
 * to open the download page in your default browser.
 *
 * http://firmata.org/wiki/Download
 */

/*
 * This firmware reads all inputs and sends them as fast as it can.  It was
 * inspired by the ease-of-use of the Arduino2Max program.
 *
 * This example code is in the public domain.
 */
#include <Firmata.h>

/* timer variables */
unsigned long previousMillis;    // for comparison with currentMillis
unsigned long intervall = 1000;         // for comparison with currentMillis

// Debug
bool ledOn = false;

void sendPort(byte portNumber, byte portValue)
{
    Firmata.sendDigitalPort(portNumber, portValue);
 
}

void setup()
{
  Firmata.begin(57600);
  //Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  // Debug
  pinMode(13, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();;

  if ((currentMillis - previousMillis) > intervall)
  {
    if(ledOn)
    {
      digitalWrite(13, LOW);
      ledOn = false;  
    }
    else
    {
      digitalWrite(13, HIGH);
      ledOn = true;
    }  

     sendPort(0, 0xf);
//     Serial.print("C: ");
//     Serial.println(currentMillis);  
//     Serial.print("P: ");
//     Serial.println(previousMillis);
//     Serial.print("I: ");
//     Serial.println(intervall);
//     Serial.print("D: ");
//     Serial.println(currentMillis - previousMillis);
     previousMillis = currentMillis;
     
  }
  //delay(300);
}


