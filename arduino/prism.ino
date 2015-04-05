/*
Prism Challenge -- Laser Control Unit (LCU)
 */
 
// set led indicators, these lights show the status of 
// each laser light sensor, on if laser is connected
// off if laser is blocked

#define NUM_LASERS 7
#define LASER_THRESHOLD 350

boolean laserTripped = false;
boolean gameMode = false;

int penaltyCount = 0;
int laserTrippedSig = 7;
int startLaserTrippedSig = 12;
int gameModeSig = 2;
int mesgRecievedSig = 10;

int indicator0 = 41;
int indicator1 = 43;
int indicator2 = 45;
int indicator3 = 47;
int indicator4 = 49;
int indicator5 = 51;
int indicator6 = 31;

int indicators[NUM_LASERS] = {indicator0, indicator1, indicator2, indicator3, indicator4, indicator5, indicator6};

int laserSensor0 = A0;
int laserSensor1 = A1;
int laserSensor2 = A2;
int laserSensor3 = A3;
int laserSensor4 = A4;
int laserSensor5 = A5;
int laserSensor6 = A6;


int laserSensors[NUM_LASERS] = {laserSensor0, laserSensor1, laserSensor2, laserSensor3, laserSensor4, laserSensor5, laserSensor6};

int laser0 = 31;
int laser1 = 32;
int laser2 = 33;
int laser3 = 34;
int laser4 = 35;
int laser5 = 36;
int laser6 = 37;

int lasers[NUM_LASERS] = {laser0, laser1, laser2, laser3, laser4, laser5, laser6};

boolean state0 = false;
boolean state1 = false;
boolean state2 = false;
boolean state3 = false;
boolean state4 = false;
boolean state5 = false;
boolean state6 = false;

boolean state[NUM_LASERS] = {state0, state1, state2, state3, state4, state5, state6};

void readLaserSensors() {
  //Serial.println("read laser sensor");
  
  int count = 0;
  for( int i = 0; i < NUM_LASERS; i++ ){ 
    //Serial.println(i);
    
    
    int lightReading;
    
    
    // read the photo cell value
    
    lightReading = analogRead(laserSensors[i]);
    
    //Serial.print(i);
    //Serial.print(" ");
    
    //Serial.println(lightReading);
    
    //delay(250);
    
    
    // check if its off
    if( lightReading < LASER_THRESHOLD ){
      state[i] = false;
      
      laserTripped = true;
      
      //Serial.println(state[i]);
      
      //Serial.println('lasers off');
      
      
    } else {
      //Serial.println('laser on');
      state[i] = true;
      count = count + 1;
      
    }
    
    
  }
  
  //Serial.println(count);
  if( count == NUM_LASERS ) {
   laserTripped = false; 
   digitalWrite(laserTrippedSig, LOW);
   //Serial.println("Laser Tripped False");
  }
  
  //delay(500);
  
  
}

void startFinishLine(){
  //Serial.println(state[0]);
  
  if( state[0] == false ){
    //Serial.println('Laser Tripped');
    digitalWrite(startLaserTrippedSig, HIGH);
  } else {
    //Serial.println('Laser Not Tripped');
    
    digitalWrite(startLaserTrippedSig, LOW);  
  }
  
}

void updateIndicators() {

  // loop through each laser
  for( int i = 0; i < NUM_LASERS; i++ ){
    
    //Serial.print(i);
    
   // if state is true (laser on)
   if( state[i] == true ){
    // set inidactor high
    digitalWrite(indicators[i], HIGH);
    //Serial.println(" true");
    
   } else {
    digitalWrite(indicators[i], LOW); 
    //Serial.println(" false");
    state[i] = false;
    
   }
   
  }
}

void recieveMessage() {
 
 if ( Serial.available() ) {
   // 0 no message
   // 1 game start
   // 2 game end
   // 2 lasers on
   // 3 lasers off
     
   decode(Serial.read() - '0');
   
 }
}

void decode(int n){
 
 if( n == 1 ){
  gameMode = true;
  digitalWrite(gameModeSig, HIGH);
 } else if( n == 2 ){
  gameMode = false; 
  digitalWrite(gameModeSig, LOW);
 } else if( n == 3 ){
  gameMode = false;
  digitalWrite(gameModeSig, LOW);
 } else if
 ( n == 4 ){
   gameMode = false;
   digitalWrite(gameModeSig, LOW);
   
 }
}

void reset() {
  
}

void checkForTrip() {
  if( laserTripped == true )
  {
   digitalWrite(laserTrippedSig, HIGH);    
  } else {
   digitalWrite(laserTrippedSig, LOW);
  }
}

// the setup routine runs once when you press reset:
void setup() {    
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(indicator0, OUTPUT);
  pinMode(indicator1, OUTPUT);  
  pinMode(indicator2, OUTPUT);  
  pinMode(indicator3, OUTPUT);  
  pinMode(indicator4, OUTPUT);  
  pinMode(indicator5, OUTPUT);
  
  pinMode(laser0, OUTPUT);
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  pinMode(laser3, OUTPUT);
  pinMode(laser4, OUTPUT);
  pinMode(laser5, OUTPUT);
  pinMode(laser6, OUTPUT);
  
  //pinMode(startLaserTrippedSig, OUTPUT);
  pinMode(laserTrippedSig, OUTPUT);
  pinMode(gameModeSig, OUTPUT);
  
  digitalWrite(laserTrippedSig, LOW);
  digitalWrite(gameModeSig, LOW);
  
}



// the loop routine runs over and over again forever:
void loop() {
  //Serial.println("Hello");
  
  readLaserSensors();
  //Serial.println("update indicators");
  
  updateIndicators();
  //Serial.println("Check for trip -- but not really");
  //checkForTrip();
  
  //Serial.println("Recieve Message");
  
  recieveMessage();
  //Serial.println("calling start finish");
  
  //startFinishLine();
  
  
  if( gameMode == true) {
   digitalWrite(gameModeSig, HIGH);
   
   //alert pi when start/finish laser is tripped
   
   while( gameMode == true ){
     //Serial.println("Game Mode");
    readLaserSensors();
    updateIndicators(); 
    
    checkForTrip();
    
    //see if that game has ended
    recieveMessage();
    startFinishLine();
   }
   
   digitalWrite(gameModeSig, LOW);
   digitalWrite(laserTrippedSig, LOW);
   
   
  }
  
}
