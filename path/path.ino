const int capteurG = 4;
const int capteurC = 3;
const int capteurD = 2;
bool etatCapteurG;
bool etatCapteurC;
bool etatCapteurD;

//les broches de l'Arduino 
const int ENA = 9;
const int IN1 = 10;
const int IN2 = 11;
const int IN3 = 6;
const int IN4 = 7;
const int ENB = 5;

void setup() {
  
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(capteurG, INPUT);
  pinMode(capteurC, INPUT);
  pinMode(capteurD, INPUT);
  
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
void stop(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
void loop() {
  delay(1000);
  etatCapteurG = digitalRead(capteurG);
  etatCapteurC = digitalRead(capteurC);
  etatCapteurD = digitalRead(capteurD);
  if(etatCapteurC){
      
      if ((etatCapteurG) && (!etatCapteurD)){    
      Serial.println("Tourner à gauche");
      left(); 
    }
    
      else if ((!etatCapteurG) && (etatCapteurD)){
      Serial.println("Tourner à droite");
      right();
    }
    
      else { 
      Serial.println("Continuer tout droit");
      forward();
    }
  }
  else {
  
    if ((etatCapteurG) && (!etatCapteurD)){
      Serial.println("Tourner à gauche");
      left();
    }
    
    else if ((!etatCapteurG) && (etatCapteurD)){ 
      Serial.println("Tourner à droite");
      right();
    }
    
    else {  
      Serial.println("Arrêt du véhicule");
      stop();
  }
}
  // go forth
  // forward();
  // delay(2000);
  // left();
  // delay(2000);      
  // right();
  //   delay(2000);      

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}