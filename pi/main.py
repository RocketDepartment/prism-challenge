# main class for prism challenge game
import RPi.GPIO as GPIO
import subprocess
import serial
from time import *
from datetime import *

import MySQLdb

db = MySQLdb.connect(host="",
		     user="",
		     passwd="",
		     db="")

cur = db.cursor();

GPIO.setmode(GPIO.BCM)

# start button
startButton1 = 7
GPIO.setup(startButton1, GPIO.IN)

startButton2 = 11
GPIO.setup(startButton2, GPIO.IN)

# laser trip
laserTrip = 23
GPIO.setup(laserTrip, GPIO.IN)

# start line laser trip
# startLineLaserTrip = 8
# GPIO.setup(startLineLaserTrip, GPIO.IN)


def main():

	gameMode = False
	
	# set serial comm port, not pretty fix this later
	try:
		ser = serial.Serial('/dev/ttyACM0', 9600)
	except:
		try:
			ser = serial.Serial('/dev/ttyACM1', 9600)
		except:
			ser = None

	while True:

		# check for start button event
		startButtonState1 = GPIO.input(startButton1)
		startButtonState2 = GPIO.input(startButton2)

		if startButtonState1 == True or startButtonState2 == True:
			gameMode = True;

			print 'Start Button Pressed'
			ser.write('2')
			sleep(0.5)

			print 'Play audio file'
			if startButtonState1:
				print 'Start Audio 1'
				audio_completion = subprocess.call(["omxplayer", "intro.mp3"])
			if startButtonState2:
				print 'Start Audio 2'
				audio_completion = subprocess.call(["omxplayer", "penalty-beep.mp3"])

			print audio_completion

			#do start game stuff
			print 'Send message to arduino to start game'
			ser.write('1')
			print 'Recording Start Time'
			start = datetime.now()
			penaltyCount = 0;

			print 'GO!'
			# while we're in game mode keep checking for laser trips

			while gameMode:
				laserTripState = GPIO.input(laserTrip)
				if laserTripState == True:
					print 'Penalty!!'
					print 'Play audio file'
					audio_completion = subprocess.call(["omxplayer", "penalty-beep.mp3"])
					print audio_completion
					penaltyCount = penaltyCount + 1

				endButtonState1 = GPIO.input(startButton1)
				sleep(.2)
				endButtonState2 = GPIO.input(startButton1)

				
				if (endButtonState1 == endButtonState2) and (endButtonState1 == True):
					finish = datetime.now()
					print 'Mission Complete'
					gameMode = False;

			# do end of game stuff
			ser.write('2')
			print ""
			print "Start Time: ", start
			print "Finish Time: ", finish

			elapsedTime = finish - start
			print "Elapsed Time: ", elapsedTime

			secsTime = elapsedTime.total_seconds()
			print "Time in Seconds: ", secsTime

			millsTime = secsTime * 1000

			print ""
			print "Penalty Count: ", penaltyCount

			totalTime = millsTime + (penaltyCount * 15 *1000)
			print "Total Time: ", totalTime

			ms = int(totalTime)

			secs = (ms / 1000) % 60
			mins = (ms / (1000 * 60)) % 60
			remainMs = (ms - (secs * 1000)) - (mins * (1000* 60))

			print str(mins) + "m " + str(secs) + "s " + str(remainMs) + "ms" 
			print ""

			cur.execute("INSERT INTO scores (id, time, lasers_hit) VALUES (%s, %s, %s)" % (0, totalTime, penaltyCount) )
			db.commit()

			sleep(5)

if __name__ == "__main__":
	main()
