// TONES  ==========================================
// Start by defining the relationship between 
//       note, period, &  frequency. 
#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
#define  R     0

int speakerOut = 8;
void setup() { 
  pinMode(8, OUTPUT);
}

int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
long tempo = 10000;
int pause = 1000;
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
int tone_ = 0;
int beat = 0;
long duration  = 0;

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

// LET THE WILD RUMPUS BEGIN =============================
void loop() {
  delay(30000);
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];
    duration = beat * tempo; // Set up timing
    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);
  }
}
