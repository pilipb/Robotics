
#include "linesensor.h"
#include "motors.h"

Motors_c motor;
LineSensor_c linesensor;



// The pin used to activate the IR LEDs
#define EMIT_PIN 11

float readings[5];

void setup() {


  linesensor.initialise();
  motor.initialise();

  // Configure the Serial port
  Serial.begin(9600);
  delay(100);

}

void loop() {
  //  int dir;
  //  dir = linesensor.bangFollow(); // bang bang control
  //  Serial.println("dir: " + String(dir));
  //  motor.stayOnLine(dir, 20);
  //  delay(100);

  //  boolean online = linesensor.onLine(2);

  //  linesensor.getReadings(readings);
  //  Serial.println(readings[1]);
  ////  Serial.print("");
  //  Serial.println(readings[2]);
  ////  Serial.print("");
  //  Serial.println(readings[3]);
  ////  Serial.print("");

  float dir;
  dir = linesensor.weightFollow(); // weighted control
  //  dir = linesensor.bangFollow();
  Serial.println("dir: " + String(dir));
  motor.stayOnLine(dir, 70);
  delay(15);

}
