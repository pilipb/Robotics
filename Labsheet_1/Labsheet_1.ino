#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

#define BUZZER_PIN 6 // Pin for analogue input
#define LED_PIN 13  // Pin to activate the orange LED
boolean led_state;  // Variable to "remember" the state
                    // of the LED, and toggle it.

boolean buzz_state;

int number_flash = 0;
int freq = 1;
int duration = 200;

void flash_leds () {
  if( led_state == true ) {
      led_state = false;
      Serial.println("flash");
    } else {
      led_state = true;
    }
}

void sound_buzz (int duration) {
  
  if( buzz_state == true ) {
      buzz_state = false;
      digitalWrite( BUZZER_PIN, LOW);
    } else {
      buzz_state = true;
      digitalWrite( BUZZER_PIN, HIGH);
    }
}



// put your setup code here, to run once:
void setup() {

  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

  // Set LED pin as an output
  pinMode( LED_PIN, OUTPUT );
  pinMode( BUZZER_PIN, OUTPUT);

  // Set initial state of the LED
  led_state = false;
}



// put your main code here, to run repeatedly:
void loop() {
  
  freq = freq + 5;
  number_flash ++;

  // We use the variable to set the
  // debug led on or off on the 3Pi+
  digitalWrite( LED_PIN, led_state );

  Serial.println("loop");
  delay(freq);
}
