import time
impot os

DEBUG = 1

sa = sys.argv
lsa = len(sys.argv)

print sa[1]

if lsa != 2:
	print "Usage: AlarmClock.py <time>"
	sys.exit(1)

time = sa[1]

try:
	hour = int(time[:2])
	minutes = int(time[2:4])

	

except ValueError:
	

