
const int PIEZO_PIN = A2; // Piezo output set to Anolog 2
const int BUTTON_LEFT = 9; // MIDI note DOWN button set to Digital Pin 9
const int BUTTON_RIGHT = 8; // MIDI note UP button set to Digital Pin 8



char NOTES[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int noteNum = 0;  //for accessing NOTES[] array
char note = NOTES[noteNum];  //default note on startup will be A1
int noteOctave = 1;
bool buttonRightPressed = false;
bool buttonLeftPressed = false;
int buttonRightLED = 6;
int buttonLeftLED = 7;

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(6, OUTPUT); // MIDI Shield LED on pin 6
  pinMode(7, OUTPUT); // MIDI Shield LED on pin 7

}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  int piezoReading = analogRead(PIEZO_PIN);
  int velocity = map(piezoReading, 0, 1023, 0, 127);  // convert reading to a velocity value (Between 0 - 127)

  // BUTTON READINGS

  // NOTE UP
  changeNote(BUTTON_RIGHT, buttonRightPressed, digitalRead(BUTTON_RIGHT), buttonRightLED);
  // NOTE DOWN
  changeNote(BUTTON_LEFT, buttonLeftPressed, digitalRead(BUTTON_LEFT), buttonLeftLED);

  
  
  // PIEZO READINGS
  // Serial.println(piezoReading); // Print the velocity
  
  if (piezoReading > 10 && piezoReading < 20) {
    Serial.println("---- SMALL vibration  --------");
  }
  if (piezoReading >= 20 && piezoReading < 50) {
    Serial.println("=============================== MEDIUM vibration ========");
  }
  if (piezoReading >= 50 && piezoReading < 100) {
    Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ BIG vibration ++++++++++");
  }
  
  Serial.print(noteNum);
  Serial.println("NOTE: ");

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
    
    // turn led off
    digitalWrite(ledPin, HIGH); // LED OFF
  }
  
  //If button IS pressed
  if (buttonState == HIGH) {

    // boolean expression so function only runs once
    if (!buttonPressedBool) {
      
      if (buttonPin == BUTTON_RIGHT) {
        noteNum += 1;
        buttonRightPressed = true;
      }
      if (buttonPin == BUTTON_LEFT) {
        noteNum += -1;
        buttonLeftPressed = true;
      }
      
    }
    
    // turn led on
    digitalWrite(ledPin, LOW);  // LED ON
  }
}



