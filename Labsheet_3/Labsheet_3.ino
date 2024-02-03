
#include "linesensor.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"


Motors_c motor;
LineSensor_c linesensor;
Kinematics_c matics;

long e0_count_t;
long e1_count_t;

// timings
unsigned long kinematics_ts;

void setup() {

  setupEncoder0();
  setupEncoder1();
  linesensor.initialise();
  motor.initialise();
  matics.initialise();

  e0_count_t = 0;
  e1_count_t = 0;

  delay(1000);

  kinematics_ts = millis();

  // Configure the Serial port
  Serial.begin(9600);
  

}

void loop() {

  //  float dir;
  //  dir = linesensor.weightFollow(); // weighted control
  //  motor.stayOnLine(dir, 70);
  //  Serial.println(count_e0);
  //  Serial.println(count_e1);

  // this gets the net distance traveled by the robot in the update
  unsigned long elapsed_ts = millis() - kinematics_ts;

  motor.setMotorPower(30,30);

  if( elapsed_ts > 50) {
    long delta_e0 = (count_e0 - e0_count_t); // counts since last reading +ve is forward
    long delta_e1 = (count_e1 - e1_count_t);
    matics.update(delta_e0, delta_e1);
    // update legacy values:
    e0_count_t = count_e0;
    e1_count_t = count_e1;
    kinematics_ts = millis();
  }

  if( global_X > 300) {
    motor.stop_robot();
  }

  
}
