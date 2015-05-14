# lcu_main.py
# Prism Challenge -- Laser Control Unit (LCU)
# Built in Sacramento by Rocket Department, Inc
#
# Main control program for Prism Challenge Raspberry Pi
# Emma Fletcher
# 05.13.2015

from time import sleep
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

inputGameStart = 20
inputLaserTripped = 21

GPIO.setup(inputGameStart, GPIO.IN)
GPIO.setup(inputLaserTripped, GPIO.IN)

def main():
	print("Hello Laser world :)")

	lastGameStartVal = 0
	lastLaserTrippedVal = 0

	while True:

		# read arduino inputs
		gameStartVal = GPIO.input(inputGameStart)
		laserTrippedVal = GPIO.input(inputLaserTripped)

		# falling edge state change from held button to released
		if lastGameStartVal and not gameStartVal:
			print("Game Started!")

		# rising edge state changed from held button to released
		if not lastLaserTrippedVal and laserTrippedVal:
			print("Laser Tripped!")
			sleep(0.5)

		lastGameStartVal = gameStartVal
		lastLaserTrippedVal = laserTrippedVal


if __name__ == "__main__":
	main()