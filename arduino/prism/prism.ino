/*
 *prism.ino
 *Prism Challenge -- Laser Control Unit (LCU)
 *Built in Sacramento by Rocket Department, Inc
 *
 *Main control program for Prism Challenge Laser Maze
 *Emma Fletcher
 *05.09.2015
 */


#define NUM_LASERS 3

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

Laser lasers[NUM_LASERS];

void updateLasers( Laser laserArr[], int n );
void initializeLasers( Laser laserArr[], int pins[], int sensors[], int indicators[], int n );
void blinkLasers( Laser laserArr[], int n, int times, int blinkSpeed);
void fadeLasers( Laser laserArr[], int n, int times, int fadeSpeed);
void blinkLaser( Laser l, int times, int blinkSpeed );
void fadeLaser( Laser l, int times, int fadeSpeed );
  
int pins[] = { 9, 8, 7 };
int sensors[] = { A0, A1, A2 };
int indicators[] = { 22, 24, 26 };


// the setup routine runs once when you press reset:
void setup() {    
  Serial.begin(9600);
  
  initializeLasers( lasers, pins, sensors, indicators, NUM_LASERS ); 
  
}



// the loop routine runs over and over again forever:
void loop() {
  
  blinkLasers(lasers, NUM_LASERS, 3, 150);
  delay(500);  
  blinkLaser( lasers[0], 2, 150 );
  delay(500);
  blinkLaser( lasers[1], 2, 150 );
  delay(500);
  blinkLaser( lasers[2], 2, 150 );
  delay(500);
  
  fadeLasers(lasers, NUM_LASERS, 3, 15);
  delay(500);
  fadeLaser( lasers[0], 2, 15 );
  delay(500);
  fadeLaser( lasers[1], 2, 15 );
  delay(500);
  fadeLaser( lasers[2], 2, 15 );
  delay(500);
  
}
