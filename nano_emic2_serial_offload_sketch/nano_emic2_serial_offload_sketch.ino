// This example exposes some of the functionality of the EMIC2 library
//library can be found: https://github.com/pAIgn10/EMIC2

//LeRoy Miller 2015 - based off the example sketch in the above library.

#include <SoftwareSerial.h>  // Needed by the EMIC2 library
#include <SD.h>  // Needed by the EMIC2 library, though not utilized in this example
#include "EMIC2.h"

// Read here: http://arduino.cc/en/Reference/SoftwareSerial
// for the available pins on your board

#define RX_PIN 2  // Connect SOUT pin of the Emic 2 module to the RX pin
#define TX_PIN 3  // Connect SIN pin of the Emic 2 module to the TX pin

EMIC2 emic;  // Creates an instance of the EMIC2 library

String Data = "";

void setup()

{
    // Initializes the EMIC2 instance
    // The library sets up a SoftwareSerial port
    // for the communication with the Emic 2 module

    emic.begin(RX_PIN, TX_PIN);
    Serial.begin(9600);
    emic.setVoice(0);  // Sets the voice (9 choices: 0 - 8)
    pinMode(12, OUTPUT);
    emic.setVolume(10);
    Data = "Testing Testing.";
    speak();
    Data = "3.14";
    speak();
    Serial.flush();
}


void loop()

{

if (Serial.available() > 0) {
  char character = Serial.read();
  Serial.println(character);
  Data = Data + character;
    if (character == '\n') {
	Serial.println(Data);
	speak();
	Data = "";
		}
	}	
}

void speak() {

  digitalWrite(12, HIGH);
  emic.speak(Data);
  digitalWrite(12, LOW);
    }


