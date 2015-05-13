/*
 *button.ino
 *File for button functions
 *Emma Fletcher
 *05.10.2015
 */

void readButtons(){
  
  // read button values
  int gameModeButtonVal = digitalRead(gameModeButton);
  int resetButtonVal = digitalRead(resetButton);
  int trippedButtonVal = digitalRead(trippedButton);
  
  Serial.println(trippedButtonVal);
  
  // game mode button
  if( gameModeButtonVal == 1 ){
    gameMode = true;
    digitalWrite(gameModeIndicator, HIGH); 
  } else {
    gameMode = false;
    digitalWrite(gameModeIndicator, LOW);
  }
  
  // reset button
  while( resetButtonVal == 1 ){
    reset();
    resetButtonVal = digitalRead(resetButton);  
  }
  digitalWrite(resetButtonLight, HIGH);
  
  // start button
  
  // tripped button
  while( trippedButtonVal == 1){
    digitalWrite(trippedButtonLight, HIGH);
    delay(100);
    digitalWrite(trippedButtonLight, LOW);
    delay(100);
    trippedButtonVal = digitalRead(trippedButton);
  }
  digitalWrite(trippedButtonLight, HIGH);
  
}

void reset(){
  //reset game
  digitalWrite(resetButtonLight, HIGH);
  delay(100);
  digitalWrite(resetButtonLight, LOW);
  delay(100);
}
