/*
 *prism.ino
 *Prism Challenge -- Laser Control Unit (LCU)
 *Built in Sacramento by Rocket Department, Inc
 *
 *Main control program for Prism Challenge Laser Maze
 *Emma Fletcher
 *05.09.2015
 */


#define NUM_LASERS 4
#define LIGHT_LEVEL 350

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

// Declar global variables for the game
Laser lasers[NUM_LASERS];
bool gameMode = true;
bool laserTripped = false;
bool laserStartTripped = false;

int gameModePin = 52;
int gameModeButton = 48;
int laserTrippedPin = 50;

// Functions defined in indicator.ino
void updateIndicators( Laser laserArr[], int n );

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
  
int pins[] = { 9, 8, 7, 6 };
int sensors[] = { A0, A1, A2, A3 };
int indicators[] = { 22, 24, 26, 28 };


// the setup routine runs once when you press reset:
void setup() {    
  Serial.begin(9600);
  
  pinMode(gameModePin, OUTPUT);
  pinMode(gameModeButton, INPUT);  
  pinMode(laserTrippedPin, OUTPUT); 
  
  
  initializeLasers( lasers, pins, sensors, indicators, NUM_LASERS ); 
  
}



// the loop routine runs over and over again forever:
void loop() {
  
  int val = digitalRead(gameModeButton);
  Serial.println(val);
  
  if( gameMode ){
    digitalWrite(gameModePin, HIGH);
  } else {
    digitalWrite(gameModePin, LOW);
  }
  
  readSensors( lasers, NUM_LASERS );
  updateIndicators( lasers, NUM_LASERS );

}
