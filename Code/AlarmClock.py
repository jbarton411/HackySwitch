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

DEBUG = 1

sa = sys.argv
lsa = len(sys.argv)

print sa[1]

if lsa != 2:
	print "Usage: AlarmClock.py <time>"
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
	print e.args

while True:
	now = time.localtime()
	if hour == now.tm_hour and minute == now.tm_min:
		print "WAKE TF UP!!!"
		break
	
	time.sleep(61 - now.tm_sec)

print "Exited successfully"
