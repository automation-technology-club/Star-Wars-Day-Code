
#include <Arduino.h>
#include <avr/io.h>
#include "config.h"
#include "player.h"
#include "vs10xx.h"

#include <Fat16.h>
#include <Fat16Util.h>
#include "newSDLib.h"

int song;
int isplaying;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600); //used to talk to light saber 
  
  InitSPI();
  InitIOForVs10xx();
  InitIOForKeys();
  InitIOForLEDs();
  Mp3Reset();
  if (!initialSDCard())
    return;

  RED_LED_ON();//light red LED


pinMode(23, OUTPUT); //track playing
pinMode(25, OUTPUT);

randomSeed(382873);

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
    digitalWrite(25, HIGH);
    Serial3.write(7);
    while(playFile("saberon.mp3"));
    delay(200);
    while(playFile("starwars.mp3")); //44 seconds.
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(25, LOW);
  delay(300);
  while(playFile("saberoff.mp3"));
  digitalWrite(23, LOW);
  digitalWrite(25, LOW);
  
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
     Serial3.write(5);
     digitalWrite(25, HIGH);
     while(playFile("saberon.mp3"));   //added for testing Nov 17 without this it works great
     delay(1000); //added
     while(playFile("cantina.mp3")); //2 mintues 47 seconds
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW); //added for testing
  digitalWrite(25, LOW);  //added for testing Nov 17 without this it works great
  delay(300); //added for testing
  while(playFile("saberoff.mp3")); //added for testing Nov 17 without this it works great
  digitalWrite(23, LOW);
  digitalWrite(25, LOW);
  
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
    Serial3.write(6);
    digitalWrite(25, HIGH);
  Serial.println("Light Saber");
  while(playFile("saberon.mp3") );
  while(playFile("saberhum.mp3") );
  delay(300);
  while(playFile("saberhum.mp3"));
  digitalWrite(25,LOW);
  delay(300);  
  while(playFile("saberoff.mp3"));
	digitalWrite(23, LOW);
    digitalWrite(25, LOW);
	break;
  }
  }

   isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
  digitalWrite(25, LOW);
}


