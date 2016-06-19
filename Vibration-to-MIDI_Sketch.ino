
const int PIEZO_PIN = A2; // Piezo output set to Anolog 2
const int BUTTON_LEFT = 9; // MIDI note DOWN button set to Digital Pin 9
const int BUTTON_RIGHT = 8; // MIDI note UP button set to Digital Pin 8



char NOTES[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int noteNum = 0;  //for accessing NOTES[] array
char note = NOTES[noteNum];  //default note on startup will be A1
int noteOctave = 1;
bool buttonRightPressed = false;
bool buttonLeftPressed = false;

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
  if (digitalRead(BUTTON_RIGHT) == LOW) {

    // boolean expression so function only runs once
    if (buttonRightPressed == true) {
      buttonRightPressed = false;
    }
    digitalWrite(6, HIGH); // LED OFF
  }
  if (digitalRead(BUTTON_RIGHT) == HIGH) {

    // boolean expression so function only runs once
    if (!buttonRightPressed) {
      noteNum += 1;
      buttonRightPressed = true;
    
    }
    digitalWrite(6, LOW);  // LED ON
  }

  // NOTE DOWN
  if (digitalRead(BUTTON_LEFT) == LOW) {
    // boolean expression so function only runs once
    if (buttonLeftPressed == true) {
      buttonLeftPressed = false;
    }
    digitalWrite(7, HIGH);  // LED OFF
  }
  if (digitalRead(BUTTON_LEFT) == HIGH) {
    // boolean expression so function only runs once
    if (!buttonLeftPressed) {
      noteNum += -1;
      buttonLeftPressed = true;
    
    }
    digitalWrite(7, LOW);  // LED ON
  }
  
  
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






