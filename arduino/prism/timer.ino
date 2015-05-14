// a function to be executed periodically
void updateTimer() {

    int time = millis() / 100;
    matrix.println(time);
    matrix.writeDisplay();
    delay(1);
    
}
