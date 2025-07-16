/*
 * LucidGloves Firmware Version 4
 * Author: Florent
 *
 * THERMAL HEATPAD CONTROL
 * ------------------------
 * Reference:
 * - https://learn.sparkfun.com/tutorials/heating-pad-hand-warmer-blanket
 * - https://astronomersanonymous.wordpress.com/2016/04/02/controlling-heating-pads-with-arduino-uno/
 *
 * PWM vs Temp:
 *   0%   ->   0   -> 23°C
 *   25%  ->  64   -> 33°C
 *   50%  -> 128   -> 43°C
 *   75%  -> 191   -> 53°C
 *   100% -> 255   -> 63°C
 */

#include <math.h>

// -------------------------------
// THERMAL MODULE
// -------------------------------

void setupThermal() {
  Serial.begin(115200);

  pinMode(PIN_TEMP_CTRL, INPUT);
  pinMode(PIN_TEMP_MES, OUTPUT);

  analogWrite(PIN_TEMP_CTRL, 0);  // Safe default
}

void writeThermal(int targetTemp) {
  int adcValue = analogRead(PIN_TEMP_CTRL);
  double voltage = (float)adcValue / 4095.0 * 3.3;
  double resistance = 10.0 * voltage / (3.3 - voltage);  // Thermistor resistance
  double tempK = 1.0 / (1.0 / (273.15 + 25.0) + log(resistance / 10.0) / 3950.0);
  double currentTemp = tempK - 273.15;

  int pwmOutput = 0;

  if (currentTemp < targetTemp - 2.0) {
    pwmOutput = 255;
  } else if (currentTemp > targetTemp + 2.0) {
    pwmOutput = 0;
  } else {
    double error = targetTemp - currentTemp;
    pwmOutput = constrain((int)(error * 32), 0, 255);  // Gain may be tuned
  }

  analogWrite(PIN_TEMP_MES, pwmOutput);
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
#if defined(ESP32)
  digitalWrite(PIN_THUMB_MOTOR,  vibrationIntensity[0]);
  digitalWrite(PIN_INDEX_MOTOR,  vibrationIntensity[1]);
  digitalWrite(PIN_MIDDLE_MOTOR, vibrationIntensity[2]);
  digitalWrite(PIN_RING_MOTOR,   vibrationIntensity[3]);
  digitalWrite(PIN_PINKY_MOTOR,  vibrationIntensity[4]);
#endif
}
