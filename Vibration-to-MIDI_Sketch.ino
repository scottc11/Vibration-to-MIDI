#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


const int BUTTON_UP = 8; // MIDI note UP button set to Digital Pin 8
const int BUTTON_DOWN = 9; // MIDI note DOWN button set to Digital Pin 9


int buttonLED = 13;

// MIDI note naming
String noteArray[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
int noteArrayLength = 12;
int noteIndex = 0;  // for accessing NOTES[] array
String note = noteArray[noteIndex];  //default note on startup will be A1
int noteOctave = 4;  // this is the middle octave for midi


// boolean expressions to ensure button presses only run their functions once
bool buttonUpPressed = false;  
bool buttonDownPressed = false;



void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  

}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  //  int piezoReading = analogRead(PIEZO_PIN);
  //  int velocity = map(piezoReading, 0, 1023, 0, 127);  // convert reading to a velocity value (Between 0 - 127)

  // BUTTON READINGS

  // NOTE UP
  changeNote(BUTTON_UP, buttonUpPressed, digitalRead(BUTTON_UP), buttonLED);
  
  // NOTE DOWN
  changeNote(BUTTON_DOWN, buttonDownPressed, digitalRead(BUTTON_DOWN), buttonLED);
  
  Serial.print("INDEX: ");
  Serial.print(noteIndex);
  Serial.print(" -- ");
  Serial.print("OCTAVE: ");
  Serial.print(noteOctave);
  Serial.print(" -- ");
  Serial.print("MIDI_NOTE: ");
  Serial.print(noteArray[noteIndex]);
  Serial.println(noteOctave);
  

  delay(20);
}


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
        noteIndex += 1;
        buttonUpPressed = true;
        changeOctave();
      }
      if (buttonPin == BUTTON_DOWN) {
        noteIndex += -1;
        buttonDownPressed = true;
        changeOctave();
      }
      
    }
  }
}


//change the noteOctave accordingly when noteIndex exceeds the size of noteArray

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





