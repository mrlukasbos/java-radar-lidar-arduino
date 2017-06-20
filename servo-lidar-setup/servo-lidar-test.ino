
 /*  PROTOCOL
 *  A: Angle  (LiDAR)
 *  D: Distance (LiDAR) 
 *  R: Direction (Radar)
 *  V: Velocity (Radar) 
 */ 
 
#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;
unsigned long pulseWidth;
Servo servo1;
int servoAngle1;
int turnDegrees = 1;

void setup()
{
// THINK ABOUT THE SETTINGS!!!!!!!!
  
  Serial.begin(115200); // Start serial communications
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  servo1.attach(5); 
  servoAngle1 = 0;
}

void loop() {

  // choose one of three
  // terminalOverview();
  // graphWriterOverview();
   readerOverview();
  
  servoAngle1 += turnDegrees;


  if (servoAngle1 == 180 || servoAngle1 == 0) { 
    turnDegrees = -turnDegrees;
  }
  servo1.write(servoAngle1);

  
}
void terminalOverview() { 
  Serial.print("lidar distance ");
  Serial.print(myLidarLite.distance());
  Serial.print("\t servo angle input ");
  Serial.println(servoAngle1);
}

void graphWriterOverview() { 
  String distanceText = "A" + String(myLidarLite.distance());
  String angleText = "B" + String(servoAngle1);
  Serial.println(distanceText);
  Serial.println(angleText);
}

void readerOverview() { 
  Serial.println("D"+String(myLidarLite.distance()) + ",A" + String(servoAngle1));
}


/*------------------------------------------------------------------------------

  LIDARLite Arduino Library
  GetDistanceI2c

  This example shows how to initialize, configure, and read distance from a
  LIDAR-Lite connected over the I2C interface.

  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND
  
  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

------------------------------------------------------------------------------*/

/*
    configure(int configuration, char lidarliteAddress)

    Selects one of several preset configurations.

    Parameters
    ----------------------------------------------------------------------------
    configuration:  Default 0.
      0: Default mode, balanced performance.
      1: Short range, high speed. Uses 0x1d maximum acquisition count.
      2: Default range, higher speed short range. Turns on quick termination
          detection for faster measurements at short range (with decreased
          accuracy)
      3: Maximum range. Uses 0xff maximum acquisition count.
      4: High sensitivity detection. Overrides default valid measurement detection
          algorithm, and uses a threshold value for high sensitivity and noise.
      5: Low sensitivity detection. Overrides default valid measurement detection
          algorithm, and uses a threshold value for low sensitivity and noise.
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */
