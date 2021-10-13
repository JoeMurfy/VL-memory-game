#define DEBUG

// How many buttons we use. Currently 5: Red, Blue, Green, Yellow and White
const byte NUM_OF_BUTTONS = 5;
// What pins the buttons go to on arduino.
const byte BUTTON_PINS[NUM_OF_BUTTONS] = {6, 5, 4, 3, 2};
// Length of correct code. Currently 5 as only 5 lights on wall.
const byte CODE_LENGTH = 5;
// SET CORRECT COLOUR ORDER HERE.
const byte CORRECT_CODE[CODE_LENGTH] = {0, 1, 2, 3, 4};
// What pins the LEDs go to on arduino.
const byte LED_PINS[CODE_LENGTH] = {9, 8};


// Using internal pull-up resistors on buttons therefore when they are not being pressed they should read HIGH.
bool lastButtonState[] = {HIGH, HIGH, HIGH, HIGH};
// What position the code is actually on.
int codePosition = 0;

// Debouncing work around. Increase delay if still bouncing.
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


void setup() {

  // Initialise all buttons connected to pins as pull ups (pulls button pin signal to high rather than floating and causing problems).
  for(int i = 0; i < NUM_OF_BUTTONS; i++){
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }

  // Initialise LEDs as outputs.
  for(int i = 0; i < CODE_LENGTH; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }

  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println(F("Debug begin."));
  #endif
}


void loop() {

  // Check that we've waited at least "debounceDelay" since last input
  if ( (millis() - lastDebounceTime) > debounceDelay) {

    // Read all buttons.
    for(int i = 0; i < NUM_OF_BUTTONS; i++){
      int buttonState = digitalRead(BUTTON_PINS[i]);

      // Debouncing.
      if(buttonState != lastButtonState[i]) {
        lastDebounceTime = millis();
      }

      if(buttonState == LOW && lastButtonState[i] == HIGH) {

        // Checking current button against correct code.
        if(CORRECT_CODE[codePosition] == i) {
          codePosition++;

          #ifdef DEBUG
            Serial.print(F("Correct input! Onto step #"));
            Serial.println(codePosition);
          #endif
        }
        // Incorrect so resets code and turns flashes red LED.
        else {
          codePosition = 0;
          digitalWrite(LED_PINS[0], HIGH);
          delay(10);
          digitalWrite(LED_PINS[0], LOW);
          Serial.println(F("Incorrect"));
        }
      }

      // Debouncing
      lastButtonState[i] = buttonState;
    }
  }

  // Check if colour order entered is correct then calls reward function.
  if(codePosition == CODE_LENGTH){
    reward();
  }

}

// Function for when colour order entered correctly.
void reward(){

  #ifdef DEBUG
    Serial.println(F("Puzzle Solved!"));
  #endif

  // Turn on Green LED
  digitalWrite(LED_PINS[1], HIGH);
}
