
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
    }




    float readLineSensor(int sensorNumber) {
      //  function to read ls 1-5 and output float val index 0
      //  12, A0, A2, A3, A4
      if (sensorNumber < 0 || sensorNumber > 4) {
        // Invalid sensor number, handle error or return a specific value
        Serial.println("Invalid sensor number");
        return 0;
      }
      int sensorPin = ls_pins[sensorNumber];

      pinMode( sensorPin, OUTPUT );
      digitalWrite( sensorPin, HIGH ); // charges capacitor
      delayMicroseconds( 10 ); // delay to charge

      unsigned long start_time = micros();
      pinMode( sensorPin, INPUT );
      while (digitalRead( sensorPin) == HIGH) {
        // Do nothing here (waiting).
        //
        //    //    time out check:
        if (micros() - start_time >= 30000) {
          // time out happens because not enough IR reflecting
          // (not on surface = 2400 with IR)

          break;
        }

      }
      unsigned long end_time = micros();

      pinMode(EMIT_PIN, INPUT);

      unsigned long elapsed_time = end_time - start_time;
      return (float)elapsed_time;
    }




};



#endif
