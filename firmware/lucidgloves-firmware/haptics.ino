#if USING_FORCE_FEEDBACK

#if defined(ESP32)
  #include "ESP32Servo.h"
#else
  #include "Servo.h"
#endif

Servo pinkyServo;
Servo ringServo;
Servo middleServo;
Servo indexServo;
Servo thumbServo;

void setupServoHaptics(){
  pinkyServo.attach(PIN_PINKY_MOTOR);
  ringServo.attach(PIN_RING_MOTOR);
  middleServo.attach(PIN_MIDDLE_MOTOR);
  indexServo.attach(PIN_INDEX_MOTOR);
  thumbServo.attach(PIN_THUMB_MOTOR);
}

//static scaling, maps to entire range of servo
void scaleLimits(int* hapticLimits, float* scaledLimits){
  for (int i = 0; i < 5; i++){
    #if FLIP_FORCE_FEEDBACK
    scaledLimits[i] = hapticLimits[i] / 1000.0f * 180.0f;
    #else
    scaledLimits[i] = 180.0f - hapticLimits[i] / 1000.0f * 180.0f;
    #endif
  }
  
}

//dynamic scaling, maps to the limits calibrated from your finger
void dynScaleLimits(int* hapticLimits, float* scaledLimits){
  //will be refactored to take min and max as an argument

  /* this implementation of dynamic scaling relies on the assumption 
   * that the servo reaches 2/3 of the potentiometer's range, 
   * and that 0 degrees is geared to the start of the potentiometer.
   * Different hardware types may need to handle dynamic scaling differently.
   */
  for (int i = 0; i < sizeof(hapticLimits); i++){
    scaledLimits[i] = hapticLimits[i] / 1000.0f * 180.0f;
  }
}

void writeServoHaptics(int* hapticLimits){
  float scaledLimits[5];
  scaleLimits(hapticLimits, scaledLimits);
  if(hapticLimits[0] >= 0) thumbServo.write(scaledLimits[0]);
  if(hapticLimits[1] >= 0) indexServo.write(scaledLimits[1]);
  if(hapticLimits[2] >= 0) middleServo.write(scaledLimits[2]);
  if(hapticLimits[3] >= 0) ringServo.write(scaledLimits[3]);
  if(hapticLimits[4] >= 0) pinkyServo.write(scaledLimits[4]);
}


// -------------------------------
// VIBRATION MODULE
// -------------------------------

void setupVibration() {
  pinMode(PIN_PINKY_VIBR, OUTPUT);
  pinMode(PIN_RING_VIBR, OUTPUT);
  pinMode(PIN_MIDDLE_VIBR, OUTPUT);
  pinMode(PIN_INDEX_VIBR, OUTPUT);
  pinMode(PIN_THUMB_VIBR, OUTPUT);

  analogWrite(PIN_PINKY_VIBR, 0);
  analogWrite(PIN_RING_VIBR, 0);
  analogWrite(PIN_MIDDLE_VIBR, 0);
  analogWrite(PIN_INDEX_VIBR, 0);
  analogWrite(PIN_THUMB_VIBR, 0);
}

void writeVibration(int *vibrationIntensity) {

  digitalWrite(PIN_THUMB_MOTOR,  vibrationIntensity[0]);
  digitalWrite(PIN_INDEX_MOTOR,  vibrationIntensity[1]);
  digitalWrite(PIN_MIDDLE_MOTOR, vibrationIntensity[2]);
  digitalWrite(PIN_RING_MOTOR,   vibrationIntensity[3]);
  digitalWrite(PIN_PINKY_MOTOR,  vibrationIntensity[4]);

}

#endif
