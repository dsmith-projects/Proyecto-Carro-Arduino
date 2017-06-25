#include "Pitches.h" //created by Tom Igoe
#include "Motor.h"
#include "Sensor.h"

Motor M1 (13,12,11);
Motor M2 (8,9,10);
int LED = 7;// LED pin attached to Arduino D7 for bluetooth activity
int incomingByte = 0;// variable to store serial data
int speed_val = 255;// variable to store speed value

//sensores
Sensor S1(2,3);
Sensor S2(4,5);

//Parlante
int speakerOut = 6;

int demoPlay[] = {
    119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,
    115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,
    97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,
    119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,
    100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100
    };

//Musica 1
int melody1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

//Musica 2
int melody2[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
int MAX_COUNT = sizeof(melody2) / 2; // Melody length, for looping.
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
int tone_ = 0;
int beat = 0;
long duration  = 0;

void setup(){
  //TCCR2B = TCCR2B & 0b11111000 | 0x01; // change PWM frequency for pins 3 and 11 to 32kHz so there will be no motor whining
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  musica1();
  M1.adelante(255);
  M2.atras(255);
  delay(500);
}

void loop(){
  if (Serial.available() > 0) { // check for serial data
    incomingByte = Serial.read(); // read the incoming byte: 
    digitalWrite(LED, HIGH);// Blink LED and print serial data received.
    Serial.print("Received: "); // say what you got:
    Serial.println(incomingByte);
    delay(10); // delay 10 milliseconds to allow serial update time
    
    if (incomingByte == 118){ // es "v" para demo mode
      speed_val = 255;
      demo();
    }
    else {
      movimiento(incomingByte); //escoge movimiento
    }
    
  }else{
    M1.parar();
    M2.parar();
    digitalWrite(LED, LOW);
  }
}

//Test de velocida en el momento x
void test_speed(){
  if (speed_val > 250){
    speed_val = 255;
    Serial.println(" MAX ");
  }
  if (speed_val < 0){
    speed_val = 0;
    Serial.println(" MIN ");
  }
}

//Esto se encarga de la logica del movimiento
void movimiento(int keystroke){
  if (keystroke == 122){ // if byte is equal to "122" or "z" - raise speed
    speed_val = speed_val + 5;
    test_speed();
    Serial.println(speed_val);
  }else if (keystroke == 120){ // if byte is equal to "120" or "x" - lower speed
    speed_val = speed_val - 5;
    test_speed();
    Serial.println(speed_val);
  }else if (keystroke == 99){ // if byte is equal to "99" or "c" - max speed
    speed_val = 255;
    test_speed();
  }else if (keystroke == 119){// if byte is equal to "119" or "w", go forward
    M1.adelante(speed_val);
    M2.adelante(speed_val); 
    sensor(S1,1);
    delay(25);
  }else if (keystroke == 115){// if byte is equal to "115" or "d", go reverse
    M1.atras(speed_val);
    M2.atras(speed_val);
    sensor(S2,2);
    delay(25);
  }else if (keystroke == 97){ // if byte is equal to "97" or "a", go left
    M1.adelante(speed_val);
    M2.atras(speed_val);
    delay(25);
  }else if (keystroke == 100){// if byte is equal to "100" or "s", go right
    M1.atras(speed_val);
    M2.adelante(speed_val);
    delay(25);
  }
  else {
    M1.parar();
    M2.parar();
  }
}

void demo(){
  musica2();
  for (int i = 0; i < (sizeof(demoPlay)/2) ;i++){
    movimiento(demoPlay[i]);
  }
}


///////Sensor ultrasonico
void sensor(Sensor sonic,int direccion){
  long duration, distance;
  digitalWrite(sonic.trig, LOW);
  delayMicroseconds(2);
  digitalWrite(sonic.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonic.trig, LOW);
  duration = pulseIn(sonic.echo, HIGH);
  distance = (duration/2) / 29.1;

  if (distance <= 15){
    if (direccion == 1){
      Serial.print("Retroceder ");
      Serial.print(distance);
      Serial.println(" cm");
      M1.parar();
      M2.parar();
      tono3();
      delay(500);
      M1.atras(255);
      M2.atras(255);
      delay(1000);
      M1.adelante(255);
      M2.atras(255);
      delay(2000);
    }
    if (direccion == 2){
      Serial.print("Avanzar ");
      Serial.print(distance);
      Serial.println(" cm");
      M1.parar();
      M2.parar();
      tono3();
      delay(500);
      M1.adelante(255);
      M2.adelante(255);
      delay(1000);
      M1.atras(255);
      M2.adelante(255);
      delay(2000);
    }
  }else {
    Serial.print(" | ");
    Serial.print(distance);
    Serial.println(" cm - Todo bien");
  }
}


////////MUSIC//////

void musica1(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerOut, melody1[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(speakerOut);
  }
}

void musica2(){
    for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody2[i];
    beat = beats[i];
    duration = beat * 10000; // Set up timing
    playTone(); 
    delayMicroseconds(1000);
  }
}
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) {
    while (elapsed_time < duration) {
      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}
void tono3(){
  for (int i=1000; i>0; i--){
    digitalWrite(speakerOut, HIGH);
    delayMicroseconds(i);
    digitalWrite(speakerOut, LOW);
    delayMicroseconds(i);
  }
  delay(100);
}

void tono4(){
  for (int i=0; i<1000; i++){
    digitalWrite(speakerOut, HIGH);
    delayMicroseconds(i);
    digitalWrite(speakerOut, LOW);
    delayMicroseconds(i);
  }
  delay(100);
}

