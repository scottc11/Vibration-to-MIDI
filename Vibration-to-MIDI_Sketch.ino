

const int BUTTON_LEFT = 9; // MIDI note DOWN button set to Digital Pin 9
const int BUTTON_RIGHT = 8; // MIDI note UP button set to Digital Pin 8

int buttonLED = 13;

// MIDI note naming
char noteArray[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int noteArrayLength = 7;
int noteIndex = 0;  // for accessing NOTES[] array
char note = noteArray[noteIndex];  //default note on startup will be A1
int noteOctave = 4;  // this is the middle octave for midi


// boolean expressions to ensure button presses only run their functions once
bool buttonRightPressed = false;  
bool buttonLeftPressed = false;



void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_LEFT, INPUT);
  

}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  //  int piezoReading = analogRead(PIEZO_PIN);
  //  int velocity = map(piezoReading, 0, 1023, 0, 127);  // convert reading to a velocity value (Between 0 - 127)

  // BUTTON READINGS

  // NOTE UP
  changeNote(BUTTON_RIGHT, buttonRightPressed, digitalRead(BUTTON_RIGHT), buttonLED);
  
  // NOTE DOWN
  changeNote(BUTTON_LEFT, buttonLeftPressed, digitalRead(BUTTON_LEFT), buttonLED);
  
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
      buttonRightPressed = false;
      buttonLeftPressed = false;
    }
    
  }
  
  //If button IS pressed
  if (buttonState == HIGH) {

    // boolean expression so function only runs once
    if (!buttonPressedBool) {
      
      if (buttonPin == BUTTON_RIGHT) {
        noteIndex += 1;
        buttonRightPressed = true;
        changeOctave();
      }
      if (buttonPin == BUTTON_LEFT) {
        noteIndex += -1;
        buttonLeftPressed = true;
        changeOctave();
      }
      
    }
  }
}


//change the noteOctave accordingly when noteIndex exceeds the size of noteArray


void changeOctave() {

  if (buttonRightPressed == true) {
    if (noteIndex > noteArrayLength - 1) {
      noteIndex = 0;
      noteOctave += 1;
    }
  }

  if (buttonLeftPressed == true) {
    if (noteIndex < 0) {
      noteIndex = 6;
      noteOctave -= 1;
    }
  }
}





