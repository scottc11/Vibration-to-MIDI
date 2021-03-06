#include <rgb_lcd.h>

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

// GIT BRANCH: midiShield

const int BUTTON_UP = 8; // MIDI note UP button set to Digital Pin 8
const int BUTTON_DOWN = 9; // MIDI note DOWN button set to Digital Pin 9
const int BUTTON_SEND_NOTE = 10;  // Send MIDI Note

int buttonLED = 13;

// MIDI note naming
String noteArray[12] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
int noteArrayLength = 12;
int noteNumber = 60;  // starting at middle C
int noteIndex = 3;  // for accessing NOTES[] array
String note = noteArray[noteIndex];  //default note on startup will be A1
int noteOctave = 3;  // this is the middle octave in Ableton


// boolean expressions to ensure button presses only run their functions once
bool buttonUpPressed = false;  
bool buttonDownPressed = false;
bool noteOn = false;
bool displayChange = false;

// create a MIDI object instance
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

// create a LCD object instance
rgb_lcd lcd;


void setup() 
{
  // MIDI.begin starts the serial port at the MIDI baudrate (31250).
  // Set the input channel at the argument given (if any, else 1).

  // init libraries
  MIDI.begin();
  lcd.begin(16, 2);
  
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_SEND_NOTE, INPUT);

  lcd.print(noteArray[noteIndex]);
  lcd.print(noteOctave);
  
}






void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  //  int piezoReading = analogRead(PIEZO_PIN);
  //  int velocity = map(piezoReading, 0, 1023, 0, 127);  // convert reading to a velocity value (Between 0 - 127)


  // NOTE UP
  changeNote(BUTTON_UP, buttonUpPressed, digitalRead(BUTTON_UP), buttonLED);
  
  // NOTE DOWN
  changeNote(BUTTON_DOWN, buttonDownPressed, digitalRead(BUTTON_DOWN), buttonLED);

  // SEND NOTE   input        bool
  sendNote(BUTTON_SEND_NOTE, noteOn, digitalRead(BUTTON_SEND_NOTE), noteNumber, 100, 1);

  // UPDATE DISPLAY
  updateDisplay();
}






// SEND A MIDI NOTE
void sendNote(int buttonPin, bool noteOnBool, int buttonState, int number, int velocity, int channel) {

  // If button NOT pressed
  if (buttonState == LOW) {
    
    MIDI.sendNoteOff(number, velocity, channel);
    
    // boolean expression so function only runs once
    if (noteOnBool == true) {
      noteOn = false;
    }
  }

  if (buttonState == HIGH) {
    

    if (noteOnBool != true) {
      MIDI.sendNoteOn(number, velocity, channel);
      noteOn = true;

      delay(1000);
    }
    
  }
}




// UPDATE DISPLAY
void updateDisplay() {

  // catching
  if (displayChange == true) {
    lcd.clear();
    lcd.print(noteArray[noteIndex]);
    lcd.print(noteOctave);
    
    displayChange = false;
  }
  
  
}






// CHANGE THE MIDI NOTE BEING SENT
void changeNote(int buttonPin, bool buttonPressedBool, int buttonState, int ledPin) {

  // If button NOT pressed
  if (buttonState == LOW) {
    // boolean expression so function only runs once
    if (buttonPressedBool == true) {
      buttonUpPressed = false;
      buttonDownPressed = false;
    }
    
  }
  
  //If button IS pressed
  if (buttonState == HIGH) {

    // boolean expression so function only runs once
    if (!buttonPressedBool) {
      
      if (buttonPin == BUTTON_UP) {
        noteNumber += 1;
        noteIndex += 1;
        buttonUpPressed = true;
        displayChange = true; // So updateDisplay() can run its code
        changeOctave();
      }
      
      if (buttonPin == BUTTON_DOWN) {
        noteNumber += -1;
        noteIndex += -1;
        buttonDownPressed = true;
        displayChange = true;
        changeOctave();
      } 
    }
  }
}








// CHANGE THE OCTAVE OF A MIDI NOTE
void changeOctave() {

  if (buttonUpPressed == true) {
    if (noteIndex > noteArrayLength - 1) {
      noteIndex = 0;
      noteOctave += 1;
    }
  }

  if (buttonDownPressed == true) {
    if (noteIndex < 0) {
      noteIndex = 11;
      noteOctave -= 1;
    }
  }
}


