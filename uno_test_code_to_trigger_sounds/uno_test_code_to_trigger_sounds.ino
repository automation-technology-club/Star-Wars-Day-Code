
int song;
int isplaying;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
pinMode(23, INPUT_PULLUP);
pinMode(25, INPUT_PULLUP);

}

int areyouplaying() {
  Serial1.flush();
  delay(500);
      //while(isplaying) {
        //Serial1.flush();
        if (Serial1.available()) {isplaying = Serial1.read();}
      //Serial.println(isplaying);
    if (isplaying == 0) {return 0;}
      //}
  areyouplaying();
}

void loop() {

while(digitalRead(23));  
  song = 0;
  Serial1.write(song);
    Serial.println("Welcome to Star Wars Day....");
while(digitalRead(25)); 
Serial2.print("Welcome to Star Wars Day\n");

//  isplaying=Serial1.read();
//  while(isplaying == 1){
//    isplaying=Serial1.read();
//  }
  //areyouplaying();
  
  delay(500);
  while(digitalRead(23));
  
  song = 1;
  Serial1.write(song);
  while(digitalRead(25));
  Serial2.print("Starting droid maintance mode.\n");
  Serial.println("Droid Maintaince testing....");
  while(digitalRead(25));
  Serial.println("Rebel Music should be playing for this routine.");
  Serial2.print("Battery Voltage Test....\n");
  Serial.println("Battery Voltage Test....");
  while(digitalRead(25));
  Serial.println("Ultrasonic Testing.....");
  Serial2.print("Ultrasonic testing....\n");
  while(digitalRead(25));
  Serial.println("Sound Sensor Testing.... will fail, too much noise");
  Serial2.print("Testing Drive Motor....\n");
  Serial.println("Drive motor Testing....");
  while(digitalRead(25));
  Serial.println("Test Leds");
  Serial2.print("Testing Leds.\n");
  while(digitalRead(25));
  Serial2.print("Cyclon LED Testing.\n");
  Serial.println("cyclon Led testing...");
  while(digitalRead(25));
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  
  delay(500);
  while(digitalRead(23));
  
  Serial2.print("I am a Hero Junior Robot, and one of my favorite movies\n");
  Serial.println("I am Hero Junior Robot, and one of my favorite movies");
    while(digitalRead(25));
  Serial2.print("is Star Wars,  I wish I could fight against\n ");
  Serial.println("is Star Wars,   I wish I could fight against ");
    song = 2;
  Serial1.write(song);
  while(digitalRead(25));
  Serial2.print("the Empire alongside my friends\n");
  Serial.println("the Empire alongside my friends.");
  
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(23));
  while(digitalRead(25));
    song = 3;
  Serial1.write(song);
  Serial2.print("R 2 D 2 and C 3 P O\n");
  Serial.println("R 2 D 2 and C 3 P O ");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(23));
  while(digitalRead(25));
  Serial2.print("But I must admit,  I am a little afraid of\n");
  Serial.println("But I must admit..... ");
  Serial.println("I am a little afraid of......");
  song = 4;
  Serial1.write(song);
  //backup robot drive backward a little bit
  while(digitalRead(25));
  Serial2.print("Darth Vader...\n");
  Serial.println("Darth Vader....");
   //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(23));
  while(digitalRead(25));
   //move robot forward a little bit
   Serial2.print("Where's my Blaster\n ");
  Serial.println("Where's my Blaster.....");
  song = 5;
  Serial1.write(song);
  //blaster LEDs
  while(digitalRead(25));
  Serial2.print("Did I get him?   Oh I think I just scared him off...\n");
  Serial.println("Did I get him?   OH I think I just scared him off....");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(23));
  
  song = 6;
  Serial1.write(song);
  while(digitalRead(25));
  Serial2.print("Oh The Cantina Bar - I wish Droids where alound in there...\n");
  Serial.println("Oh The Catina Bar - I wish Droids where aloud in there....");
  while(digitalRead(25));
  Serial2.print("I would do my Droid Dancing....\n");
  Serial.println("I'd do my Droid Dancing.....");
  //dance routine....motors, cyclon leds, etc.
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(23));
  song = 7;
  Serial1.write(song);
    Serial.println("May the Force Be With You....");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(23));
  while(digitalRead(25));
  Serial2.print("May The Force Be with you.  Hit any key for random sounds.\n");
  while(digitalRead(25));
  Serial2.print("or the E to exit and start over.\n");
  Serial.println("Random Star Wars Sounds From Keypad");
  delay(30000);
}
