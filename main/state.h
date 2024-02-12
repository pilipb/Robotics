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
#define OUT 8

int state;
int prev_state;

float last_angle;

long dist_x;
long dist_y;

// Class to contain generic PID algorithm.
class STATE_c {
  public:

    // Constructor, must exist.
    STATE_c() {

    }

    void initialise() {
      state = OUT;
    }

    void update(boolean online0, boolean online1, boolean online2, boolean online3, boolean online4, unsigned long start_time) {

      // first travel to line in straight line until detect line
      if (state == OUT && (millis() - start_time) > 1000) {

        state = TO_LINE;
        
      }
      if (state == TO_LINE && online0 && online1 && online2 && online3 && online4) {
        motor.stop_robot();
        state = JOIN_LINE;
        prev_state = TO_LINE;

        // join line by rotating
      } else if (state == JOIN_LINE && (global_theta > (PI / 6))) {

        state = FOLLOW_LINE;
        prev_state = JOIN_LINE;

      } else if ((state == RIGHT_ANGLE_L | state == RIGHT_ANGLE_R ) && (abs(global_theta - last_angle) > (PI / 2))) {
        // safety stop to not miss line
        state = FOLLOW_LINE;
        
      } else if (state == TURN_AROUND && (abs(global_theta - last_angle) > PI)) {

        state = FOLLOW_LINE;
        prev_state = TURN_AROUND;

      } else if (state == TURN_AROUND && (abs(global_theta - last_angle) < (PI - 0.4))){

        state = TURN_AROUND;

      } else if (state == FOLLOW_LINE && online4 && (online0 + online1 + online2 + online3 == 0) ) {

        state = RIGHT_ANGLE_L;
        prev_state = FOLLOW_LINE;
        last_angle = global_theta;

      } else if (state == FOLLOW_LINE && online0 && (online1 + online2 + online3 + online4 == 0) ) {

        state = RIGHT_ANGLE_R;
        prev_state = FOLLOW_LINE;
        last_angle = global_theta;

      } else if (state == FOLLOW_LINE && prev_state == FOLLOW_LINE && (online1 + online2 + online3 == 0)) {

        if ((millis() - start_time) > 20000) {

          state = RETURN_HOME;
          dist_x = global_X;
          dist_y = global_Y;
          last_angle = global_theta;

        } else {

          state = TURN_AROUND;
          last_angle = global_theta;

        }

      }
    }


    void action(unsigned long elapsed_ts) {

      if (state == DEBUG) {

        float ls0 = linesensor.analogLineSensor(0);
        float ls1 = linesensor.analogLineSensor(1);
        float ls2 = linesensor.analogLineSensor(2);
        float ls3 = linesensor.analogLineSensor(3);
        float ls4 = linesensor.analogLineSensor(4);
        //        Serial.print(ls0);
        //        Serial.print(ls1);
        //        Serial.print(ls2);
        //        Serial.print(ls3);
        //        Serial.println(ls4);
        //        Serial.print(global_X);
        //        Serial.print("X");
        //        Serial.print(",");
        //        Serial.print(global_Y);
        //        Serial.print("Y");
        //        Serial.print(",");
        //        Serial.print(global_theta);
        //        Serial.println("theta");
        //        motor.turn_to(2*PI, elapsed_ts, 12);

      } else if (state == TO_LINE | state == OUT) {

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

      } else if (state == RETURN_HOME) {

        // calculate distance travelled
        if ((abs(global_X) + abs(global_Y)) > 50) {

          motor.turn_to( -PI / 2 - (atan(global_X / global_Y)), elapsed_ts, 12);

        } else {
          motor.stop_robot();
        }

      }
    }
};



#endif
