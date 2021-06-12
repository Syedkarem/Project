const int sensor_pin = A0;  /* Soil moisture sensor O/P pin */
#include <Wire.h>
int ledPin = 2;
void setup() {
  pinMode(ledPin, OUTPUT);
  Wire.begin(0x5);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = (100 - ( (sensor_analog/4095.00) * 100 ) ); // calculating moisture level
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);      // printing moisture percentage on serial monitor
  Serial.print("%\n\n");
  delay(1000);
  if (moisture_percentage < 80){          // checking if moisture level is a certain percentage to determine whether LED should be turned on or off
  digitalWrite(ledPin, HIGH);
  Serial.println("PLANTS NEED WATER!!!!");
  }
  if (moisture_percentage >80){
    digitalWrite(ledPin, LOW);
    Serial.println("WATER IS ENOUGH!!!");
  }
}


void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    //digitalWrite(ledPin, c);
  }
}
