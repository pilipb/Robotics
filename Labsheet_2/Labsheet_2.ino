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

int speed = 45;
boolean dir_forwards = true;
unsigned long startTime;

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
  pinMode( L_PWM_PIN, OUTPUT);
  pinMode( R_PWM_PIN, OUTPUT);
  pinMode( R_DIR_PIN, OUTPUT);
  pinMode( L_DIR_PIN, OUTPUT);

  set_dir(dir_forwards);

  // Start serial, send debug text.
  Serial.begin(9600);
  startTime = millis();

}

// Repeats.
void loop() {

  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  if (elapsedTime >= 5000) {
    Serial.println("Time: " + String(elapsedTime));
    while (1) {
      analogWrite( L_PWM_PIN, 0 );
      analogWrite( R_PWM_PIN, 0 );
    }
    return;
  }

  analogWrite( L_PWM_PIN, speed );
  analogWrite( R_PWM_PIN, speed );

  delay(50);
}
