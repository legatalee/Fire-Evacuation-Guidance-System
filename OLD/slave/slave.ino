#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial HC12(3, 2);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 6, NEO_GRBW + NEO_KHZ800);

String myID = "1";
String myString = "go" + myID;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

  pinMode(4, INPUT);

  strip.setBrightness(50);
  strip.begin();
  strip.show();
}

bool fire = false;

void loop() {
  String input = "";
  while (Serial.available()) {
    input += (char) Serial.read();
    Serial.println(input);
    delay(1);
  }
  while (HC12.available()) {
    input += (char) HC12.read();
    Serial.println(input);
    delay(1);
  }

  fire = !digitalRead(4);
  if (fire) {
    HC12.write(myID.c_str());
    delay(100);
  }
  if (input == myString) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 255, 0, 0);
      strip.show();
      delay(50);
    }
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, 0);
      strip.show();
      delay(50);
    }
    String data = "done" + myID;
    HC12.write(data.c_str());
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
