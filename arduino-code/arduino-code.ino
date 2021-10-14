#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

#define DEBUG
//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Function declaration
void sequenceCorrectLCD();
void enterSequenceLCD();
void reward();
void clearLCD();

// How many buttons we use. Currently 5: Red, Blue, Green, Yellow and White
const byte NUM_OF_BUTTONS = 5;
// What pins the buttons go to on arduino.
const byte BUTTON_PINS[NUM_OF_BUTTONS] = {45, 47, 49, 51, 53};
// Length of correct code. Currently 5 as only 5 lights on wall.
const byte CODE_LENGTH = 5;
// SET CORRECT COLOUR ORDER HERE.
const byte CORRECT_CODE[CODE_LENGTH] = {0, 1, 2, 3, 4};
// What pins the LEDs go to on arduino.
const byte LED_PINS[CODE_LENGTH] = {39, 41};


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

  
  // Initialise LCD and set black.
  mylcd.Init_LCD();
  clearLCD();
  Serial.println(mylcd.Read_ID(), HEX);
  enterSequenceLCD();

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
          digitalWrite(LED_PINS[1], HIGH);
          delay(40);
          digitalWrite(LED_PINS[1], LOW);
          #ifdef DEBUG
            Serial.print(F("Correct input! Onto step #"));
            Serial.println(codePosition);
          #endif
        }
        // Incorrect so resets code and turns flashes red LED.
        else {
          codePosition = 0;
          digitalWrite(LED_PINS[0], HIGH);
          delay(40);
          digitalWrite(LED_PINS[0], LOW);
          clearLCD();
          mylcd.Set_Rotation(1);
          mylcd.Set_Text_colour(WHITE);
          mylcd.Set_Text_Back_colour(RED);
          mylcd.Set_Text_Size(8);
          mylcd.Print_String("      ", CENTER, 200);
          mylcd.Print_String("      ", CENTER, 240);
          mylcd.Print_String(" XXXXX ", CENTER, 220);
          Serial.println(F("Incorrect"));
          delay(100);
        }
      }

      // Debouncing
      lastButtonState[i] = buttonState;
    }
  }

//  if (codePosition == 1){
//    mylcd.Print_String(" *____ ", CENTER, 220);
//  }
//  else if (codePosition == 2){
//    mylcd.Print_String(" _*___ ", CENTER, 220);
//  }
//  else if (codePosition == 3){
//    mylcd.Print_String(" __*__ ", CENTER, 220);
//  }
//  else if (codePosition == 4){
//    mylcd.Print_String(" ___*_ ", CENTER, 220);
//  }
//  else if (codePosition == 5){
//    mylcd.Print_String(" ____* ", CENTER, 220);
//  }

  // Check if colour order entered is correct then calls reward function.
  if(codePosition == CODE_LENGTH){
    while(true){
    reward();
    }
  }

}

// Function for when colour order entered correctly.
void reward(){

  #ifdef DEBUG
    Serial.println(F("Puzzle Solved!"));
  #endif

  // Turn on Green LED
  digitalWrite(LED_PINS[1], HIGH);
  clearLCD();
  sequenceCorrectLCD();
}

void enterSequenceLCD(){
  
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(9);
  mylcd.Print_String("ENTER", CENTER, 30);
  mylcd.Print_String("SEQUENCE", CENTER, 110);
  
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Back_colour(RED);
  mylcd.Set_Text_Size(5);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String("      ", CENTER, 200);
  mylcd.Print_String("      ", CENTER, 240);
  mylcd.Print_String(" _____ ", CENTER, 220);

  delay(10000);
}
//Function to display reward on LCD.
void sequenceCorrectLCD(){
  
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);
  mylcd.Set_Text_colour(YELLOW);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(9);
  mylcd.Print_String("SEQUENCE", CENTER, 30);
  mylcd.Print_String("CORRECT", CENTER, 110);
  
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(YELLOW);
  mylcd.Set_Text_Size(5);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String("      ", CENTER, 200);
  mylcd.Print_String("      ", CENTER, 240);
  mylcd.Print_String(" 6598 ", CENTER, 220);
  delay(100000);

}

void clearLCD(){
    mylcd.Fill_Screen(BLACK);
}
