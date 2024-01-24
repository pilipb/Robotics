// Powering motors labsheet
#include "math.h"
#include "motors.h"

Motors_c motors;

void setup() {

  // Set all the motor pins as outputs.
  motors.initialise();

  // Start serial, send debug text.
  Serial.begin(9600);
  Serial.println("**RESET**");
  delay(100);

}

// Repeats.
void loop() {

  motors.setMotorPower(25, 25);
  delay(5000);
  motors.setMotorPower(-25, -25);
  delay(5000);

  motors.stop_robot();


}
