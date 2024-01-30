
#include "linesensor.h"
#include "motors.h"

Motors_c motor;
LineSensor_c linesensor;



// The pin used to activate the IR LEDs
#define EMIT_PIN 11

void setup() {


  linesensor.initialise();
  //  motor.initialise();

  // Configure the Serial port
  Serial.begin(9600);

}

void loop() {
  //  int dir;
  //  dir = linesensor.bangFollow(); // bang bang control
  //  Serial.println("dir: " + String(dir));
  //  motor.stayOnLine(dir, 20);
  //  delay(100);

  float readings[5] = {};

  // FOR ALL SENSORS
  linesensor.getReadings(readings);
  linesensor.weightReadings(readings);

  Serial.println("\nreadings:");
  for (int i = 0; i < 5; i++) {
    Serial.println(String(readings[i]));
  }

  delay(200);
}
