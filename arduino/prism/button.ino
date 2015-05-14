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
  int startButtonVal = digitalRead(startButton);
  int trippedButtonVal = digitalRead(trippedButton);
  
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
  while( startButtonVal == 1 && gameMode ){
    digitalWrite(startGamePin, HIGH);
    flashButtonLight( startButtonLight );    
    startButtonVal = digitalRead(startButton);
  }
  digitalWrite(startButtonLight, HIGH);
  digitalWrite(startGamePin, LOW);
  
  // tripped button
  while( trippedButtonVal == 1){
    flashButtonLight( trippedButtonLight );
    trippedButtonVal = digitalRead(trippedButton);
  }
  digitalWrite(trippedButtonLight, HIGH);
  
}

void flashButtonLight( int lightPin ){
  digitalWrite(lightPin, HIGH);
  delay(100);
  digitalWrite(lightPin, LOW);
  delay(100);
}

void reset(){
  //reset game
  flashButtonLight( resetButtonLight );
}
