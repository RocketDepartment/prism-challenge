/*
 *laser.ino
 *File for laser control functions
 *
 *Emma Fletcher
 *05.09.2015
 */

/*
 * initializeLasers( Laser laserArr[], int pins[], int sensors[], int indicators[], int n):
 * Function to initialize all lasers at start of program
 *
 * Parameter 1: Laser laserArr[] - Array of Lasers
 * Parameter 2: int pins[] - Arry of pins lasers are attached to, index value matches
 * index of laserArr index
 * Parameter 3: int sensors[] - Array of pins light sensors are attached to, index value
 * matches index of laserArr index
 * Parameter 4: int indicators[] - Array of pin indicators lights are attached to, index
 * value matches index of laserArr index
 * Parameter 5: int n - number of lasers to initialize
 *
 * Return: Void
 */  
void initializeLasers( Laser laserArr[], int pins[], int sensors[], int indicators[], int n ){
    
  for( int i = 0; i < n; i++ ){
      Laser aLaser;
      aLaser.pin = pins[i];
      aLaser.brightness = 255;
      aLaser.sensorPin = sensors[i];
      aLaser.sensorValue = 0;
      aLaser.indicatorPin = indicators[i];
      aLaser.indicatorValue = HIGH;
      
      pinMode(aLaser.pin, OUTPUT);
      pinMode(aLaser.sensorPin, INPUT);
      pinMode(aLaser.indicatorPin, OUTPUT);
      
      digitalWrite(aLaser.pin, HIGH);
      
      laserArr[i] = aLaser;
    }
    
}

void updateLasers( Laser laserArr[], int n ){
    // loop through each laser
    Serial.println("New Loop");
    for( int i = 0; i < n; i++ ){
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(laserArr[i].pin);
      delay(1000);
    }
}

/*
 * blinkLasers( Laser laserArr[], int n, int times, int fadeSpeed): Function
 * to blink multiple lasers at the same time
 *
 * Parameter 1: Laser laserArr[] - Array of Lasers
 * Parameter 2: int n - number of Lasers in laserArr[]
 * Parameter 3: int times - number of times to fade
 * Parameter 4: int blinkSpeed - delay in milliseconds between blinks
 *
 * Return: Void
 */
void blinkLasers( Laser laserArr[], int n, int times, int blinkSpeed){
  while(times > 0) {
    for( int i = 0; i < n; i++ ){
      digitalWrite(laserArr[i].pin, LOW);
    }
    
    delay(blinkSpeed);
    
    for(int i = 0; i < n; i++ ){
      digitalWrite(laserArr[i].pin, HIGH);
    }
    
    delay(blinkSpeed);
    
    times = times - 1;
  }
  
}

/*
 * fadeLasers( Laser laserArr[], int n, int times, int fadeSpeed): Function
 * to fade multiple lasers at the same time
 *
 * Parameter 1: Laser laserArr[] - Array of Lasers
 * Parameter 2: int n - number of Lasers in laserArr[]
 * Parameter 3: int times - number of times to fade
 * Parameter 4: int fadeSpeed - delay in milliseconds between brightness
 * value change
 *
 * Return: Void
 */
void fadeLasers( Laser laserArr[], int n, int times, int fadeSpeed){
  while(times > 0) {
    
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      // sets the value (range from 0 to 255):
      for( int i = 0; i < n; i++ ){
        if( fadeValue == 255 ){
          delay(250);
        }
        analogWrite(laserArr[i].pin, fadeValue);
      }      
      // wait for 30 milliseconds to see the dimming effect    
      delay(fadeSpeed);                            
    } 
    
    
    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      // sets the value (range from 0 to 255):
      for( int i = 0; i < n; i++ ){
        analogWrite(laserArr[i].pin, fadeValue);
      }      
      // wait for 30 milliseconds to see the dimming effect    
      delay(fadeSpeed);                            
    } 
    
    times = times - 1;
  }
  
}

/*
 * blinkLaser( Laser l, int times, int blinkSpeed ): Function to blink
 * individual laser
 *
 * Parameter 1: Laser l - Laser to blink
 * Parameter 2: int times - number of time to blink
 * Parameter 3: int blinkSpeed - delay in milleseconds between blinks
 *
 * Return: Void
 */
void blinkLaser( Laser l, int times, int blinkSpeed ){
  for( int i = 0; i < times; i++ ){
    digitalWrite(l.pin, LOW);
    delay(blinkSpeed);
    digitalWrite(l.pin, HIGH);
    delay(blinkSpeed);   
  } 
}

/*
 * fadeLaser( Laser l, int times, int fadeSpeed ): Function to fade individual Laser
 *
 * Parameter 1: Laser l - Laser to fade
 * Parameter 2: int times - number of times to fade
 * Parameter 3: int fadeSpeed - delay in milliseconds between brightness value change
 *
 * Return: Void
 */
void fadeLaser( Laser l, int times, int fadeSpeed ){
  for( int i = 0; i < times; i++ ){
    // sets the value (range from 0 to 255):
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
        if( fadeValue == 255 ){
          delay(250);
        }
        analogWrite(l.pin, fadeValue);  
      // wait for 30 milliseconds to see the dimming effect    
      delay(fadeSpeed);                            
    } 
    
    
    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(l.pin, fadeValue);  
      // wait for 30 milliseconds to see the dimming effect    
      delay(fadeSpeed);                            
    }   
  } 
}

/*
 * laserTest( Laser laserArry[], int n ): Function test the functions inside laser.ino. Currently
 * tests blinkLasers(), blinkLaser, fadeLasers, fadeLaser
 *
 * Parameter 1: Laser laserArr[] - Array of Lasers
 * Parameter 2: int n - number of Lasers in laserArr[]
 *
 * Return: Void
 */
void testLasers( Laser laserArr[], int n ){

  blinkLasers(laserArr, n, 3, 150);
  delay(500);  
  blinkLaser( laserArr[0], 2, 150 );
  delay(500);
  blinkLaser( laserArr[1], 2, 150 );
  delay(500);
  blinkLaser( laserArr[2], 2, 150 );
  delay(500);
  
  fadeLasers(laserArr, n, 3, 15);
  delay(500);
  fadeLaser( laserArr[0], 2, 15 );
  delay(500);
  fadeLaser( laserArr[1], 2, 15 );
  delay(500);
  fadeLaser( laserArr[2], 2, 15 );
  delay(500);
  
}
