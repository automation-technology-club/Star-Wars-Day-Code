/* On Mar 9, 2015 6:09PM Eastern Time. 
The Hero Jr become 98.99% complete, power was given to him via his on board battery
and he sung Daisy for the 1st time! */

/*
At this point, a lot more of the code needs to be written, but all of the 
hardware is hooked up. 
Only optional hardware may need to be added.
Some type of wireless device, a RTC, and a PIR sensor.
*/

/* Code Version 101115.2003 */

/* Copyright 2015 LeRoy Miller
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses
 */
    

#include <Wire.h>
#include <Keypad.h>
#include <NewPing.h>
#include <Stepper.h>

/*Hero Jr Control - Arduino Mega
Commands:
key() - read a button push from the keypad
ping() - read distance from ping sensor
led(#) - turn on led # 0 to 7 state is toggled on or off
forward(distance) - move forward 
reverse(distance) - move backward
left(degree) - turn to the left 
right(degree) - turn to the right
light() - read the light sensor
volt() - check the voltage levels for the drive battery
test() - test leds, speech, drive motor, turning motor, ultrasonic, voltage, light
rinit() - reset Arduino Mega board to power on conditions
listen() - returns when it hears a sound (Signal Wire hooks up to pin 53 on the Mega. Sound sensor works at 5v)
speak(string) - string of what to say
speakint(int) - say an int number by converting it to a string
speakcmd(command) - gives a way to change the speech output
singhbd() - sing Happy Birthday
singdaisy() - sing Daisy
guess() - Guess the Number between 0 and 999 game
keytest() - test the keypad

*** Voltage Sensor Information
This seems to work 3.3v hooked to output side
and "S" hooked to Analog input 1
It qives whole numbers as output
Tested on the UNO, and not sure why it needs "Wire.h"

Just for run ** New Command: 
cylon(times) - will cause the leds to cycle back and forth the number of times given

More Functions to add relating to the Keypad:
sing - mapped to key 4 - randomly sign one of three songs 
play - mapped to key 5 - Ask which game you want to play
help - mapped to key 6 - 
speak - mapped to key 7 - 
gab - mapped to key 8 -
poet - mapped to key 9 - tells a random poem (one of three)
demo - mapped to key A - not sure yet
guard - mapped to key B - random move, using ultra sonic and drive
alarm - mapped to key C - Using PIR or Ultrasonic to watch something and make sure it doesn't move - if it does sound alarm (probably loud speech)
plan - mapped to key D - not sure what this does
setup - mapped to key E - 
enter - mapped to key F - enter key
*/

int lightPin = 0; //analog pin0 for photoresistor

#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm. About 78 Inches
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int val11; 
int val2; 
int led0 = 22;
int led1 = 24;
int led2 = 26;
int led3 = 28;
int led4 = 30;
int led5 = 32;
int led6 = 34;
int led7 = 36;
int state0 = 1;
int state1 = 1;
int state2 = 1;
int state3 = 1;
int state4 = 1;
int state5 = 1;
int state6 = 1;
int state7 = 1;
int timea;
int sound = 0;
int count = 0;
int enA = 38;
int in1 = 40;
int in2 = 50;


const int stepsPerRevolution = 200; 
const byte ROWS = 4; // Four rows
const byte COLS = 4; // four columns
// Define the Keymap

char keys[ROWS][COLS] = {
  {'C','D','E','F'},
  {'8','9','A','B'},
  {'4','5','6','7'},
  {'0','1','2','3'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 4, 5, 6, 7 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 8, 9, 10, 11 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Stepper myStepper(stepsPerRevolution, 46, 44, 42, 48); 

int stepCount = 0;  
int number;
int state;
String command;
int distance;
int speed;
int degree;
int fl;
String str; //use this to convert a int to a char for speech.

//Needed for Card Games
int cards[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14};

int deck[52];
char decksuite[52];
int r;
int hearts[13], clubs[13], spades[13], diamonds[13];
//end card games

void setup() 
{   
   
Serial.begin(9600);
Serial1.begin(9600); //Serial 1 is used for the eMIC 2 
delay(5000); //wait for eMIC 2 to come online
Serial1.flush();
Serial1.println();
Serial1.println("v10"); //set volume to level 10
delay(500);
Serial1.println("p0"); //set pharser for DECtalk
pinMode(52, OUTPUT); //Pin 52 is used to provide 5v to the Sound sensor
digitalWrite(52, HIGH); 
   pinMode(led0, OUTPUT);
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
   pinMode(led4, OUTPUT);
   pinMode(led5, OUTPUT);
   pinMode(led6, OUTPUT);
   pinMode(led7, OUTPUT);
   pinMode(enA, OUTPUT);
   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   digitalWrite(led0, 1);
   digitalWrite(led1, 1);
   digitalWrite(led2, 1);
   digitalWrite(led3, 1);
   digitalWrite(led4, 1);
   digitalWrite(led5, 1);
   digitalWrite(led6, 1);
   digitalWrite(led7, 1);
   Serial.println(""); 
   Serial.println("");
   Serial.println("Hero Jr Control Program");
   Serial.println("Ready");
   Serial.println(">");
   myStepper.setSpeed(75);
   randomSeed(light()+ping()+millis());
   
} 

void (* resetFunc) (void) = 0;

void loop() 
{       
	//play Starwars.mp3 (This is the openning title music) While playing have Hero Give a welcome speech
speak ("Welcome to our special, Star Wars Day!");
//wait for song to end.
speak ("I am a Hero Junior Robot, and one of my most favorite movies is");

speak ("Star Wars, I wish I could fight against the ");

// play imperial.mp3
speak ("Impire along side of my Friends, R 2 D 2 and C 3 P O");

//wait for imperial to end, and play r2d2wst.mp3 wait r2d2wst1.mp3 wait.
//play c3po.mp3 wait.
speak("They are my Heros. ");
speak("But I am a little afraid of ");
//play breath.mp3 
speak("Oh my....Darth Vader. ");
speak("Where is my blaster.");
//if breath is done, play blaster.mp3
speak("Did I scare him off?");
speak("I think I scared myself a little bit." );
//play r2d2wstl.mp3 wait till done
//play star-wars-cantina-song.mp3
//while (cantina is playing...) {
//forward(20);
//left(45);
//forward(15);
//left(45);
//forward(10);
//left(45);
//forward(20);
//}
cylon(10);
speak("Hit a button on my keypad to hear a Star Wars");
	speak("Sound. Hit E to exit. ");

starwarsplay();
}                  

void speakcmd(char say[]) {
	
	Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	Serial1.println(say);
	while(Serial1.read() != ':');
	delay(500);
	
}

void singdaisy() {

	/*"Daisy Bell (Bicycle Built for Two)" is a popular song, written in 1892 by Harry Dacre,
	with the well-known chorus "Daisy, Daisy / Give me your answer, do. / I'm half crazy / all for the love of you", ending with the words "a bicycle built for two".
    It is the earliest known song sung using computer speech synthesis, as later referenced in the film 2001: A Space Odyssey.
    It is also included as a demo of the Parallax eMic 2 speech synthesizer
*/
	Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	Serial1.println("d1");
	ledmouth();
	Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
}
void singhbd() {
//Happy Birthday (shortten version) 
/*  The combination of melody and lyrics in "Happy Birthday to You" first appeared in print in 1912, 
    and probably existed even earlier. None of these early appearances included credits or copyright notices. 
    The Summy Company registered for copyright in 1935, crediting authors Preston Ware Orem and Mrs. R.R. Forman
*/
	Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	Serial1.println("s[:phone arpa speak on][:rate 200][:n0][hxae<300,10>piy<300,10>brrrx<600,12>th<100>dey<600,10>tuw<600,15> yu<1200,14>_<300> hxae<300,10>piy<300,10>brrrx<600,12>th<100>dey<600,10> tuw<600,17>yu<1200,15>_<300> hxae<300,10>piy<300,10>brrrx<600,22>th<100>dey<600,19> _<150>_<300>hxae<300,20>piy<300,20>brrrx<600,19>th<100>dey<600,15> tuw<600,17> yu<1200,15>][:n0]");
	ledmouth();
	Serial1.println();
while(Serial1.read() != ':');
	delay(500);

}

void speak(char say[]) {

	Serial1.println();
	while(Serial1.read() != ':') {delay(1);}
	delay(500);
	Serial1.print("s");
	Serial1.println(say);
		ledmouth();
	Serial1.println();
	while(Serial1.read() != ':') {delay(1);}
	delay(500);
}

void speakint(int say) {
 
	Serial1.println();
	while(Serial1.read() != ':') {delay(1);}
	delay(500);
	Serial1.print("s");
	Serial1.println(say);
		ledmouth();
	Serial1.println();
    while(Serial1.read() != ':') {delay(1);}
//	delay(500);
}

int listen() {
	//delay(1000);
	Serial.println("Listen Subroutine!");
	/*while(digitalRead(53) != 0) {
		delay(100);
	}
	Serial.println("Sound Detected! Return");
	*/
	//wait for about 15 seconds and move on
	for (int waiting=0; waiting <= 7000; waiting++) {
	sound = digitalRead(53);
	if (sound == 0) { 
		Serial.println("Sound detected! :");
		return(1);
			}
			Serial.println(waiting);
	//delay(250);		
		}
		return(0);
}



int key() {

delay(100);
for (int waiting=0; waiting <= 50000; waiting++) {
 char key = kpd.getKey();
 if(key)  // Check for a valid key.
  {
    switch (key)
    {
        default:
 		Serial.print("Key Pressed: ");
 		Serial.println(key);
        if (key-48>=17) {return (key-55);} else { return(key-48);}
        
    }
}
}
}

int ping() {
 unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
   Serial.println(uS / US_ROUNDTRIP_IN); // Convert ping time to distance in cm and print result (0 = outside set distance range)
   return(uS/US_ROUNDTRIP_IN);
}

void led(int number1) {

switch (number1) {
	case 0:
	state0 = !state0;
		digitalWrite(led0, state0);
		break;
	case 1:
	state1 = !state1;
		digitalWrite(led1, state1);
		break;
	case 2:
	state2 = !state2;
		digitalWrite(led2, state2);
		break;
	case 3:
	state3 = !state3;
		digitalWrite(led3, state3);
		break;
	case 4:
	state4 = !state4;
		digitalWrite(led4, state4);
		break;
	case 5:
	state5 = !state5;
		digitalWrite(led5, state5);
		break;
	case 6:
	state6 = !state6;
		digitalWrite(led6, state6);
		break;
	case 7:
	state7 = !state7;
		digitalWrite(led7, state7);
		break;
	}
}

void forward(int distance) {
	digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255);
    delay(1000*distance); //how long the motor should be left on 
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}

void reverse(int distance) {
	digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 255);
    delay(1000*distance); //how long the motor should be left on
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}

void left(int degree) {

  if (degree > 90) {speak("Error in Degree"); return;}
  myStepper.step(100*(degree/15));
}

void right(int degree) {

if (degree > 90) {speak("Error in Degree"); return;}
  myStepper.step(-100*(degree/15));
}

int light() {
	int photor = analogRead(lightPin);
	Serial.println(photor);
	delay(50);
	return(photor);
}

int volt() {
float temp;       
val11=analogRead(1);
temp=val11/4;       
val11=(int)temp;       
val2=((val11)/10);
Serial.println(val2);          
return(val2);
}

void motortest() {
	
	speak("Test Drive Motor Forward");
	forward(1);
	delay(500);
	speak("Test Drive Motor Reverse");
	reverse(1);
	delay(500);
	speak("Test Turn left 90 degrees");
	left(90);
	delay(500);
	forward(1);
	delay(500);
	speak("And back.");
	right(90);
	delay(500);
	reverse(1);
	delay(500);
	speak("Test Turn Right 90 degrees");
	right(90);
	delay(500);
	forward(1);
	delay(500);
	speak("And back.");
	left(90);
	delay(500);
	reverse(1);
	delay(500);

}

void cylon(int times) {
   digitalWrite(led0, 1);
   digitalWrite(led1, 1);
   digitalWrite(led2, 1);
   digitalWrite(led3, 1);
   digitalWrite(led4, 1);
   digitalWrite(led5, 1);
   digitalWrite(led6, 1);
   digitalWrite(led7, 1);
   for (int i = 1; i < times; i++){
   	digitalWrite(led0, 0);
   	delay(100);
   	digitalWrite(led0, 1);
   	digitalWrite(led1, 0);
   	delay(100);
   	digitalWrite(led1, 1);
   	digitalWrite(led2, 0);
   	delay(100);
   	digitalWrite(led2, 1);
   	digitalWrite(led3, 0);
   	delay(100);
   	digitalWrite(led3, 1);
   	digitalWrite(led4, 0);
   	delay(100);
   	digitalWrite(led4, 1);
   	digitalWrite(led5, 0);
   	delay(100);
   	digitalWrite(led5, 1);
   	digitalWrite(led6, 0);
   	delay(100);
   	digitalWrite(led6, 1);
   	digitalWrite(led7, 0);
   	delay(100);
   	digitalWrite(led7, 1);
   	digitalWrite(led6, 0);
   	delay(100);
   	digitalWrite(led6, 1);
   	digitalWrite(led5, 0);
   	delay(100);
   	digitalWrite(led5, 1);
   	digitalWrite(led4, 0);
   	delay(100);
   	digitalWrite(led4, 1);
   	digitalWrite(led3, 0);
   	delay(100);
   	digitalWrite(led3, 1);
   	digitalWrite(led2, 0);
   	delay(100);
   	digitalWrite(led2, 1);
   	digitalWrite(led1, 0);
   	delay(100);
   	digitalWrite(led1, 1);
   	
   }
   digitalWrite(led0, state0);
   digitalWrite(led1, state1);
   digitalWrite(led2, state2);
   digitalWrite(led3, state3);
   digitalWrite(led4, state4);
   digitalWrite(led5, state5);
   digitalWrite(led6, state6);
   digitalWrite(led7, state7);
   //Serial.println(">");
}

void credit() {
	
	speak("I am a Heath Kit Hero Junior Robot, I came online on March ninth 20 fifteen");
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
//	speak(" on March ninth 20 fifteen");
	speak("at 6:09 pm eastern time");
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	speak("I was restored by LeRoy Miller, using modern electronic hardware.");
}

void rhyme1() {
	//A-Tisket, A-Tasket is a traditional American nursery rhyme. It was first time published in 1879. But it became very popular when it was recorded by Ella Fitzgerald in 1938
speakcmd("n2");
	speak("A-tisket, a-tasket.");
	speak("A green and yellow basket");
	speak("I wrote a letter to my love");
	speak("And on the way I dropped it.");
	speak("I dropped it");
	speak("I dropped it");
	speak("Yes, on the way I dropped it");
	speak("A little boy he picked it up");
	speak("and put it in his pocket");
	speakcmd("n0");
}

void rhyme2() {
	//Humpty Dumpty is a traditional English nursery rhyme about an egg. It was published in 1810. In other words, this nursery rhyme has been used for generations. 
 speak("Humpty Dumpty sat on a wall,");
speak("Humpty Dumpty");
speak (" had a great fall");
speak("All the King's horses And all the king's men.");
speak("Cannot put Humpty Dumpty Together again");

}

void quote1() {
	speak("Life is short, and it is up to you to make it sweet.  Sarah Louise Delany");
}

void quote2() {
	speak("The Pen is mightier than the sword if the sword is very short, and the pen is very sharp.  Terry Pratchett");
}

void quote3() {
	speak("You have to learn the rules of the game.  And then you have to play better than anyone else. Albert instein");
}

void quote4() {
speak("Insanity:  Doing the same thing over and over again and expecting different results.  Albert instein");
}

void quote5() {
	speak("The true sign of intelligence is not knowledge but imagination.  Albert instein");
}

void robotlaws() {
	/* The three Laws of Robotics which govern the behaviour of Isaac Asimov's fictional Positronic Robots were formally stated by Asimov in his story "Runaround" March 1942 Astounding */
	/* Others have expanded on the laws to include a 4th and 5th law, this robot is only bound by the 1st three, and perhaps the Zeroth Law which would seem to violate the 1st Law */
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	speak("I am governed by three laws of robotics, as set forth by Sir Isaac Asimov. ");
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	speak("1. A robot may not injure a human being or, though inaction, allow a human being to come to harm; ");
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	speak("2. A robot must obey the orders given it by human beings except where such orders would conflict with the first law; ");
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	speak("3. A robot must protect its own existence as long as such protection does not conflict with the first or second law. ");
		Serial1.println();
	while(Serial1.read() != ':');
	delay(500);
	speak("The Zeroth Law: A robot may not harm humanity, or by inaction, allow humanity to come to harm.");
}

void test2() {
	int voltage;
	int pings;
	int lights;
	int listens;
	//This routine will test the functions of the robot
//	credit();
//	delay(2000);
//robotlaws();
//delay(2000);
	speak("I will run some self tests now. ");
	speak("Test Voltage reading.");
	voltage = volt();
	speak("The current battery voltage is ");
	speakint(voltage);
	speak("volts");
	speak("Test Ultrasonic Test");
	pings = ping();
	speak("Current Distance from closest object is ");
	speakint(pings);
	speak(" inches.");
speak("Test Read Light Sensor");
	lights = light();
	speak("Current light reading is ");
speakint(lights);
	speak("Test Can I hear a Sound? ");
	speak("Please make a sound in the next 20 seconds.");
	listens = listen();
	if (listens == 1) {speak ("I heard a sound."); } else {
		speak("I didn't hear a thing.");
			}
	speak("Test I will sing to you. ");
	singdaisy();
	speak("And one more song. ");
	singhbd();
	rhyme1();
rhyme2();
quote1();
quote2();
quote3();
quote4();
quote5();

	speak("Test LEDS");
	speak("I will toggle all the leds, on and off.");
	delay(500);
	led(0);
	delay(800);
	led(1);
	delay(800);
	led(2);
	delay(800);
	led(3);
	delay(800);
	led(4);
	delay(800);
	led(5);
	delay(800);
	led(6);
	delay(800);
	led(7);
	delay(800);
	led(0);
	delay(800);
	led(1);
	delay(800);
	led(2);
	delay(800);
	led(3);
	delay(800);
	led(4);
	delay(800);
	led(5);
	delay(800);
	led(6);
	delay(800);
	led(7);
	delay(800);
	speak("I will now do a Cyclon pattern with the LEDs 10 times.");
	cylon(10);
	delay(500);

speak("This conculdes my tests, thank you!");

}

void guess() {
	/*
	Guess Number from 0 to 999, Hero will give a higher or lower response, and you'll have 20 tries to guess it.
	Based on a classic high/low game, modified for use on the Hero Jr
	Idea came from Guess published in Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=75
	*/
	
	speak("This is a number guessing Game.  I will think");
	speak("of a number between 0 and 999.  Then you have to guess it.");
	
	int l1 = random(0, 999);
	int g1, readkey, n;
ledup();
	speak("What is your guess");
	readkey = key();
	speakint(readkey);
	
}

void animal() {
	/*
	Guess the Animal you are thinking of.
	Based on Animal page 4 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=4
	*/
	
}

void bagels() {
	/*
	Based on Mastermind, guess the random numbers in the correct order, 3 digit number
	Based on Bagels Page 9 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=9
	*/
	
}

// Blackjack and Acey Ducey - also have the deck shuffling functions that are also written

void blackjack() {
	/*
	Based on Blackjack or 21, Las Vegas Rules
	Based on Blackjack page 18 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=18
	*/
}

void aceyducey() {
	/*
	Based on the card game Acey Ducey
	pretty sure it is also in Basic Computer Games by David Ahl 1978 Creative Computing, 
	don't have any referance for it.
	*/
	
}

void civilwar() {
	/*
	Based on Civil War page 46 Basic Computer Games By David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=46
	*/
}
void combat() {
	/*
	based on Combat page 50 Basic Computer Games By David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=50
	*/
}

void craps() {
	/* based from Craps page 52 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=52
	*/
}

void depthcharge() {
	/* based from Depth Charge page 55 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=55
	*/
	
}

void dice() {
	/*Based on Dice page 57 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=57
	Not exactly a game, this program simulates rolling a pair of dice a large number of times and prints out the frequency
	distribution.  You simply input the number of rolls.  It is interesting to see how many rolls are necessary to approach the theoretical distribution.
	Daniel Freidus wrote this program while in the seventh grade at Harrison Jr-SR High School, Harrison New York
	*/
	speak("Dice. This Game simulates the rolling of a pair of dice.");
	delay(1000);
	speak("You Enter the number of times you want the computer to roll the dice");
	speak(" How many rolls? Zero will exit.");
	int readkey = multikey();
	if (readkey == 0) {speak("Thanks for Playing. "); return;}
	int f[12];
	for (int fcount=0; fcount<12; fcount++) {
		f[fcount] = 0;
	}
	speak("Rolling the Dice.");
	for (int s=1; s<=readkey; s++) {
		int a=random(2,6);
		int b=random(2,6);
		ledup();
		int r=(a+b)-1;
		f[r]=f[r]+1;
		for (int xx=0; xx<9; xx++) {
			led(xx);
			delay(50);
		}
	}
	speak("Totals ");
	speak("Total Dice Roles: ");
	speakint(readkey);
	for (int s=1; s<12; s++){
		speak("Number: ");
		speakint(s+1);
		speak("Rolled: ");
		speakint(f[s]);
		speak("times.");
		
	}
	}
//done needs tested Apr 17, 2015	


void furtrader() {
	/*Based on Fur Trader page 69 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=69
	*/
}

void hammurabi() {
	/*Based on Hammurabi page 78 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=78
	*/
}

void hangman() {
	/*Based on Hangman page 80 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=80
	*/
}

void hello() {
	/*Hello Conversation program based on Hello page 82 - Basic Computer Games by David Ahl 1978 Creative Computing
	http://www.atariarchives.org/basicgames/showpage.php?page=82
	*/
}

void ledmouth() {
	
	digitalWrite(led0, 1);
   	digitalWrite(led1, 1);
   	digitalWrite(led2, 1);
   	digitalWrite(led3, 1);
   	digitalWrite(led4, 1);
   	digitalWrite(led5, 1);
   	digitalWrite(led6, 1);
   	digitalWrite(led7, 1);
	while(Serial1.read() != ':') {
	digitalWrite(led4, 1);
	digitalWrite(led3, 1);
	delay(25);
	digitalWrite(led2, 1);
	digitalWrite(led5, 1);
	delay(125);
	digitalWrite(led1, 1);
	digitalWrite(led6, 1);
	delay(125);
	digitalWrite(led0, 1);
	digitalWrite(led7, 1);
	delay(125);
	digitalWrite(led0, 0);
	digitalWrite(led7, 0);
	delay(125);
	digitalWrite(led1, 0);
	digitalWrite(led6, 0);
	delay(125);
	digitalWrite(led2, 0);
	digitalWrite(led5, 0);
	delay(125);
	digitalWrite(led4, 0);
	digitalWrite(led3, 0);
	delay(25);
	};
digitalWrite(led0, 1);
   	digitalWrite(led1, 1);
   	digitalWrite(led2, 1);
   	digitalWrite(led3, 1);
   	digitalWrite(led4, 1);
   	digitalWrite(led5, 1);
   	digitalWrite(led6, 1);
   	digitalWrite(led7, 1);
	digitalWrite(led0, state0);
	digitalWrite(led1, state1);
   	digitalWrite(led2, state2);
   	digitalWrite(led3, state3);
   	digitalWrite(led4, state4);
   	digitalWrite(led5, state5);
   	digitalWrite(led6, state6);
   	digitalWrite(led7, state7);
   //Serial.println(">");

}

void ledup() {
	digitalWrite(led0, 1);
   digitalWrite(led1, 1);
   digitalWrite(led2, 1);
   digitalWrite(led3, 1);
   digitalWrite(led4, 1);
   digitalWrite(led5, 1);
   digitalWrite(led6, 1);
   digitalWrite(led7, 1);
 
 for (int xx=0; xx<=5; xx++) {  
   digitalWrite(led0, 0);
   delay(10);
   digitalWrite(led1, 0);
   delay(10);
   digitalWrite(led2, 0);
   delay(10);
   digitalWrite(led3, 0);
   delay(10);
   digitalWrite(led4, 0);
   delay(10);
   digitalWrite(led5, 0);
   delay(10);
   digitalWrite(led6, 0);
   delay(10);
   digitalWrite(led7, 0);
   delay(10);
   digitalWrite(led7, 1);
   delay(10);
   digitalWrite(led6, 1);
   delay(10);
   digitalWrite(led5, 1);
   delay(10);
   digitalWrite(led4, 1);
   delay(10);
   digitalWrite(led3, 1);
   delay(10);
   digitalWrite(led2, 1);
   delay(10);
   digitalWrite(led1, 1);
   delay(10);
   digitalWrite(led0, 1);
   delay(10);
 }
 
 digitalWrite(led0, state0);
   digitalWrite(led1, state1);
   digitalWrite(led2, state2);
   digitalWrite(led3, state3);
   digitalWrite(led4, state4);
   digitalWrite(led5, state5);
   digitalWrite(led6, state6);
   digitalWrite(led7, state7);
  // Serial.println(">");
   
}

/*
Card Shuffle 

Hero Jr will learn how to play Acey Deucey, and Black Jack (21)
This was just the start of having one routine, randomly shuffle a deck of 52 cards,
It first shuffles all the suite cards, then combines, and shuffles the whole deck. Seems to be working
fairly well, but I always end up with the ACE of Spades as the last card.
Cards are all numbered from 2 to 14, with 11, 12, 13 being Jack, Queen, King and 14 being the Ace.
this will make it easy to figure out if a card is higher or lower then a card showing on the table, with the
possable expection of the Ace, as in some games it can either be high or low (wild-card).
Suites are dealt with in a different array, the deck array, and decksuite array should always be used together
when shuffling, passing cards out, exchanging cards, passing cards to other players, etc
decksuite will have one of the following values set as a "CHAR" 'H', 'S', 'D', 'C' for hearts, spades, diamonds and clubs
This is just for shuffling, and other arrays will be needed for the players hands, and to track what has been removed from the deck

New Functions and usage:
shufflecards() - shuffles each suite without shuffling the deck.
resetdeck() - clears deck, no cards are in the deck when this is done - use to start a new game.
shuffledeck() - calls resetdeck(), shufflecards(), filldeck() - and shuffles all 52 cards in deck.
filldeck() - called from shuffledeck() it loads the suites to the deck.
*/

/* Un-need code for Hero Jr, but example of how to display suite names, and face cards
for (int a=0; a<52; a++){
		
		Serial.print("Card Number: ");
		Serial.print(a+1, DEC);
		Serial.print(": ");
		if (deck[a] == 11) {Serial.print("Jack");}
		if (deck[a] == 12) {Serial.print("Queen");}
		if (deck[a] == 13) {Serial.print("King");}
		if (deck[a] == 14) {Serial.print("Ace");}
		if (deck[a] <= 10) {Serial.print(deck[a]);}
		Serial.print(" of ");
		if (decksuite[a] == 'S') {Serial.println("Spades");}
		if (decksuite[a] == 'C') {Serial.println("Clubs");}
		if (decksuite[a] == 'D') {Serial.println("Diamonds");}
		if (decksuite[a] == 'H') {Serial.println("Hearts");}
		
	}
	*/
	
	void shufflecards() {
	for (int ac=0; ac<13; ac++){
		r = random(ac, 12);
		int temp = cards[ac];
		cards[ac] = cards[r];
		cards[r] = temp;
		hearts[ac] = cards[ac];
			}
for (int ac=0; ac<13; ac++){
		r = random(ac, 12);
		int temp = cards[ac];
		cards[ac] = cards[r];
		cards[r] = temp;
		spades[ac] = cards[ac];
			}
			for (int ac=0; ac<13; ac++){
		r = random(ac, 12);
		int temp = cards[ac];
		cards[ac] = cards[r];
		cards[r] = temp;
		clubs[ac] = cards[ac];
			}
			for (int ac=0; ac<13; ac++){
		r = random(ac, 12);
		int temp = cards[ac];
		cards[ac] = cards[r];
		cards[r] = temp;
		diamonds[ac] = cards[ac];
			}
return;
}

void resetdeck() {
	for (int ac=0; ac<52; ac++) {
		deck[ac] = 0;
	decksuite[ac] = '0';
		}
return;
}

void filldeck() {

		for (int ac=0; ac<13; ac++) {
			deck[ac] = hearts[ac];
			decksuite[ac] = 'H';

			deck[ac+13] = clubs[ac];
			decksuite[ac+13] = 'C';

			deck[ac+26] = diamonds[ac];
			decksuite[ac+26] = 'D';

			deck[ac+39] = spades[ac];
			decksuite[ac+39] = 'S';

		}

}

void shuffledeck() {
	resetdeck();
	shufflecards();
	filldeck();
	
	for (int aa=0; aa<52; aa++){
		r = random(aa, 51);
		int temp = deck[aa];
		char tempsuite = decksuite[aa];
		deck[aa] = deck[r];
		decksuite[aa] = decksuite[r];
		deck[r] = temp;
		decksuite[r] = tempsuite;
	}
return;
}

void play() {
	speak("Welcome to Hero Junior Games, please select a game from the list. ");
	speak("Hit Zero for Guess the Number. ");
	speak("Hit One for Animals, I will try to guess the animal you are thinking of.");
	speak("hit two for Bagels ");
	speak("hit three for Blackjack  also known as 21.");
	speak("hit four for  Acey Ducey card game.");
	speak("hit five for Civil War");
	speak("hit six for combat");
	speak("hit seven for craps");
	speak("hit eight for depth charge");
	speak("hit nine for Dice");
	speak("Hit A for Fur Trader");
	speak("Hit B for Hammurabi");
	speak("Hit C for Hang man");
	speak("Hit E to Exit back to main.");
	int keypress = key();
	
	if (keypress == 0) {guess();}
	if (keypress == 1) {animal();}
	if (keypress == 2) {bagels();}
	if (keypress == 3) {blackjack();}
	if (keypress == 4) {aceyducey();}
	if (keypress == 5) {civilwar();}
	if (keypress == 6) {combat();}
	if (keypress == 7) {craps();}
	if (keypress == 8) {depthcharge();}
	if (keypress == 9) {dice();}
	if (keypress == 10) {furtrader();}
	if (keypress == 11) {hammurabi();}
	if (keypress == 12) {hangman();}
	
	speak("Thanks for playing...");
	
}

void keytest() {
	int readkey = key();
	speak("You Pressed ");
if (readkey == 10) {speak("A");}
if (readkey == 11) {speak("B");}
if (readkey == 12) {speak("C");}
if (readkey == 13) {speak("D");}
if (readkey == 14) {speak("E");}
if (readkey == 15) {speak("F");}
if (readkey < 10) {speakint(readkey);}
	//Serial.print("Keypressed: ");
	//Serial.println(readkey);

}

int multikey() {
	int digitone = 0;
	int digittwo = 0;
	int digitthree = 0;
	int digitfour = 0;
	int finaldigit = 0;
	digitone = key();
	if (digitone == 15) {return(digitone);} else {
	led(0);
	}
	digittwo = key();
	if (digittwo == 15) {
		finaldigit = digitone;
		led(0);
		return(finaldigit);
	} else { 
		led(1);
	}
	digitthree = key();
	if (digitthree == 15) {
		finaldigit = (digitone * 10) + (digittwo);
		led(0);
		led(1);
		return(finaldigit);
	} else {
		led(2);
	}
	digitfour = key();
	if (digitfour == 15) {
		finaldigit = (digitone * 100) + (digittwo * 10) + (digitthree);
		led(0);
		led(1);
		led(2);
		return(finaldigit);
	} else {
		finaldigit = (digitone * 1000) + (digittwo * 100) + (digitthree *10) + (digitfour);
		led(0);
		led(1);
		led(2);
		return(finaldigit);
	}
}

void starwarsplay() {
	
	int keypress = key();
	
	if (keypress != 14) {
		//play random mp3 file
		starwarsplay();}
		return;
}
