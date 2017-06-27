unsigned long interval=1000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
int LED = 7;
bool ledState = false; // state variable for the LED
 
void setup() {
 Serial.begin(9600);
 pinMode(LED, OUTPUT);
 digitalWrite(LED, ledState);
}
 
void loop() {
 unsigned long currentMillis = millis(); // grab current time
 Serial.println(currentMillis);
 delay(1000);
 // check if "interval" time has passed (1000 milliseconds)
 if ((unsigned long)(currentMillis - previousMillis) >= interval) {
  
   ledState = !ledState; // "toggles" the state
   digitalWrite(LED, ledState); // sets the LED based on ledState
   // save the "current" time
   previousMillis = millis();
 }
}
