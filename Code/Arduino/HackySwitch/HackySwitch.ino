// Arduino Pin Diagram

/* NRF24L01
 *  # NRF24L01+                Arduino Pro Mini
 *  VCC --------------------------- 3.3V
 *  GND --------------------------- GND
 *  CSN --------------------------- D9
 *  CE  --------------------------- D10
 *  MOSI -------------------------- D11
 *  MISO -------------------------- D12 
 *  SCK --------------------------- D13
 *  IRQ - NOT CONNECTED
 */

#include <SPI.h>
#include <Servo.h>
#include <RF24.h>

//Radio setup
#define MAX_PAYLOAD_SIZE 32 //Maximum message size to receive
RF24 radio(9,10); //Set up the nRF24L01 radio on SPI bus plus pins (CE, CSN)
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL }; //Radio pipe addresses for the 2 nodes to communicate

//Servo setup
Servo lightSwitch;
int pos = 0;

const char* LIGHT_SWITCH_ON = "LIGHT_SWITCH_ON";
const char* LIGHT_SWITCH_OFF = "LIGHT_SWITCH_OFF";

void setup() {
  Serial.begin(57600);
  printf("\nRemote Switch Arduino\n\r");

  //Radio setup
  radio.begin();
  radio.setAutoAck(1);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  radio.printDetails();

  //Servo setup
  lightSwitch.attach(3);
  lightSwitch.write(0);
}

void loop() {
  char payload[MAX_PAYLOAD_SIZE] = "";
  
  if (radio.available()) {
    uint8_t index = 0;
    while(radio.available()) {
      radio.read(&payload[index], sizeof(unsigned char));
      index++;
    }
    payload[index] = '\0';
  }
  
  if (String(payload).equals(LIGHT_SWITCH_ON)) {
    lightSwitchOn();
  } else if (String(payload).equals(LIGHT_SWITCH_OFF)) {
    lightSwitchOff();
  }
}

void lightSwitchOn() {
  lightSwitch.write(0);
}

void lightSwitchOff() {
  lightSwitch.write(180);
}


