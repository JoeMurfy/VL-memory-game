#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DEBUG
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for 20 chars/4 line display.


// How many buttons we use. Currently 5: Red, Blue, Green, Yellow and White
const byte NUM_OF_BUTTONS = 5;

// Length of correct code. Currently 5 as only 5 lights on wall.
const byte CODE_LENGTH = 5;

// What pins the LEDs and buttons go to on arduino. 
const byte LED_PINS[CODE_LENGTH] = {12, 11, 10, 9, 8};
const byte BUTTON_PINS[NUM_OF_BUTTONS] = {6, 5, 4, 3, 40};

// SET CORRECT COLOUR ORDER HERE.
const byte CORRECT_CODE[CODE_LENGTH] = {0, 1, 2, 3, 4};


// Using internal pull-up resistors on buttons therefore when they are not being pressed they should read HIGH.
bool lastButtonState[] = {HIGH, HIGH, HIGH, HIGH};
// What position the code is actually on.
int codePosition = 0;

// Debouncing work around.
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


void setup() {

  // Initialise the LCD and prints prompt.
  lcd.begin();
  lcd.backlight();
  lcd.print("INPUT COLOUR ORDER");


  // Initialise all buttons connected to pins as pull ups (pulls button pin signal to high rather than floating and causing problems).
  for(int i = 0; i < NUM_OF_BUTTONS; i++){
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  
  // Initialise the LED pins that show progress through the sequence 
  for(int i = 0; i < CODE_LENGTH; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }

  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println(F("Debug started"));
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
        // Incorrect so resets code.
        else {
          codePosition = 0;
          Serial.println(F("Incorrect input! Back to the beginning!"));
      }
     
      // Debouncing
      lastButtonState[i] = buttonState;
    }
   
  }

  // Check if code entered is correct.
  if(codePosition == CODE_LENGTH){
    reward();
    Serial.println("correctcodee");
  }
 }
}

// Function for when they enter the correct colour code.
void reward(){
  // Show reward code and congratulations on screen.
  lcd.clear();
  lcd.home();
  lcd.print("COLOUR ORDER CORRECT");
  lcd.setCursor(0, 1);
  lcd.setCursor(8, 2);
  lcd.print("6598");
  Serial.println("Correctcode");
}
