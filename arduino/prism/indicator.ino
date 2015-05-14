/*
 *indicator.ino
 *File for light sensor functions
 *Emma Fletcher
 *05.10.2015
 */
 
void updateIndicators( Laser laserArr[], int n ){
   int numTripped = 0;
   
   for( int i = 0; i < n; i++ ){
     if( laserArr[i].indicatorValue ){
       digitalWrite(laserArr[i].indicatorPin, HIGH);
     } else {
       digitalWrite(laserArr[i].indicatorPin, LOW);
       numTripped++;
     }
   }
   
   // Update the laserTripped signal variable
   if( numTripped > 0 ){
     laserTripped = true;
   } else {
     laserTripped = false;
   }
   
}

void reportStatus(){
  //report game start lasert tripped
  if( laserStartTripped ){
    digitalWrite(startGamePin, HIGH);    
  } else {
    digitalWrite(startGamePin, LOW);  
  }
  
  //report tripped game lasers
  if( laserTripped ){
    digitalWrite(laserTrippedPin, HIGH);
    delay(100);  
  } else {
    digitalWrite(laserTrippedPin, LOW);
  }
}
