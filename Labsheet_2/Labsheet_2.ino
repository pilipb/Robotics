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

# define REV HIGH // Remember notation
# define FWD LOW

int speed = 20;
boolean dir_forwards = true;

void circle(int size) {
  // go in a circle radius size
  analogWrite( L_PWM_PIN, speed * sin(size + 2));
  analogWrite( R_PWM_PIN, speed * sin(size ));

}

void set_dir(boolean forwards) {
  if (forwards) {
    digitalWrite( L_DIR_PIN, FWD);
    digitalWrite( R_DIR_PIN, FWD);
  } else {
    digitalWrite( L_DIR_PIN, REV);
    digitalWrite( R_DIR_PIN, REV);
  }
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

  set_dir(dir_forwards);

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

  //  Serial.println("Speed: " + String(speed));
  //  circle(10);

  // An empty loop can block further uploads.
  // A small delay to prevent this for now.
  delay(5);
}
