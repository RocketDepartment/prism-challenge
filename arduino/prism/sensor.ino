/*
 *sensor.ino
 *File for light sensor functions
 *Emma Fletcher
 *05.10.2015
 */

void readSensors( Laser laserArr[], int n ){
  
  for( int i = 0; i < n; i++ ){
    int val = analogRead(laserArr[i].sensorPin);
    laserArr[i].sensorValue = val;
    if( val > 100 ){
      laserArr[i].indicatorValue = true;
    } else {
      laserArr[i].indicatorValue = false;
    }
    delay(1);    
  }
  
}
