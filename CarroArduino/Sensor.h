class Sensor{
  
public:
  int trig;
  int echo;

  Sensor(int x, int y){
    trig = x;
    echo = y;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
  }
};
