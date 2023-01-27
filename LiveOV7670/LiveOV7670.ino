




// change setup.h to switch between buffered and pixel-by-pixel processing
#include "setup.h"
const int MOTION_SENSOR_PIN = 8;   // Arduino pin connected to the OUTPUT pin of motion sensor
const int BUZZER_PIN        = 9;   // Arduino pin connected to Buzzer's pin
int motionStateCurrent      = LOW; // current  state of motion sensor's pin
int motionStatePrevious     = LOW; 
int i ;


void setup() {
  // This is not necessary and has no effect for ATMEGA based Arduinos.
  // WAVGAT Nano has slower clock rate by default. We want to reset it to maximum speed
//  Serial.begin(2000000);                
  pinMode(MOTION_SENSOR_PIN, INPUT); // set arduino pin to input mode
  pinMode(BUZZER_PIN, OUTPUT);  
  CLKPR = 0x80; // enter clock rate change mode
  CLKPR = 0; // set prescaler to 0. WAVGAT MCU has it 3 by default.

  initializeScreenAndCamera();
}


void loop() {
  String teststr = Serial.readString();
  Serial.println(teststr);
  if (teststr == 1){
    digitalWrite(BUZZER_PIN, HIGH);  
  }
  motionStatePrevious = motionStateCurrent;            // store old state
  motionStateCurrent  = digitalRead(MOTION_SENSOR_PIN); // read new state

  if (motionStatePrevious == LOW && motionStateCurrent == HIGH) { // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    for (i=0; i<40; i++){
      processFrame();  
    }
    
//    initializeScreenAndCamera();
//    digitalWrite(BUZZER_PIN, HIGH); // turn on
  }
  else if (motionStatePrevious == HIGH && motionStateCurrent == LOW) { // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    digitalWrite(BUZZER_PIN, LOW);  // turn off
  }
 

 
//  processFrame();
}
