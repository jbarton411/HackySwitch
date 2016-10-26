#include <Servo.h>

Servo lightSwitch;
uint8_t pos = 90; // 0 <= x <= 180

bool incr = true;

void setup() {
  // put your setup code here, to run once:
  lightSwitch.attach(3);
  Serial.begin(9600);
  delay(5000);
}

int counter = 1;

void loop() {
  if (counter % 2 == 0) {
    pos = 180;
    lightSwitch.write(pos);
  } else {
    pos = 40;
    lightSwitch.write(pos);
  }
Serial.println(pos);
  
  counter++;
  
  delay(5000);
}
