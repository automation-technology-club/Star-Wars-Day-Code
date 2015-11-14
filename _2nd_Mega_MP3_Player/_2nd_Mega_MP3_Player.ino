
#include <Arduino.h>
#include <avr/io.h>
#include "config.h"
#include "player.h"
#include "vs10xx.h"

#include <Fat16.h>
#include <Fat16Util.h>
#include "newSDLib.h"
#include <Adafruit_NeoPixel.h>

int PIN = 49;
int totalLEDs = 30;
int ledFadeTime = 5;
int song;
int isplaying;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(totalLEDs, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
    
  InitSPI();
  InitIOForVs10xx();
  InitIOForKeys();
  InitIOForLEDs();
  Mp3Reset();
  if (!initialSDCard())
    return;

  RED_LED_ON();//light red LED


pinMode(23, OUTPUT); //track playing

randomSeed(382873);

 strip.begin();
 strip.show(); // Initialize all pixels to 'off'

}


void loop()
{ 
  /*
  song = 9;
  changetrack();
  while(1);
  */ 
  // The above lines are for testing only
  
  Serial2.flush();
  if(Serial2.available()) {
  song=Serial2.read();
  Serial.println((char)song);
    changetrack();
    }
  
 
}

int changetrack() {
  isplaying = 1;
  Serial1.write(isplaying);
  digitalWrite(23, HIGH);
  switch (song) {
    case 0:
    while(playFile("starwars.mp3")); //44 seconds.
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
  
    Serial.println("Star Wars Done.");
    break;
    case 1:
    while(playFile("rebel.mp3")); //4 minutes During Self Check routine
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    
    Serial.println("Rebel Theme Done");
    break;
    case 2:
    while(playFile("imperial.mp3")); // 37 seconds
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
   
    Serial.println("Imperial March Done!");
    break;
    case 3:
    while(playFile("r2d2wst2.mp3")); //1 second
   // while(playFile("c3po.mp3")>1); //1 second
    while(playFile("r2d2wst3.mp3")); //2 seconds
    
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    
    break;
    case 4:
    while(playFile("breath.mp3")); //4 seconds
    //while(playFile("jawascr.mp3")>1); //2 seconds
    
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Darth Vader -Scared Droid Done");
    break;
    case 5:
    while(playFile("blaster.mp3")); //<1 second
    while(playFile("blaster.mp3"));
    
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Blaster Done");
    break;
    case 6:
    do {
      discoleds(ledFadeTime);
    } while(playFile("cantina.mp3")); //2 mintues 47 seconds
     saberoff();
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Dance Break Done!");
    break;
    case 7:
    while(playFile("force2.mp3")); //2 seconds
    
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("May The Force Be With You.");
    break;
    case 8:
    {
    Serial.println("Random Sound");
    String r;
    int rx = random(0,37);
    r = String(rx);
    r = r + ".mp3";
    char ran[10];
    r.toCharArray(ran,10);
    while(playFile(ran));
    digitalWrite(23, LOW);
    break;
    }
  case 9:
  {
  Serial.println("Light Saber");
  saberon(0, 255, 0, ledFadeTime);
  while(playFile("saberon.mp3") );
  for (int xx = 0; xx > 20; xx++) {
  rgbFadeInAndOut(0, 255, 0, ledFadeTime); //green
  while(playFile("saberhum.mp3") );
  }
	saberoff();
	while(playFile("saberoff.mp3"));
	digitalWrite(23, LOW);
	break;
  }
  }

   isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
}

void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
 strip.setPixelColor(0, 255, 0,0);
  for(uint8_t b = 75; b <255; b++) {
     for(uint8_t i=8; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }

     strip.show();
     delay(wait);
  };

  for(uint8_t b=255; b > 75; b--) {
     for(uint8_t i = 8; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }
     strip.show();
     delay(wait);
  };
};

void saberon(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
	for (uint8_t i = 8; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, red, green, blue);
		strip.show();
		delay(25);
	}
}

void saberoff() {
	for (uint8_t i = strip.numPixels(); i > 7; i--) {
		strip.setPixelColor(i, 0, 0, 0);
		strip.show();
		delay(25);
	}
}

void discoleds(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=8; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


