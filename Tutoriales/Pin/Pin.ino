/*int ledPin = 7;      // LED connected to digital pin 9

void setup(){
  pinMode(ledPin, OUTPUT);   // sets the pin as output
}
void loop(){
  analogWrite(ledPin, 255);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  delay(1000);
  analogWrite(ledPin, 500);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  delay(1000);
}
*/

int ledPin = 0;

void setup(){
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}

void loop(){
  digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(1000);                  // waits for a second
}
