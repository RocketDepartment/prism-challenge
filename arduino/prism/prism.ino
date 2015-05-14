/*
 *prism.ino
 *Prism Challenge -- Laser Control Unit (LCU)
 *Built in Sacramento by Rocket Department, Inc
 *
 *Main control program for Prism Challenge Laser Maze
 *Emma Fletcher
 *05.09.2015
 */

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include <Wire.h>
#include <SimpleTimer.h>

#define NUM_LASERS 3
#define LIGHT_LEVEL 225

/* structure for lasers
 * pin - the pin the laser is connected to
 * brightness - the brigtness of the laser
 * sensorValue - the value from the light sensor
 * indicator - true for indicator on, false for indicator off
 */
typedef struct _laser {
   int pin;
   int brightness;
   int sensorPin;
   int sensorValue;
   int indicatorPin;
   boolean indicatorValue; 
} Laser;

// Declare global variables for the game
Laser lasers[NUM_LASERS];
bool gameMode = true;
bool laserTripped = false;
bool laserStartTripped = false;

int gameModeButton = 38;
int resetButton = 40;
int trippedButton = 42;

int laserTrippedPin = 52;
int startGamePin = 50;
int gameModeIndicator = 44;

int resetButtonLight = 46;
int trippedButtonLight = 48;

// Functions defined in button.ino
void readButtons();
void reset();

// Functions defined in indicator.ino
void updateIndicators( Laser laserArr[], int n );
void reportStatus();

// Functions defined in laser.ino
void updateLasers( Laser laserArr[], int n );
void initializeLasers( Laser laserArr[], int pins[], int sensors[], int indicators[], int n );
void blinkLasers( Laser laserArr[], int n, int times, int blinkSpeed);
void fadeLasers( Laser laserArr[], int n, int times, int fadeSpeed);
void blinkLaser( Laser l, int times, int blinkSpeed );
void fadeLaser( Laser l, int times, int fadeSpeed );
void testLasers( Laser laserArr[], int n );

// Functions defined in sensor.ino
void readSensors( Laser laserArr[], int n );
  
int pins[] = { 9, 8, 7 };
int sensors[] = { A0, A1, A2 };
int indicators[] = { 22, 24, 26 };

// the timer object
SimpleTimer timer;

Adafruit_7segment matrix = Adafruit_7segment();


// the setup routine runs once when you press reset:
void setup() {
  timer.setInterval(100, updateTimer);  
  Serial.begin(9600);
  matrix.begin(0x70); 
 
  pinMode(gameModeButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(trippedButton, INPUT_PULLUP); 
  
  pinMode(laserTrippedPin, OUTPUT);
  pinMode(startGamePin, OUTPUT);
  pinMode(gameModeIndicator, OUTPUT);
  pinMode(resetButtonLight, OUTPUT);
  pinMode(trippedButtonLight, OUTPUT);
  
  digitalWrite(startGamePin, LOW);
  
  digitalWrite(resetButtonLight, HIGH);
  digitalWrite(trippedButtonLight, HIGH);
  
  initializeLasers( lasers, pins, sensors, indicators, NUM_LASERS ); 
  
}



// the loop routine runs over and over again forever:
void loop() {
  timer.run();
  
  //readButtons();
  readSensors( lasers, NUM_LASERS );
  updateIndicators( lasers, NUM_LASERS );
  //reportStatus();

}
