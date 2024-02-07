
#include "linesensor.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

PID_c pid1;
Motors_c motor;
LineSensor_c linesensor;
Kinematics_c matics;

void setup() {

  setupEncoder0();
  setupEncoder1();
  linesensor.initialise();
  motor.initialise();
  matics.initialise();

  // start time
  ts = millis();

  // Configure the Serial port
  Serial.begin(9600);


}

void loop() {

  //  get time
  unsigned long elapsed_ts = millis() - ts;

  //  update all sensors
  if ( elapsed_ts > 20) {

    // identify state and set state

  }

  // state actions...

  if (state==DEBUG) {
    
  }









}
