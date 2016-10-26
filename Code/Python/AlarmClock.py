# Connecting the Raspberry Pi to the NRF24L01+

# NRF24L01+			Raspberry Pi
#   VCC --------------------------- 3.3V	(Pin 01)
#   GND --------------------------- GND		(Pin 06)
#   CSN --------------------------- GPIO	(Pin 24)
#   CE  --------------------------- GPIO17	(Pin 11)
#  MOSI --------------------------- GPIO10	(Pin 19)
#  MISO --------------------------- GPIO9	(Pin 21)
#  SCK ---------------------------- GPIO11	(Pin CLK)
#   IRQ - NOT CONNECTED

import time
import os
import sys
import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import spidev

DEBUG = 1


## ALARM TIME SETUP ##
sa = sys.argv
lsa = len(sys.argv)
if lsa != 2:
    print("Usage: AlarmClock.py <time>")
    sys.exit(1)
wake_up_time = sa[1]
try:
    hour = int(wake_up_time[:2])
    minute = int(wake_up_time[2:4])
        
    if hour < 0 or hour > 23:
        raise ValueError('Hour must be between 0-23')
    if minute < 0 or minute > 59:
        raise ValueError('Minute must be between 0-59')
except ValueError as e:
    print(e.args)


## GPIO SETUP ##
GPIO.setmode(GPIO.BCM)
pipes = [[0xe7, 0xe7, 0xe7, 0xe7, 0xe7], [0xc2, 0xc2, 0xc2, 0xc2, 0xc2]]
radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)
radio.setPayloadSize(32)
radio.setChannel(0x60)
radio.setDataRate(NRF24.BR_2MBPS)
radio.setPALevel(NRF24.PA_MIN)
#radio.enableDynamicPayload()
radio.enableAckPayload()
radio.openWritingPipe(pipes[0])
radio.printDetails()

#
'''
while True:
	now = time.localtime()
	if hour == now.tm_hour and minute == now.tm_min:
        continueSending = True
        while continueSending:
            radio.write(list("LIGHT_SWITCH_ON"))
            if radio.isAckPayloadAvailable():
                returnedPL = []
                radio.read(returnedPL, radio.getDynamicPayloadSize())
                if int(returnedPL[0]) != 1:
                    continue
                else:
                    continueSending = False
            print("Light is not on, resending payload")
                
                break #breaks out of while 1
	
	time.sleep(61 - now.tm_sec)
'''

counter = 0
while True:
    if counter % 2 == 0:
        print("LIGHT_SWITCH_ON")
        radio.write(list("LIGHT_SWITCH_ON"))
    else:
        print("LIGHT_SWITCH_OFF")
        radio.write(list("LIGHT_SWITCH_OFF"))
    counter += 1
    time.sleep(1)

print("Exited successfully")
