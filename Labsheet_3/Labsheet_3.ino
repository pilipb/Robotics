
#define EMIT_PIN 11
#define LS_LEFT_PIN 12 // line sensor 1

#define MAX_SAMPLES 10
float results[ MAX_SAMPLES ];

void setup() {

  // Set some initial pin modes and states
  pinMode( EMIT_PIN, OUTPUT ); // Set EMIT as an input (off)
  pinMode( LS_LEFT_PIN, INPUT );    // Set line sensor pin to input

  // Start Serial, wait to connect, print a debug message.
  Serial.begin(9600);
  delay(1500);
  Serial.println("***RESET***");

} // End of setup()


void loop() {


  pinMode( EMIT_PIN, OUTPUT ); // if its input uses ambient light
  digitalWrite( EMIT_PIN, HIGH ); // turns on IR

  pinMode( LS_LEFT_PIN, OUTPUT );
  digitalWrite( LS_LEFT_PIN, HIGH ); // charges capacitor
  delayMicroseconds( 10 ); // delay to charge



  unsigned long start_time = micros();
  pinMode( LS_LEFT_PIN, INPUT );
  while (digitalRead( LS_LEFT_PIN) == HIGH) {
    // Do nothing here (waiting).
    //
    //    //    time out check:
    //    if (micros() - start_time >= 2400) {
    //          // time out happens because not enough IR reflecting
    //          // (not on surface = 2400 with IR)
    //
    //      break;
    //    }

  }

  unsigned long end_time = micros();

  pinMode(EMIT_PIN, INPUT);

  unsigned long elapsed_time = end_time - start_time;

  for (int i = 0; i < MAX_SAMPLES; i++) {
    // This line is complete, but it needs to be
    // within a for loop construct.  Complete this.
    results[i] = (float)elapsed_time;
    delay(1000);
  }


  // The section below has been completed for you.
  // Use this section to build a similar construct
  // around the code above, which was Algorithm 1.

  // The robot will be "stuck" here forever, because
  // the condition true will never change.
  // Therefore, the robot will Serial Print the
  // results back to your computer every 1000ms.
  while ( true ) {
    Serial.println("Results: ");
    for ( int i = 0; i < MAX_SAMPLES; i++ ) {
      Serial.println( results[i] );
    }
    delay(1000);
  }

} // End of loop()
