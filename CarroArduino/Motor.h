class Motor{
  int In1;
  int In2;
  int Power; //Regula la velocidad

  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  public:
  Motor(int A, int B, int PWR){
    In1 = A;
    In2 = B;
    Power = PWR;
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(Power, OUTPUT);
    
    previousMillis = 0;
  }

  void adelante (int velocidad){
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    analogWrite(Power, velocidad); //aqui hay problema
  }
  void atras (int velocidad){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(Power, velocidad); //aqui hay problema
  }
  void parar (){
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(Power, LOW);
  }

  void Update(){
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
    }
  }
};
