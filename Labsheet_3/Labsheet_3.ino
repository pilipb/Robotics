
#define EMIT_PIN 11
#define LS_LEFT_PIN 12 // line sensor 1


void setup() {

  // Set some initial pin modes and states
  pinMode( EMIT_PIN, INPUT ); // Set EMIT as an input (off)
  pinMode( LS_LEFT_PIN, INPUT );    // Set line sensor pin to input

  // Start Serial, wait to connect, print a debug message.
  Serial.begin(9600);
  delay(1500);
  Serial.println("***RESET***");

} // End of setup()


void loop() {

  // Complete the steps referring to the pseudocode block
  // Algorithm 1.
  // The first steps have been done for you.
  // Fix parts labelled ????
  // Some steps are missing - add these.
  pinMode( EMIT_PIN, OUTPUT );
  digitalWrite( EMIT_PIN, HIGH ); // turns on IR

  pinMode( LS_LEFT_PIN, OUTPUT );
  digitalWrite( LS_LEFT_PIN, HIGH ); // charges capacitor
  
  delayMicroseconds( 10 );

  unsigned long start_time = micros();
  pinMode( LS_LEFT_PIN, INPUT );
  while ( digitalRead( LS_LEFT_PIN) == HIGH ) {
    // Do nothing here (waiting).
  }

  unsigned long end_time = micros();
  unsigned long elapsed_time = end_time - start_time;

  pinMode(EMIT_PIN, INPUT);

  Serial.println( elapsed_time );

} // End of loop()
