
#include "linesensor.h"
#include "motors.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

PID_c pid1;
Motors_c motor;
LineSensor_c linesensor;
Kinematics_c matics;

// ls states
boolean online0;
boolean online1;
boolean online2;
boolean online3;
boolean online4;


// timings
unsigned long ts;


// define states
#define DEBUG 0
#define TO_LINE 1
#define JOIN_LINE 2
#define FOLLOW_LINE 3
#define TURN_AROUND 4
#define RIGHT_ANGLE_R 5
#define RIGHT_ANGLE_L 6



int state;

void setup() {

  delay(1000);

  setupEncoder0();
  setupEncoder1();
  linesensor.initialise();
  motor.initialise();
  matics.initialise();

  e0_count_t = 0;
  e1_count_t = 0;

  // start time
  ts = millis();

  // Configure the Serial port
  Serial.begin(9600);

  // starting state
  state = TO_LINE;


}

void loop() {

  //  get time
  unsigned long elapsed_ts = millis() - ts;

  //  update all sensors
  if ( elapsed_ts > 10) {

    // identify state and set state

    //    update matics
    long delta_e0 = count_e0 - e0_count_t;
    long delta_e1 = count_e1 - e1_count_t;
    matics.update(delta_e0, delta_e1);
    e0_count_t = count_e0;
    e1_count_t = count_e1;

    //    update linesensors
    online0 = linesensor.onLine(0);
    online1 = linesensor.onLine(1);
    online2 = linesensor.onLine(2);
    online3 = linesensor.onLine(3);
    online4 = linesensor.onLine(4);

    //    update state
    if (state == TO_LINE && online0 && online1 && online2 && online3 && online4) {

      motor.stop_robot();
      state = JOIN_LINE;

    } else if (state == JOIN_LINE && (online0 + online1 + online2 + online3 + online4 < 4)) {

      state = FOLLOW_LINE;

    } else if (online2) {

      state = FOLLOW_LINE;

    } else if (state == FOLLOW_LINE &&  online4 ) {

      state = RIGHT_ANGLE_R;

    } else if (state == FOLLOW_LINE && online0 ) {

      state = RIGHT_ANGLE_L;

    } else if (state == FOLLOW_LINE && (online0 + online1 + online2 + online3 + online4 == 0)) {

      motor.stop_robot();
      state = TURN_AROUND;

    



  }


  ts = millis();
}




// state actions...

if (state == DEBUG) {



} else if (state == TO_LINE) {

  // if the state is to_line just drive forward
  motor.setMotorPower(30, 30);

} else if (state == JOIN_LINE) {

  motor.turn_left();

} else if (state == FOLLOW_LINE) {

  float dir = linesensor.weightFollow();
  motor.stayOnLine(dir, 30);

} else if (state == TURN_AROUND) {

  motor.turn_to(PI / 2, elapsed_ts); // currently hard coded as PI/2


} else if (state == RIGHT_ANGLE_R) {

  motor.turn_right();

} else if (state == RIGHT_ANGLE_L) {

  motor.turn_left();

}

}
