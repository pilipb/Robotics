#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"
#include "math.h"


#define BUZZER_PIN 6 // Pin for analogue input
#define LED_PIN 13  // Pin to activate the orange LED
boolean led_state;  // Variable to "remember" the state
                    // of the LED, and toggle it.

boolean buzz_state;

int number_flash = 0;
int freq = 1;
int duration = 200;


float a;
float b;
float c;

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

  //Start a serial connection
  Serial.begin( 9600 );

  // Wait for stable connection, report reset.
  delay(1000);
  Serial.println("***RESET***");

  a = TWO_PI;
  b = a;
  c = b;
  
}



// put your main code here, to run repeatedly:
void loop() {
  
  a += 0.01;
  b = sin( a * 20 );
  c = cos( a * 10 );

  Serial.print( a );
  Serial.print( ",");
  Serial.print( b );
  Serial.print( ",");
  Serial.print( c );

  Serial.print( "\n" );   // Finish with a newline
  //Serial.println( "" ); // either of these two work.

  delay(50);

  
}
