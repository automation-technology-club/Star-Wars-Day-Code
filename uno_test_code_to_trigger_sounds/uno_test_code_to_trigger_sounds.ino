
int song;
int isplaying;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
    
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
  
  song = 0;
  Serial1.write(song);
    Serial.println("Welcome to Star Wars Day....");
//  isplaying=Serial1.read();
//  while(isplaying == 1){
//    isplaying=Serial1.read();
//  }
  areyouplaying();
  
  delay(500);
  
  song = 1;
  Serial1.write(song);
  Serial.println("Droid Maintaince testing....");
  Serial.println("Rebel Music should be playing for this routine.");
  Serial.println("Battery Voltage Test....");
  Serial.println("Ultrasonic Testing.....");
  Serial.println("Sound Sensor Testing.... will fail, too much noise");
  Serial.println("Drive motor Testing....");
  Serial.println("Test Leds");
  Serial.println("cyclon Led testing...");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  
  delay(500);
  
  Serial.println("I am Hero Junior Robot, and one of my favorite movies");
  Serial.println("is Star Wars,   I wish I could fight against ");
  song = 2;
  Serial1.write(song);
  Serial.println("the Empire alongside my friends.");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  delay(500);
  song = 3;
  Serial1.write(song);
  Serial.println("R 2 D 2 and C 3 P O ");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  delay(500);
  Serial.println("But I must admit..... ");
  Serial.println("I am a little afraid of......");
  song = 4;
  Serial1.write(song);
  //backup robot drive backward a little bit
  Serial.println("Darth Vader....");
   //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  delay(500);
   //move robot forward a little bit
  Serial.println("Where's my Blaster.....");
  song = 5;
  Serial1.write(song);
  //blaster LEDs
  Serial.println("Did I get him?   OH I think I just scared him off....");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  delay(500);
  song = 6;
  Serial1.write(song);
  Serial.println("I wish Droids where aloud in here....");
  
  Serial.println("I'd do my Droid Dancing.....");
  //dance routine....motors, cyclon leds, etc.
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  delay(500);
  song = 7;
  Serial1.write(song);
  Serial.println("May the Force Be With You....");
  //isplaying=Serial1.read();
  //while(isplaying == 1){
  //  isplaying=Serial1.read();
  //}
  areyouplaying();
  delay(500);
  Serial.println("Random Star Wars Sounds From Keypad");
  delay(30000);
}
