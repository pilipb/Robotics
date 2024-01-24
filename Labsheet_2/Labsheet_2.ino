// Powering motors labsheet
#include "math.h"

// analogueWrite(255) = 5v, 0 = 0v and PWM in between

// minimum PWMs
// forwards = 14
// backwards = 17

# define L_PWM_PIN 10
# define L_DIR_PIN 16
# define R_PWM_PIN 9
# define R_DIR_PIN 15

# define FWD HIGH // Remember notation
# define REV LOW

int speed = 0;
boolean dir_backwards = false;

void circle(int size) {
  // go in a circle radius size
  analogWrite( L_PWM_PIN, speed * sin(size + 10));
  analogWrite( R_PWM_PIN, speed * sin(size ));

}

// Runs once.
void setup() {

  // Set all the motor pins as outputs.
  // There are 4 pins in total to set.
  // ...
  pinMode( L_PWM_PIN, OUTPUT);
  pinMode( R_PWM_PIN, OUTPUT);
  pinMode( R_DIR_PIN, OUTPUT);
  pinMode( L_DIR_PIN, OUTPUT);

  // Set initial direction (HIGH/LOW)
  if (dir_forwards = true) {
    analogWrite( L_DIR_PIN, FWD); // l direction dictates forward
    analogWrite( R_DIR_PIN, REV);
  } else {
    analogWrite( L_DIR_PIN, REV); // l direction dictates forward
    analogWrite( R_DIR_PIN, FWD);
  }

  // Initial speed
  analogWrite( L_PWM_PIN, speed);
  analogWrite( R_PWM_PIN, speed);

  // Start serial, send debug text.
  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");
}

// Repeats.
void loop() {

  // Add code to set the direction of rotation
  // for the left and right motor here.

  analogWrite( L_PWM_PIN, speed );
  analogWrite( R_PWM_PIN, speed );
  Serial.println("Speed: " + String(speed));
  //  circle(10);
  speed++;

  // An empty loop can block further uploads.
  // A small delay to prevent this for now.
  delay(2000);
}
