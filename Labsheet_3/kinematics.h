// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _KINEMATICS_H
#define _KINEMATICS_H
//#include "math"

// define global variables
float global_X = 0;
float global_Y = 0;
float global_theta = 0;

float l = 42.5; // mm
float r = 16; // mm

float step_mm0 = PI * 2 * r / 358;
float step_mm1 = PI * 2 * r / 358; // confirm value


// Class to track robot position.
class Kinematics_c {
  public:

    // Constructor, must exist.
    Kinematics_c() {

    }

    void initialise() {
      global_X = 0;
      global_Y = 0;
      global_theta = 0;
    }

    void update(long e0_dist, long e1_dist) {

      // e0 is right wheel, e1 is left net distance
      // update X and Y
      e0_dist = e0_dist * step_mm0;
      e1_dist = e1_dist * step_mm1;

      float X_dot = 0.5 * (e0_dist + e1_dist);
      global_X = global_X + (X_dot * cos(global_theta));
      global_Y = global_Y + (X_dot * sin(global_theta));

      // update theta
      float theta_dot =  (e1_dist - e0_dist) / (2*l);
      global_theta = global_theta + theta_dot;

      //      Serial.println("X: " + String(global_X));
      //      Serial.println("Y: " + String(global_Y));
      Serial.println("Angle: " + String(global_theta));

    }

};



#endif
