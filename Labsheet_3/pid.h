// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _PID_H
#define _PID_H

float feedback_signal;
float p_gain;
float i_gain;

// Class to contain generic PID algorithm.
class PID_c {
  public:

    // Constructor, must exist.
    PID_c() {

    }

    void initialise(float init_p, float init_i) {

      p_gain = init_p;
      i_gain = init_i;
      
      feedback_signal =  0;

    }

    double update( double demand, double measure){

      double error = demand - measure;
      double p_term = p_gain * error;
      return p_term;

    }

};



#endif
