#include <SPI.h>
#include <Servo.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//Radio definitions
#define RF_SETUP 0x17 //What is this?
#define MAX_PAYLOAD_SIZE 32 //Maximum message size to receive
#define CHANNEL 0x46
#define TIMEOUT 75

//Pin definitions
#define CE_PIN 9
#define CSN_PIN 10
#define LS_PIN 3

//Radio global vars
RF24 radio(CE_PIN, CSN_PIN); //Set up nRF24L01 radio on SPI pin for CE, CSN
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0C2LL }; //Addresses to send/receive
char receivePayload[MAX_PAYLOAD_SIZE]; //Payload we are reading into
bool timedOut = false;

//Servo global vars
Servo lightswitch;
bool state; //true = ON, false = OFF

void setup(void)
{
  Serial.begin(57600);

  printf_begin();
  printf("Testing printf\n\r");

  radio.begin();
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads(); //Enable this seems to work better
  radio.setDataRate(RF24_1MBPS); //1 MBPS data rate
  radio.setPALevel(RF24_PA_MIN); //Minimum power since I'm working in < 10m
  radio.setChannel(CHANNEL); //Channel 70. 0 <= channel < 127
  radio.setRetries(15,15);
  radio.openReadingPipe(1, pipes[1]);

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  radio.startListening();
  
  delay(1000);
}

void loop(void) {
  uint64_t begin_recv = millis();
  while (radio.available() && !timedOut) {
    uint8_t len = radio.getDynamicPayloadSize();
    radio.read(receivePayload, len);
    receivePayload[len] = 0;

    printf("inBuffer: %s\n\r", receivePayload);
    if (!strcmp("LIGHT_SWITCH_ON", receivePayload)) {
      lightSwitchOn();
    } else if (!strcmp("LIGHT_SWITCH_OFF", receivePayload)) {
      lightSwitchOff();
    }

    if (millis() - begin_recv > TIMEOUT) {
      Serial.println("Timeout!");
      timedOut = true;
    }

    delay(10);
  }

  delay(250);
} //


void lightSwitchOn() {
  lightswitch.write(180);
  state = true;
}

void lightSwitchOff() {
  lightswitch.write(40);
  state = false;
}
