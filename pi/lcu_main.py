# lcu_main.py
# Prism Challenge -- Laser Control Unit (LCU)
# Built in Sacramento by Rocket Department, Inc
#
# Main control program for Prism Challenge Raspberry Pi
# Emma Fletcher
# 05.13.2015

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)

arduinoInput = 20
GPIO.setup(arduinoInput, GPIO.IN)

def main():
	print("Hello Laser world :)")

	while(1):
		val = GPIO.input(arduinoInput)
		print(val)

if __name__ == "__main__":
	main()