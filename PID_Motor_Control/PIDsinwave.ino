#include<Encoder.h>

Encoder myEnc(2,3);

void setup() {
  Serial.begin(115200);
 // Serial.println("Basic Encoder Test:");
 
}

double intStartTime = 0;
double currentPosition = -999.0;
double goalPosition = 1;
double Kp = 5;
double Kd = 1;
double Ki =  5; 
double Vout11 = 0;
double Vout9=0;
double prevError = 0;
double currError = 0;
double iSumation = 0;
double riseTime = 0;

double startLoop = 0;
double endLoop = 0;

double gains = 0;

void loop() {
 Kp = 11.5*3.676*0.001*sq(12)/0.4179;
 Kd = (2*1*12*11.5*3.676*0.001/0.4179) - 0.4179;
 // gains = 0.4179/(11.5*3.676*0.001*sq(s) + sq(0.4179)*s);

  double currTime = millis();
  goalPosition = sin(currTime/1000);
  if( (currTime - intStartTime) >= 10){
    //if(millis() < 100000){
   //double eqtime = millis() / 1000.0;
   //double xt = 1.0 - (1.0 + 12.0*eqtime)*pow(2.718281828459045235360287,(-12.0*eqtime));
   //Serial.println(xt);
    //}
      currentPosition = myEnc.read();
      double radPosition = (currentPosition*2*PI)/(28*298);
      Serial.println(radPosition);
      Serial.println("looping");
      
      currError = goalPosition - radPosition; //steady state
      double dervError = (currError - prevError)/(currTime - intStartTime);

      iSumation += currError*(currTime - intStartTime)/1000;
      double integralterm = Ki * iSumation;
      Serial.println("integralterm");
      Serial.println(integralterm);
      if(integralterm > 5){

        integralterm = 5;
      }
      if(integralterm < -5){

        integralterm = -5;
      }
      double C = Kp*currError + integralterm + Kd*dervError;  
      prevError = currError;

      //converting controller output units
     double value = C *255 / 5;
      if(abs (C) <= 5){
        if(value>0){
          Vout11 = 0;
          Vout9 = value;
        }
        else {
          Vout11 = -value;
          Vout9 = 0;
 
        }
       
      
      }else{

        if(value > 0){
          Vout11 = 0;
          Vout9 = 5 *255 / 5;
        }
        else {
          Vout11 = -5 *255 / 5;
          Vout9 = 0;
 
        }

          
      }

        
      analogWrite(9,Vout9);
      analogWrite(11,Vout11); 
      
      /*if((radPosition < (goalPosition/10*9) )&& (radPosition > (goalPosition/10))){
        riseTime = currTime;
        
      }*/

     if(goalPosition < 1/20 * 19){
        startLoop = currTime;
      }
      if(goalPosition > -1/20 * 19){
        endLoop = currTime;
        Serial.println("rise");
        Serial.println(endLoop - startLoop);
      }

     Serial.println("Error");
     Serial.println(currError); //overshoot only the final time    
      intStartTime = currTime;
      //Serial.println(riseTime);
     }  
  
}