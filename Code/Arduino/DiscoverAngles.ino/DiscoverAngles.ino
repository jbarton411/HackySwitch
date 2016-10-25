#include <Servo.h>

Servo lightSwitch;
uint8_t pos = 90; // 0 <= x <= 180

bool incr = true;

void setup() {
  // put your setup code here, to run once:
  lightSwitch.attach(3);
  lightSwitch.write(pos);

  Serial.begin(9600);
  
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSwitch.write(pos);
  Serial.write(pos);
  
  if (incr) {
    pos++;
  } else {
    pos--;
  }
  
  if (pos <= 0 || pos >= 180) {
    incr = !incr;
  }

  delay(1000);
}
