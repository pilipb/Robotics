
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
  if ( elapsed_ts > 50) {

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
      state = JOIN_LINE;
    }
  }


  

  // state actions...

  if (state == DEBUG) {



  } else if (state == TO_LINE) {

    // if the state is to_line just drive forward
    motor.setMotorPower(30, 30);

  } else if (state == JOIN_LINE) {

    motor.stop_robot();



  } else if (state == FOLLOW_LINE) {

    float dir = linesensor.weightFollow();
    motor.stayOnLine(dir, 30);

  } else if (state == TURN_AROUND) {



  }



}
