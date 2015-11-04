//  File MusicPlayWithName.ino
//  Demo code for playing any existing music file on Micro SD card by file name
//  For more details about the product please check http://www.seeedstudio.com/depot/

//  Copyright (c) 2010 seeed technology inc.
//  Author: Icing Chang
//  Version: 1.0
//  Time: Oct 21, 2010
//  Changing records:
//    
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/**************************Note*******************************************
 To make this demo code run sucessfully, you need to download the fat16lib 
 into your Arduino library at the following address:
http://code.google.com/p/fat16lib/downloads/detail?name=fat16lib20101009.zip&can=2&q=
**************************************************************************/

#include <Arduino.h>
#include <avr/io.h>
#include "config.h"
#include "player.h"
#include "vs10xx.h"

#include <Fat16.h>
#include <Fat16Util.h>
#include "newSDLib.h"

void setup()
{
  Serial.begin(9600);

  InitSPI();

  InitIOForVs10xx();

  InitIOForKeys();

  InitIOForLEDs();

  Mp3Reset();
  if (!initialSDCard())
    return;

  RED_LED_ON();//light red LED
}


void loop()
{ 
  /*
  playFile("starwars.mp3");
  playFile("badfeel.mp3");
  playFile("blaster.mp3");
  playFile("breath.mp3");
  playFile("c3po.mp3");
  playFile("carpet.mp3");
  playFile("checked.mp3");
  playFile("crops.mp3");
  playFile("deity.mp3");
  playFile("detonatr.mp3");
  playFile("disturb.mp3");
  playFile("droid2.mp3");
  playFile("droid3.mp3");
  playFile("droids.mp3");
  playFile("ewokpara.mp3");
  playFile("faith.mp3");
  playFile("fire.mp3");
  playFile("force.mp3");
  playFile("force1.mp3");
  playFile("force2.mp3");
  playFile("fstrong.mp3");
  playFile("helpme.mp3");
  playFile("humnbehv.mp3");
  playFile("imperial.mp3");
  playFile("jawascr.mp3");
  playFile("jawastun.mp3");
  playFile("luck.mp3");
  playFile("master.mp3");
  playFile("notout.mp3");
  playFile("plans.mp3");
  */
  playFile("princess.mp3");
  /*
  playFile("r2d2wst1.mp3");
  playFile("r2d2wst2.mp3");
  playFile("r2d2wst3.mp3");
  playFile("r2d2wst4.mp3");
  playFile("r2d2wstl.mp3");
  playFile("r2d2.mp3");
  playFile("rebel.mp3");
  */
  
  playFile("remotes.mp3");
  playFile("reward.mp3");
  playFile("saberoff.mp3");
  playFile("saberon.mp3");
  playFile("sandppl.mp3");
  playFile("scum.mp3");
  playFile("cantina.mp3");
  playFile("vader03.mp3");
  playFile("wait.mp3");
 playFile("duelfate.mp3"); 
  //play the song with the name you give.
//playFile("test.wma");
//playFile("test.wav");
}



