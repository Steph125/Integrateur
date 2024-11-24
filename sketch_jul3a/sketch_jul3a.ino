

//les broches de l'Arduino 
const int ENA = 9;
const int IN1 = 10;
const int IN2 = 11;
const int IN3 = 6;
const int IN4 = 7;
const int ENB = 5;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // speed ini, equals 0
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void forward(){
  digitalWrite(IN1, HIGH);
  // digitalWrite(IN2, HIGH);
  // digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);  
}
void right(){
    digitalWrite(IN4, HIGH);  

}
void left(){
    digitalWrite(IN1, HIGH);  

}
void loop() {
  // go forth
  // forward();
  delay(2000);
  left();
  delay(2000);      
  right();
    delay(2000);      

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}