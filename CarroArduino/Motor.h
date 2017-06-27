class Motor{
  int In1;
  int In2;
  int Power; //Regula la velocidad

public:
  Motor(int A, int B, int PWR){
    In1 = A;
    In2 = B;
    Power = PWR;
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    //pinMode(Power, OUTPUT);
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
};
