/******************************************************************************
Piezo_Vibration_Sensor.ino
Example sketch for SparkFun's Piezo Vibration Sensor
  (https://www.sparkfun.com/products/9197)
Jim Lindblom @ SparkFun Electronics
April 29, 2016

- Connect a 1Mohm resistor across the Piezo sensor's pins.
- Connect one leg of the Piezo to GND
- Connect the other leg of the piezo to A0

Vibrations on the Piezo sensor create voltags, which are sensed by the Arduino's
A0 pin. Check the serial monitor to view the voltage generated.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int PIEZO_PIN = A0; // Piezo output

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  int piezoReading = analogRead(PIEZO_PIN);
  int velocity = map(piezoReading, 0, 1023, 0, 127);  // convert reading to a velocity value (Between 0 - 127)
  Serial.println(piezoReading); // Print the velocity

  
  if (piezoReading > 10 && piezoReading < 20) {
    Serial.println("---- SMALL vibration  --------");
  }
  if (piezoReading >= 20 && piezoReading < 50) {
    Serial.println("=============================== MEDIUM vibration ========");
  }
  if (piezoReading >= 50 && piezoReading < 100) {
    Serial.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ BIG vibration ++++++++++");
  }

  
  delay(20);
}






