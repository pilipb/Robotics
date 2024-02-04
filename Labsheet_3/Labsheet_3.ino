
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
unsigned long ts;

// rot velocity
double vel_rot0;
double vel_rot1;

void setup() {

  setupEncoder0();
  setupEncoder1();
  linesensor.initialise();
  motor.initialise();
  matics.initialise();

  e0_count_t = 0;
  e1_count_t = 0;

  //  delay(1000);

  kinematics_ts = millis();
  ts = millis();

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
  unsigned long elapsed_ts = millis() - ts;

  if ( elapsed_ts > 10) {


    vel_rot0 = vel_rot(0, elapsed_ts);
    vel_rot1 = vel_rot(1, elapsed_ts);

    Serial.println(vel_rot0);

    e0_count_t = count_e0;
    e1_count_t = count_e1;
    ts = millis();
  }
}

double vel_rot(int wheel, unsigned long elapsed_ts) {

  double alpha = 0.1;
  double delta_e = 0;

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
  vel_rot0 = alpha * velocity + (1 - alpha) * velocity;
  
  return velocity;

}
