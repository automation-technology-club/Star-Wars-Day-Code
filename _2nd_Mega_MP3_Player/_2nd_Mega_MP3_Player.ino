
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
    
  InitSPI();
  InitIOForVs10xx();
  InitIOForKeys();
  InitIOForLEDs();
  Mp3Reset();
  if (!initialSDCard())
    return;

  RED_LED_ON();//light red LED

//pinMode(22, INPUT); //change track trigger
pinMode(23, OUTPUT); //track playing

randomSeed(382873);

}


void loop()
{ 

  Serial2.flush();
  if(Serial2.available()) {
  song=Serial2.read();
  Serial.println((char)song);
  changetrack();
  }
  
 
  
//digitalWrite(23, LOW);
//if (song > 7) {song = 0;}
//if (digitalRead(22) == HIGH) {changetrack();}
//changetrack();  
//  playFile("force1.mp3");
//  playFile("imperial.mp3");
//  playFile("starwars.mp3");
//  playFile("blaster.mp3"); //play the song with the name you give.
//playFile("test.wma");
//playFile("test.wav");

//playFile("breath.mp3");
//playFile("c3po.mp3");
//playFile("carpet.mp3");
//playFile("checked.mp3");
//playFile("crops.mp3");
//playFile("badfeeling.mp3");
}

int changetrack() {
  isplaying = 1;qa
  Serial1.write(isplaying);
  digitalWrite(23, HIGH);
  switch (song) {
    case 0:
    while(playFile("starwars.mp3")>1); //44 seconds.
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
  //delay(44000); 
    Serial.println("Star Wars Done.");
    break;
    case 1:
    while(playFile("rebel.mp3")>1); //4 minutes During Self Check routine
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    //delay(240000);
    Serial.println("Rebel Theme Done");
    break;
    case 2:
    while(playFile("imperial.mp3")>1); // 37 seconds
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    //delay(37000);
    Serial.println("Imperial March Done!");
    break;
    case 3:
    while(playFile("r2d2wst2.mp3")>1); //1 second
    while(playFile("c3po.mp3")>1); //1 second
    while(playFile("r2d2wst3.mp3")>1); //2 seconds
    //delay(4000);
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Random Droid Sounds Done");
    break;
    case 4:
    while(playFile("breath.mp3")>1); //4 seconds
    while(playFile("jawascr.mp3")>1); //2 seconds
    //playFile("blaster.mp3"); //<1 seconds
    //delay(6000);
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Darth Vader -Scared Droid Done");
    break;
    case 5:
    while(playFile("blaster.mp3")>1); //<1 second
    while(playFile("blaster.mp3")>1);
    //while(playFile("blaster.mp3")>1);
    //delay(1500);
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Blaster Done");
    break;
    case 6:
    while(playFile("cantina.mp3")>1); //2 mintues 47 seconds
    //dance break;
    //delay(167000);
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("Dance Break Done!");
    break;
    case 7:
    while(playFile("force2.mp3")>1); //2 seconds
    //delay(2500);
     isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
    Serial.println("May The Force Be With You.");
    break;
    case 8:
    Serial.println("Random Sound");
    String r;
    int rx = random(0,37);
    r = String(rx);
    r = r + ".mp3";
    char ran[10];
    r.toCharArray(ran,10);
    while(playFile(ran)>1);
    digitalWrite(23, LOW);
    break;
  }
//  song = song + 1;
  //while(1);
   isplaying = 0;
  Serial1.write(isplaying);
  digitalWrite(23, LOW);
}




