/*
 * LucidGloves Firmware Version 4
 * Author: Florent 
 */


 /*
    Test vibration motor

    int motorPin = 14; //motor transistor is connected to, REMEMBER TO CHANGE WHEN TESTING VIBRATION AND TEMP AT SAME TIME, MAYBE TEST CONTROL WITH LIKE A BUTTON OR SOMETHING

    void setup()
    {
      pinMode(motorPin, OUTPUT);
    }

    void loop()
    {
      digitalWrite(motorPin, HIGH); //vibrate
      delay(1000);  // delay one second
      digitalWrite(motorPin, LOW);  //stop vibrating
      delay(1000); //wait 50 seconds.
    }
 
 */




 
 /*
      #Test tapis chaleur


      #include <math.h>
      #define ANALOG_IN 36
      int ThermistorPin = 36;
      int Vo;
      float R1 = 10000; // value of R1 on board
      float logR2, R2, T;
      float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor
      int fetPin = 14;
      const int pinUP = 255;
      const int pinDOWN =0;
      void setup() {
        Serial.begin(115200);
        
        //analogReadResolution(12);
        pinMode(fetPin,OUTPUT);
      }
      void loop() {
        //Vo = analogRead(ThermistorPin);
        //R2 = R1 * (4095.0 / (float)Vo - 1.0); //calculate resistance on thermistor
        //R2=(R1*(float)Vo)/(4095.0-(float)Vo);
      // logR2 = log(R2);
      // T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
      // T = T - 273.15; //convert Kelvin to Celcius
      // T = (T * 9.0)/ 5.0 + 32.0; //convert Celcius to Farenheit
      int adcValue=analogRead(ANALOG_IN);
      double voltage = (float)adcValue/4095.0*3.3;
      double Rt=10*voltage/(3.3-voltage);
      double tempk=1/(1/(273.15+25)+log(Rt/10)/3950.0);
      double T = tempk-273.15;
        Serial.print("Temperature: "); 
        Serial.print(T);
        Serial.println(" C"); 

      //https://learn.sparkfun.com/tutorials/heating-pad-hand-warmer-blanket
      //https://astronomersanonymous.wordpress.com/2016/04/02/controlling-heating-pads-with-arduino-uno/
      if(T>30){
        analogWrite(fetPin, 0); //0% heater off
        delay(30000);
        }
      else if (T<14){
        analogWrite(fetPin, 255); //heater on at 100%
        delay(30000);
      }
      else{
        analogWrite(fetPin, 255); //66% duty cycle on heater
        delay(10000);
      }
      delay(1000); //repeat once per second
      }
 */