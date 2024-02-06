
#include "linesensor.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

PID_c pid0;
PID_c pid1;
Motors_c motor;
LineSensor_c linesensor;
Kinematics_c matics;

long e0_count_t;
long e1_count_t;

// timings
unsigned long kinematics_ts;
unsigned long ts;

// pid
float feedback0;
float feedback1;
float demand;

// rot velocity
float vel_rot0;
float vel_rot1;

void setup() {

  setupEncoder0();
  setupEncoder1();
  linesensor.initialise();
  motor.initialise();
  matics.initialise();
  pid0.initialise(80, 0.95, 0.1);
  pid1.initialise(80, 0.95, 0.1);

  e0_count_t = 0;
  e1_count_t = 0;

  feedback0 = 0;
  feedback1 = 0;
  demand = 1;

  ts = millis();

  // Configure the Serial port
  Serial.begin(9600);


}

void loop() {

  motor.setMotorPower(feedback1, feedback0);

  unsigned long elapsed_ts = millis() - ts;

  if ( elapsed_ts > 20) {

    vel_rot0 = vel_rot(0, elapsed_ts);
    vel_rot1 = vel_rot(1, elapsed_ts);

    feedback0 = pid0.update(demand, vel_rot0, elapsed_ts);
    feedback1 = pid1.update(demand, vel_rot1, elapsed_ts);

    Serial.print(demand);
    Serial.print(",");
    Serial.println(vel_rot1);

    e0_count_t = count_e0;
    e1_count_t = count_e1;
    ts = millis();
  }
}

float vel_rot(int wheel, unsigned long elapsed_ts) {

  //  float alpha = 0.1;
  float delta_e;
  float dt = elapsed_ts;

  if (wheel == 0) {
    delta_e = count_e0 - e0_count_t;
  } else if (wheel == 1) {
    delta_e = count_e1 - e1_count_t;
  } else {
    Serial.println("Invalid wheel index");
    return 0;
  }

  float velocity = delta_e / dt;

  return velocity;

}
