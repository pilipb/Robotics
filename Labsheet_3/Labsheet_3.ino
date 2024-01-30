
#include "linesensor.h"
#include "motors.h"

Motors_c motor;
LineSensor_c linesensor;



// The pin used to activate the IR LEDs
#define EMIT_PIN 11

void setup() {


  linesensor.initialise();
//  motor.initialise();

  // Configure the Serial port
  Serial.begin(9600);

}

void loop() {


//  int dir;
//  dir = linesensor.updateDir();
//  motor.turn(dir * 20);
//  delay(20);
//  // go forward
//  motor.setMotorPower(20,20);
//  Serial.print(" dir: " + String(dir) );
//  Serial.print( "\n" );
  Serial.println("reading: " + String(reading));

  delay(100);
}
