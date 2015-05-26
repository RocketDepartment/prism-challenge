# lcu_main.py
# Prism Challenge -- Laser Control Unit (LCU)
# Built in Sacramento by Rocket Department, Inc
#
# Main control program for Prism Challenge Raspberry Pi
# Emma Fletcher
# 05.13.2015

from time import sleep

import datetime
import math
import RPi.GPIO as GPIO

from db_connect import create_connection

db = create_connection()
cur = db.cursor()

GPIO.setmode(GPIO.BCM)

input_game_start = 20
input_laser_tripped = 21

GPIO.setup(input_game_start, GPIO.IN)
GPIO.setup(input_laser_tripped, GPIO.IN)

class Game:

	def __init__(self):
		self.start_time = datetime.datetime.now()
		self.end_time = None
		self.total_time = None
		self.lasers_hit = 0
		self.score = None

	def __str__(self):
		ret_str = ""
		
		# build up return string
		ret_str += ":: Start Time: "
		ret_str += str(self.start_time)
		ret_str += "\n:: End Time: "
		ret_str += str(self.end_time)
		ret_str += "\n:: Elapsed Time: "
		ret_str += str(self.total_time)
		ret_str += "\n:: Lasers Hit: "
		ret_str += str(self.lasers_hit)
		ret_str += "\n:: Score: "
		ret_str += str(self.score)
		
		return ret_str

	def calculateScore(self):
		# find total time
		elapsed_time = self.end_time - self.start_time
		elapsed_time = elapsed_time.total_seconds()

		self.total_time = math.floor(elapsed_time*100)/100

		# calculte the score with penalties
		score = self.total_time + (self.lasers_hit * 10)

		# retunr the score
		return score

def main():
	print("Laser Control Unit Powering On...")

	# track if we're in a game or not
	IN_GAME = False

	# signals from the arduino
	last_game_start_val = 0
	last_laser_tripped_val = 0

	current_game = None

	# main loop for laser control unit
	while True:

		# read arduino inputs
		game_start_val = GPIO.input(input_game_start)
		laser_tripped_val = GPIO.input(input_laser_tripped)

		# print game_start_val
		# print laser_tripped_val
		# sleep(0.5)

		# falling edge state change from held button to released
		if last_game_start_val and not game_start_val:
			
			# if we're in a game the game is over
			# otherwise start a new game
			if IN_GAME:

				# record the finish of the game
				current_game.end_time = datetime.datetime.now()

				# calculate the score
				current_game.score = current_game.calculateScore()
				
				# we've finished the game
				IN_GAME = False
				

				print("Game Complete.")
				print current_game

				cur.execute("""UPDATE scores 
							   SET lasers_hit=%s, time=%s, end_time=%s 
							   WHERE start_time=%s
							""", (current_game.lasers_hit, current_game.score, current_game.end_time, current_game.start_time))
				db.commit()

			else:
				IN_GAME = True
				current_game = Game()
				print("Game Started!")

				cur.execute("INSERT INTO scores (start_time) VALUES ('%s')" % (current_game.start_time))
				db.commit()

		# rising edge state changed from held button to released
		if not last_laser_tripped_val and laser_tripped_val and IN_GAME:

			# add 1 to number of lasers hit 
			current_game.lasers_hit = current_game.lasers_hit + 1

			cur.execute("""UPDATE scores 
							SET lasers_hit=%s 
							WHERE start_time=%s
						""", (current_game.lasers_hit, current_game.start_time))
			db.commit()
			
			print("Laser Tripped!")
			sleep(0.5)

		last_game_start_val = game_start_val
		last_laser_tripped_val = laser_tripped_val


if __name__ == "__main__":
	main()