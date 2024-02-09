// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _STATE_H
#define _STATE_H


#include "encoders.h"
#include "kinematics.h"
#include "motors.h"
#include "linesensor.h"

LineSensor_c linesensor;
Motors_c motor;

// define states
#define DEBUG 0
#define TO_LINE 1
#define JOIN_LINE 2
#define FOLLOW_LINE 3
#define TURN_AROUND 4
#define RIGHT_ANGLE_R 5
#define RIGHT_ANGLE_L 6
#define RETURN_HOME 7

int state;
int prev_state;

float last_angle;

// Class to contain generic PID algorithm.
class STATE_c {
  public:

    // Constructor, must exist.
    STATE_c() {

    }

    void initialise() {
      state = TO_LINE;
    }

    void update(boolean online0, boolean online1, boolean online2, boolean online3, boolean online4, unsigned long start_time) {

      //    update state
      if (state == TO_LINE && online0 && online1 && online2 && online3 && online4) {

        motor.stop_robot();
        state = JOIN_LINE;
        prev_state = TO_LINE;

      } else if (state == JOIN_LINE && (global_theta > (PI / 6))) {

        state = FOLLOW_LINE;
        prev_state = JOIN_LINE;

      } else if ((state == RIGHT_ANGLE_L | state == RIGHT_ANGLE_R ) && (abs(global_theta - last_angle) > (PI / 3))) {
        // safety stop to not miss line
        state = FOLLOW_LINE;

      } else if (state == TURN_AROUND && (abs(global_theta - last_angle) > PI / 2)) {

        state = FOLLOW_LINE;
        prev_state = TURN_AROUND;

      } else if (state == FOLLOW_LINE && online4 && (online0 + online1 + online2 + online3 == 0) ) {

        state = RIGHT_ANGLE_L;
        prev_state = FOLLOW_LINE;
        last_angle = global_theta;

      } else if (state == FOLLOW_LINE && online0 && (online1 + online2 + online3 + online4 == 0) ) {

        state = RIGHT_ANGLE_R;
        prev_state = FOLLOW_LINE;
        last_angle = global_theta;

      } else if (state == FOLLOW_LINE && (online0 + online1 + online2 + online3 + online4 == 0)) {

        if ((millis() - start_time) > 20000) {
          motor.setMotorPower(0, 0);
          state = RETURN_HOME;
        } else {
          motor.stop_robot();
          state = TURN_AROUND;
          prev_state = FOLLOW_LINE;
          last_angle = global_theta;
        }

      } else if (state == RETURN_HOME) {

        while (true) {
          motor.stop_robot();
        }

      }
    }


    

    void action() {

      if (state == DEBUG) {


      } else if (state == TO_LINE) {

        // if the state is to_line just drive forward
        motor.setMotorPower(30, 30);

      } else if (state == JOIN_LINE) {

        motor.turn_right();

      } else if (state == FOLLOW_LINE) {

        float dir = linesensor.weightFollow();
        motor.stayOnLine(dir, 30);

      } else if (state == TURN_AROUND) {

        motor.turn_right();

      } else if (state == RIGHT_ANGLE_R) {

        motor.turn_right();

      } else if (state == RIGHT_ANGLE_L) {

        motor.turn_left();

      }
    }
};



#endif
