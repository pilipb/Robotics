
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

#define EMIT_PIN 11
#define LS_PIN_1 12 // line sensor 1
#define LS_PIN_2 A0
#define LS_PIN_3 A2
#define LS_PIN_4 A3
#define LS_PIN_5 A4

int ls_pins[5] = { LS_PIN_1, LS_PIN_2, LS_PIN_3, LS_PIN_4 , LS_PIN_5 };

// Class to operate the linesensor(s).
class LineSensor_c {
  public:

    // Constructor, must exist.
    LineSensor_c() {

    }

    void initialise() {
      // Set some initial pin modes and states
      pinMode( EMIT_PIN, OUTPUT ); // Set EMIT as an input (off)
      digitalWrite( EMIT_PIN, HIGH ); // turns on IR

      // set pins as resistor
      pinMode(ls_pins[0], INPUT_PULLUP);
      pinMode(ls_pins[1], INPUT_PULLUP);
      pinMode(ls_pins[2], INPUT_PULLUP);
      pinMode(ls_pins[3], INPUT_PULLUP);
      pinMode(ls_pins[4], INPUT_PULLUP);
    }


    int updateDir() {
      // function to read the middle three sensors and as a result return whether the
      // robot should turn left -1, right 1, straight 0

      // scenario 1: all sensors on the line, return 0
      if (onLine(1) && onLine(2) && onLine(3)) {
        return 0; // going straight along line
      }
      if (not onLine(1) && onLine(2) && onLine(3)) {
        // too far left, should turn right
        return 1;
      }
      if (onLine(1) && onLine(2) && not onLine(3)) {
        // too far right, should turn left
        return -1;
      } else {
        // error state (line finished)
        return 0;
      }

    }

    boolean onLine(int sensorNumber) {
      // returns whether the given sensor is on the line (true)
      //      or not
      float val = analogLineSensor(sensorNumber);
      if (val > 600) {
        return true;
      } else {
        return false;
      }
    }

    int analogLineSensor(int sensorNumber) {
      int val;
      val = analogRead(sensorNumber);
      return val;
    }



};



#endif
