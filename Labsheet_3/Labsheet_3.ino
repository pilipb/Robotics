
#include "linesensor.h"

LineSensor_c linesensor;


#define MAX_SAMPLES 10
float results[ MAX_SAMPLES ];


void setup() {

  linesensor.initialise();

  // Start Serial, wait to connect, print a debug message.
  Serial.begin(9600);
  delay(1500);
  Serial.println("***RESET***");

}


void loop() {

  float elapsed_time = linesensor.readLineSensor(3);
  Serial.println(elapsed_time);
  delay(500);

  //
//  for (int i = 0; i < MAX_SAMPLES; i++) {
//    results[i] = readLineSensor(0);
//    delay(200);
//  }

//  while ( true ) {
//    Serial.println("Results: ");
//    for ( int i = 0; i < MAX_SAMPLES; i++ ) {
//      Serial.println( results[i] );
//    }
//    delay(1000);
//  }

}
