#include <FreqPeriod.h>
// input should be on pin 7
 
double lfrq;
long int pp;
int count = 0; 

// direction accuracy
int maxcount = 5;
int directions[5];
int direction = 0;

// velocity accuracy
double velocitySum = 0; 
int amountOfVelocityMeasurements = 3; 
int velocityCount = 0; 
 
void setup() {
Serial.begin(115200);
  FreqPeriod::begin();
  Serial.println("FreqPeriod Library Test");
}
 
void loop() {
  pp = FreqPeriod::getPeriod();
  if (pp) {
   // Serial.print ("period: ");
   // Serial.print(pp);
   // Serial.print(" 1/16us / frequency: ");
 
    lfrq = 16000400.0 /pp;
  //  Serial.print(lfrq);
   // Serial.print(" Hz ");
    // Serial.print(lfrq/31.36);
    // Serial.println( "mph");


    if (count < maxcount) {
      if (analogRead(0) > analogRead(1)) { 
          directions[count] = 1;
      } else {
          directions[count] = -1; 
      }
      count++; 
    } else {
      count = 0;
    }

    bool directionsAreTheSame = true;
    for (int i = 1; i < maxcount; i++) {
      if (directions[i] != directions[0]) {
        directionsAreTheSame = false;
        break; 
      }
    }

    if (directionsAreTheSame) { 
      direction = directions[0];
    }

    double velocity = lfrq/19.49; 

    // if (velocity < 100) { //we don't count weird velocities above 100 km/h
      if (velocityCount < amountOfVelocityMeasurements) {
        velocitySum += lfrq/19.49;
        velocityCount++; 
      } else {
        Serial.println("V" + String(int(lfrq/19.49/amountOfVelocityMeasurements*100)) + ",R" + String(direction));
  
        velocityCount = 0;
        velocitySum = 0;
      }
   // }
    //    if (lfrq/19.49 < 200) { 
    //      Serial.println("V" + String(int(lfrq/19.49*100)) + ",R" + String(direction));
    //    }
  }
}

