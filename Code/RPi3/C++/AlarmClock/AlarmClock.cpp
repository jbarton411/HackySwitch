#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>

//Radio definitions
#define MAX_PAYLOAD_SIZE 32
#define CHANNEL 0x46


//
// Hardware configuration
//

// CE Pin, CSN Pin, SPI Speed
// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 1Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_26, BCM2835_SPI_SPEED_1MHZ);
// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);
// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

const uint64_t addresses[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0C2LL };

void setup(void);

int main(int argc, char** argv) {
	setup();
}



void setup(void) {
	radio.begin();
	radio.enableDynamicPayloads();
	radio.setDataRate(RF24_1MBPS);
	radio.setPALevel(RF24_PA_MIN);
	radio.setChannel(CHANNEL);
	radio.setRetries(15, 15);x
	radio.openWritingPipe(pipes[1]);
	radio.printDetails();
}
