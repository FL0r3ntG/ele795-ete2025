/*
 * LucidGloves Firmware Version 4
 * Author: Florent 
*/

// Data Structures
struct ThermalData {
  float currentTemp = 0;
  float targetTemp = 30.0;
  uint8_t pwmValue = 0;
  bool heatingActive = false;
};

struct VibrationData {
  uint8_t pinkyIntensity = 0;
  uint8_t ringIntensity = 0;
  uint8_t middleIntensity = 0;
  uint8_t indexIntensity = 0;
  uint8_t thumbIntensity = 0;
  bool motorsActive = false;
};

extern ThermalData thermal;
extern VibrationData vibration;

///////////////// THERMAL HEATPAD //////////////////////////////
//https://learn.sparkfun.com/tutorials/heating-pad-hand-warmer-blanket
//https://astronomersanonymous.wordpress.com/2016/04/02/controlling-heating-pads-with-arduino-uno/


// 0%   ->   0   -> 23°C
// 25%  ->  64   -> 33°C
// 50%  -> 128   -> 43°C
// 75%  -> 191   -> 53°C
// 100% -> 255   -> 63°C


#include <math.h>


void setupThermal(){

  Serial.begin(115200);

  pinMode(PIN_TEMP_CTRL, INPUT);
  analogWrite(PIN_TEMP_CTRL, 0);

  pinMode(PIN_TEMP_MES, OUTPUT);
  
}

void WriteThermal() {

  int adcValue = analogRead(PIN_TEMP_CTRL);
  double voltage = (float)adcValue/4095.0*3.3;
  double Rt = 10*voltage/(3.3-voltage);
  double tempk = 1/(1/(273.15+25)+log(Rt/10)/3950.0);
  double T = tempk-273.15;

    //Serial.print("Temperature: "); 
    //Serial.print(T);
    //Serial.println(" C"); 

  if(T>30){
    analogWrite(PIN_TEMP_MES, 0); //0% heater off
    }
  else if (T<14){
    analogWrite(PIN_TEMP_MES, 255); //heater on at 100%
  }
  else{
    analogWrite(PIN_TEMP_MES, 0); //0% duty cycle on heater
  }

}

void ReadThermal(){

}


//////////////////// VIBRATION MOTOR ////////////////////////

void setupVibration() {
  const int motorPins[] = {PIN_PINKY_VIBR, PIN_RING_VIBR, PIN_MIDDLE_VIBR, 
                          PIN_INDEX_VIBR, PIN_THUMB_VIBR};
  
  for (int i = 0; i < 5; i++) {
    pinMode(motorPins[i], OUTPUT);
    analogWrite(motorPins[i], 0);
  }
}

void WriteVibration(){

    digitalWrite(motorPin, HIGH); //vibrate
    digitalWrite(motorPin, LOW);  //stop vibrating

}

