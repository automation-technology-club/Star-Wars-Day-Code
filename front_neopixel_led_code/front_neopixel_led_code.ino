#include <Adafruit_NeoPixel.h>

int PIN = 3;
int totalLEDs = 16;
int ledFadeTime = 5;

int r;
int r1;
int b;
int b1;

int isOn = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(totalLEDs, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
//	delay(5000);
  strip.begin();
  strip.setBrightness(25);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
	r = random(0, 16);
	b = random(0, 16);
	r1 = random(0, 16);
	b1 = random(0, 16);
//	if (random(0,6) > 1) {
	strip.setPixelColor(r, 0, 255, 0);
//		}
//	if (random(0,6) > 1) {
	strip.setPixelColor(r1, 0, 0, 255);
//		}
//	if (random(0,6) > 1) {
	strip.setPixelColor(b, 0, 0, 255);
//		}
//	if (random(0,6) >1) {
	strip.setPixelColor(b1, 0, 0, 255);
//	}	
		
	strip.show();
	delay(200);
	strip.setPixelColor(r, 0, 0, 0);
	strip.setPixelColor(r1, 0, 0, 0);
	strip.setPixelColor(b, 0, 0, 0);
	strip.setPixelColor(b1, 0, 0, 0);
	strip.show();
}

