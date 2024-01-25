
#define EMIT_PIN 11
#define LS_PIN_1 12 // line sensor 1
#define LS_PIN_2 A0
#define LS_PIN_3 A2
#define LS_PIN_4 A3
#define LS_PIN_5 A4

int ls_pins[5] = { LS_PIN_1, LS_PIN_2, LS_PIN_3, LS_PIN_4 , LS_PIN_5 };


#define MAX_SAMPLES 10
float results[ MAX_SAMPLES ];

float readLineSensor(int sensorNumber) {
  //  function to read ls 1-5 and output float val
  //  12, A0, A2, A3, A4
  if (sensorNumber < 0 || sensorNumber > 4) {
    // Invalid sensor number, handle error or return a specific value
    Serial.println("Invalid sensor number");
    return 0;
  }
  int sensorPin = ls_pins[sensorNumber];

  pinMode( EMIT_PIN, OUTPUT ); // if its input uses ambient light
  digitalWrite( EMIT_PIN, HIGH ); // turns on IR

  pinMode( sensorPin, OUTPUT );
  digitalWrite( sensorPin, HIGH ); // charges capacitor
  delayMicroseconds( 10 ); // delay to charge

  unsigned long start_time = micros();
  pinMode( sensorPin, INPUT );
  while (digitalRead( sensorPin) == HIGH) {
    // Do nothing here (waiting).
    //
    //    //    time out check:
    if (micros() - start_time >= 30000) {
      // time out happens because not enough IR reflecting
      // (not on surface = 2400 with IR)

      break;
    }

  }
  unsigned long end_time = micros();

  pinMode(EMIT_PIN, INPUT);

  unsigned long elapsed_time = end_time - start_time;
  return (float)elapsed_time;
}


void setup() {

  // Set some initial pin modes and states
  pinMode( EMIT_PIN, OUTPUT ); // Set EMIT as an input (off)

  // Start Serial, wait to connect, print a debug message.
  Serial.begin(9600);
  delay(1500);
  Serial.println("***RESET***");

}


void loop() {

  float elapsed_time = readLineSensor(3);
  Serial.println(elapsed_time);
  delay(500);

  //
  for (int i = 0; i < MAX_SAMPLES; i++) {
    results[i] = readLineSensor(0);
    delay(200);
  }

  while ( true ) {
    Serial.println("Results: ");
    for ( int i = 0; i < MAX_SAMPLES; i++ ) {
      Serial.println( results[i] );
    }
    delay(1000);
  }

}
