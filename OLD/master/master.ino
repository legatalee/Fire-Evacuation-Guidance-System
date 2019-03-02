#include <SoftwareSerial.h>
SoftwareSerial HC12(3, 2);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
}

bool loopcheck = true;

void loop() {
  while (Serial.available()) {
    HC12.write(Serial.read());
  }
  String input = "";
  while (HC12.available()) {
    input += (char) HC12.read();
    Serial.println(input);
    delay(1);
  }
  if (input == "1") {
    loopcheck = true;
    HC12.write("go1");
    String check = "";
    while (loopcheck) {
      Serial.println("looping");
      while (HC12.available()) {
        check += (char) HC12.read();
        Serial.println(check);
        delay(1);
      }
      if (check == "1done1")
        loopcheck = false;
    }
  }
  if (input == "2") {
    HC12.write("go2");
    String check = "";
    while (1) {
      while (HC12.available()) {
        check += (char) HC12.read();
        Serial.println(check);
        delay(1);
      }
      if (check == "2done2")
        break;
    }
  }
  if (input == "3") {
    HC12.write("go3");
    String check = "";
    while (1) {
      while (HC12.available()) {
        check += (char) HC12.read();
        Serial.println(check);
        delay(1);
      }
      if (check == "3done3")
        break;
    }
  }
}
