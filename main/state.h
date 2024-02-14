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
#define TURN_RIGHT 5
#define TURN_LEFT 6
#define RETURN_HOME 7
#define OUT 8
#define CROSS 9

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
      if (state == OUT && (millis() - start_time) > 800) {

        state = TO_LINE;

      } else if (state == TO_LINE && online0 && online1 && online2 && online3 && online4) {
        motor.stop_robot();
        state = JOIN_LINE;
        prev_state = TO_LINE;

        // join line by rotating
      } else if (state == JOIN_LINE && (abs(global_theta) > (PI / 2))) {

        state = FOLLOW_LINE;
        prev_state = JOIN_LINE;
        last_angle = global_theta;

      } else if (state == CROSS && (abs(global_theta - last_angle) > PI / 2)) {

        state = FOLLOW_LINE;

      } else if (state == FOLLOW_LINE && (online0 + online1 + online2 + online3 + online4 == 5) ) {

        state = CROSS;
        last_angle = global_theta;

      } else if (state == FOLLOW_LINE && online0 == 0 && (online1 + online2 + online3 + online4 == 4)) {

        state = TURN_RIGHT;
        last_angle = global_theta;

      } else if (state == FOLLOW_LINE && online4 == 0 && (online0 + online1 + online2 + online3 == 4)) {

        state = TURN_LEFT;
        last_angle = global_theta;

      } else if (state == TURN_RIGHT  && (abs(global_theta - last_angle) > PI / 2)) {

        state = FOLLOW_LINE;

      } else if (state == TURN_LEFT && (abs(global_theta - last_angle) > PI / 2)) {

        state = FOLLOW_LINE;

      } else if (state == TURN_AROUND && (abs(global_theta - last_angle) > 0.9 * PI)) {

        state = FOLLOW_LINE;
        prev_state = TURN_AROUND;

      } else if (state == TURN_AROUND && (abs(global_theta - last_angle) < PI)) {

        state = TURN_AROUND;

      } else if (state == FOLLOW_LINE  && (online0 + online1 + online2 + online3 + online4 == 0)) {

        if ((millis() - start_time) > 10000 | (abs(global_X) + abs(global_Y) > 1100)) {

          state = RETURN_HOME;
          dist_x = global_X;
          dist_y = global_Y;
          last_angle = global_theta;

        } else if (online0 + online1 + online2 + online3 + online4 == 0) {

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
        Serial.print(ls0);
        Serial.print(ls1);
        Serial.print(ls2);
        Serial.print(ls3);
        Serial.println(ls4);
        //        Serial.print(global_X);
        //        Serial.print("X");
        //        Serial.print(",");
        //        Serial.print(global_Y);
        //        Serial.print("Y");
        //        Serial.print(",");
        //        Serial.print(global_theta);
        //        Serial.println("theta");

        motor.turn_to(PI, elapsed_ts, 25);

      } else if (state == TO_LINE | state == OUT) {

        // if the state is to_line just drive forward
        motor.setMotorPower(30, 30);

      } else if (state == JOIN_LINE) {

        motor.turn_left();

      } else if (state == FOLLOW_LINE) {

        float dir = linesensor.weightFollow();
        motor.stayOnLine(dir, 40);

      } else if (state == TURN_AROUND) {

        motor.turn_left_spot(); // function turns on the spot

      } else if (state == TURN_RIGHT | state == CROSS) {

        motor.turn_right();

      } else if (state == TURN_LEFT) {

        motor.turn_left();

      } else if (state == RETURN_HOME) {

        if (abs(global_X) + abs(global_Y) > 15) {

          float angle;
          if (global_Y != 0) {
            angle = atan2(-global_Y, -global_X); // Calculate the angle correctly using atan2
          } else if (global_X < 0) {
            angle = 0; // Facing directly opposite if global_Y == 0 and global_X < 0
          } else {
            angle = PI; // Facing directly forward if global_Y == 0 and global_X >= 0
          }

          motor.turn_to(angle, elapsed_ts, 25);

        } else {
          
          motor.stop_robot();
          
        }

      }
    }
};



#endif
