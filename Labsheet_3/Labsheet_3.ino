
#include "linesensor.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

PID_c pid;
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

// rot velocity
double vel_rot0;
double vel_rot1;

void setup() {

  setupEncoder0();
  setupEncoder1();
  linesensor.initialise();
  motor.initialise();
  matics.initialise();
  pid.initialise(5);

  e0_count_t = 0;
  e1_count_t = 0;

  feedback0 = 0;
  feedback1 = 0;

  ts = millis();

  // Configure the Serial port
  Serial.begin(9600);


}

void loop() {

  motor.setMotorPower(10 + feedback0, 10 + feedback1);

  unsigned long elapsed_ts = millis() - ts;

  if ( elapsed_ts > 10) {


    vel_rot0 = vel_rot(0, elapsed_ts);
    vel_rot1 = vel_rot(1, elapsed_ts);

    feedback0 = pid.update(5, vel_rot0);
    feedback1 = pid.update(5, vel_rot0);

    Serial.print("Demand:");
    Serial.print(5);
    Serial.print(" ");
    Serial.print("feedback:");
    Serial.print(feedback0);
    Serial.print(" ");
    Serial.print("measure:");
    Serial.println(vel_rot0);


    e0_count_t = count_e0;
    e1_count_t = count_e1;
    ts = millis();
  }
}

double vel_rot(int wheel, unsigned long elapsed_ts) {

  float alpha = 0.1;
  float delta_e = 0;

  if (wheel == 0) {
    delta_e = count_e0 - e0_count_t;
  } else if (wheel == 1) {
    delta_e = count_e1 - e1_count_t;
  } else {
    Serial.println("Invalid wheel index");
    return 0;
  }

  // low pass filter
  double velocity = delta_e / elapsed_ts;
//  double fil_velocity = alpha * velocity + (1 - alpha) * velocity;

  return velocity;

}
