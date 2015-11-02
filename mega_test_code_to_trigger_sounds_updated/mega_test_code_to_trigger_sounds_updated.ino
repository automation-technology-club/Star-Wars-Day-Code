
int song;
int isplaying;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);
  
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

while(digitalRead(25));  
  song = 0;
  Serial3.write(song);
    Serial.println("Welcome to Star Wars Day....");
while(digitalRead(23)); 
Serial1.print("Welcome to Star Wars Day\n");

//  isplaying=Serial1.read();
//  while(isplaying == 1){
//    isplaying=Serial1.read();
//  }
  //areyouplaying();
  
  delay(500);
  while(digitalRead(25));
  
  song = 1;
  Serial3.write(song);
  while(digitalRead(23));
  Serial1.print("Starting droid maintance mode.\n");
  Serial.println("Droid Maintaince testing....");
  while(digitalRead(23));
  Serial.println("Rebel Music should be playing for this routine.");
  Serial1.print("Battery Voltage Test....\n");
  Serial.println("Battery Voltage Test....");
  delay(7000); //probably longer than test takes
  while(digitalRead(23));
  Serial.println("Ultrasonic Testing.....");
  Serial1.print("Ultrasonic testing....\n");
  delay(7000); //probably longer than test takes
  while(digitalRead(23));
  //Serial.println("Sound Sensor Testing.... will fail, too much noise");
  Serial1.print("Testing Drive Motor....\n");
    Serial.println("Drive motor Testing....");
    delay(30000); //about a minute and half
  while(digitalRead(23));
  Serial.println("Test L E Ds");
  Serial1.print("Testing L.E.Ds.\n");
  delay(7000); //probably longer than it takes
  while(digitalRead(23));
  Serial1.print("Cylon L E D Testing.\n");
    Serial.println("cylon LED testing...");
  delay(7000); //don't know
  while(digitalRead(23));
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  
  delay(500);
  while(digitalRead(25));
  
  Serial1.print("I am a Hero Junior Robot, and one of my favorite movies\n");
  Serial.println("I am Hero Junior Robot, and one of my favorite movies");
    while(digitalRead(23));
  Serial1.print("is Star Wars,  I wish I could fight against the empire.\n ");
  Serial.println("is Star Wars,   I wish I could fight against the empire.");
    while(digitalRead(23));
    song = 2;
  Serial3.write(song);
  while(digitalRead(25));
  //Serial3.print("the Empire, alongside my friends\n");
  //Serial.println("the Empire alongside my friends.");
  //while(digitalRead(25));
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  //delay(500);
  while(digitalRead(25));
  delay(500);
  while(digitalRead(23));
    song = 3;
  Serial3.write(song);
  Serial1.print("with my friends C 3 P O and R 2 D 2\n");
  Serial.println("with my friends C 3 P O and R 2 D 2");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(4000);
  while(digitalRead(25));
  while(digitalRead(23));
  Serial1.print("But I must admit,  I am a little afraid of\n");
  Serial.println("But I must admit..... ");
  Serial.println("I am a little afraid of......");
  delay(500);
  song = 4;
  Serial3.write(song);
  //backup robot drive backward a little bit
  while(digitalRead(23));
  Serial1.print("Darth Vader...\n");
  Serial.println("Darth Vader....");
   //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(25));
  while(digitalRead(23));
   //move robot forward a little bit
   Serial1.print("Where's my Blaster\n ");
  Serial.println("Where's my Blaster.....");
  song = 5;
  Serial3.write(song);
  //blaster LEDs
  while(digitalRead(23));
  Serial1.print("Did I get him?   Oh I think I just scared him off...\n");
  Serial.println("Did I get him?   OH I think I just scared him off....");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(25));
  
  delay(4000);
  song = 6;
  Serial3.write(song);
  while(digitalRead(23));
  Serial1.print("Look it's The Cantina Bar - I wish Droids where alound in there...\n");
  Serial.println("Look it's The Catina Bar - I wish Droids where aloud in there....");
  while(digitalRead(23));
  Serial1.print("I would do my Droid Dancing....\n");
  Serial.println("I'd do my Droid Dancing.....");
  //dance routine....motors, cyclon leds, etc.
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(25));
  song = 7;
  Serial3.write(song);
    Serial.println("May the Force Be With You....");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  //areyouplaying();
  delay(500);
  while(digitalRead(25));
  while(digitalRead(23));
  Serial1.print("May The Force Be with you.  Hit any key for random sounds.\n");
  while(digitalRead(23));
  Serial1.print("or the E to exit and start over.\n");
  Serial.println("Random Star Wars Sounds From Keypad");
  delay(30000);
}
