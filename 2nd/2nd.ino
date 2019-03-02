#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial HC12(3, 2);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 6, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

  pinMode(4, INPUT);

  strip.setBrightness(50);
  strip.begin();
  strip.show();
}

bool fire = false;
bool check = false;
bool pcheck = true;
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
    check = true;
  } else check = false;
  if (check || input == "2") {
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
    HC12.write("3");
    pcheck = true;
    while (pcheck) {
      String fine = "";
      while (HC12.available()) {
        fine += (char) HC12.read();
        Serial.println(fine);
        delay(1);
      }
      if (fine == "fine3"){
        pcheck = false;
      }
    }
    HC12.write("fine2");
  }
}
