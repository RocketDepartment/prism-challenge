/*
 *sensor.ino
 *File for light sensor functions
 *Emma Fletcher
 *05.10.2015
 */

void readSensors( Laser laserArr[], int n ){
  
  for( int i = 0; i < n; i++ ){
    int sensorVal = analogRead(laserArr[i].sensorPin);
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(sensorVal);
    delay(250);    
  }
  
}
