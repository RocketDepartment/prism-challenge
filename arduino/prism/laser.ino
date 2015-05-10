/*
 *laser.ino
 *File for laser control functions
 *
 *Emma Fletcher
 *05.09.2015
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

void blinkLaser( Laser l, int times, int blinkSpeed ){
  for( int i = 0; i < times; i++ ){
    digitalWrite(l.pin, LOW);
    delay(blinkSpeed);
    digitalWrite(l.pin, HIGH);
    delay(blinkSpeed);   
  } 
}

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
