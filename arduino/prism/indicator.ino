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
   
   // Update the laserTripped indicator light
   if( numTripped > 0 ){
     digitalWrite(laserTrippedPin, HIGH);
   } else {
     digitalWrite(laserTrippedPin, LOW);
   }
   
}
