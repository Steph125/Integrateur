const int capteurg = 4; 
const int capteurm = 3; 
const int capteurd = 2; 
const int IN3 = 6; // L293D - premier moteur pin 1 (Gauche)
const int IN4 = 7; // L293D - premier moteur pin 2 (Gauche)
int ENA = 11;
const int IN2 = 12; // L293D - second moteur pin 1 (Droite)
const int IN1 = 10; // L293D - second moteur pin 2 (Droite)
int ENB = 9; // L293D - les 2 pins enable
char stat1 ,stat2;


void setup() {
  pinMode(capteurg, INPUT); 
  pinMode(capteurm, INPUT);
  pinMode(capteurd, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.begin(9600);
}

void d() // Fonction qui permet au robot de tourner à droite
{
  int in2_val = digitalRead(capteurm); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, HIGH);
  analogWrite(ENA, -100);
  analogWrite(ENB, 100);
  while (in2_val == LOW){
    delay(10);
    in2_val = digitalRead(capteurm); 

  }
  // digitalWrite(IN4, HIGH);
}
void g() // Fonction qui permet au robot de tourner à gauche
{
  int in2_val = digitalRead(capteurm); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, -100);
  while (in2_val == LOW){
    delay(10);
    in2_val = digitalRead(capteurm); 

  }
  // digitalWrite(IN4, HIGH);
}

void av() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
}

void arreter() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void Aleatoire(){

  stat1 = random(HIGH,LOW);
  stat2 = random(HIGH,LOW);

  digitalWrite(IN1, stat1);
  // digitalWrite(6,LOW);
  digitalWrite(IN4, stat2);
  analogWrite(ENA, 50);
  analogWrite(ENB, 50);
  // digitalWrite(11,LOW);

  // analogWrite(A0, 255);
  // analogWrite(A1, 255);
  }

void loop()
{
 int in1_val = digitalRead(capteurg);  // Lit la valeur du capteur gauche (IN1)
int in2_val = digitalRead(capteurm);  
int in3_val = digitalRead(capteurd); 
  if (in1_val == HIGH && in2_val == HIGH && in3_val == HIGH) { // Si tous les capteurs détectent du noir, tourner à gauche ou à droite
    Serial.println("Tous les capteurs détectent du noir");
    Aleatoire();
    delay(50);
  } 
  else if (in1_val == LOW && in2_val == LOW && in3_val == LOW) { // Si tous les capteurs détectent du blanc, arrêter le robot
    Serial.println("Tous les capteurs détectent du blanc");
    av();
    delay(50);
    arreter();
    
  }
  else if (in1_val == HIGH && in2_val == HIGH && in3_val == LOW) { // Si le capteur de gauche détecte du noir, le capteur du milieu détecte du noir, et le capteur de droite détecte du blanc, tourner à gauche
    Serial.println("Tourner à gauche");
    g();
    delay(50);
  } 
  else if (in1_val == LOW && in2_val == HIGH && in3_val == HIGH) { // Si le capteur de gauche détecte du blanc, le capteur du milieu détecte du noir, et le capteur de droite détecte du noir, tourner à droite
    Serial.println("Tourner à droite");
    d();
    delay(50);
  }
  else if (in1_val == LOW && in2_val == HIGH && in3_val == LOW) { // Si le capteur de gauche détecte du blanc, le capteur du milieu détecte du noir, et le capteur de droite détecte du blanc, continuer tout droit
    Serial.println("Continuer tout droit");
    av();
    delay(50);
  }
  else if (in1_val == HIGH && in2_val == LOW && in3_val == LOW) { // Si le capteur de gauche détecte du noir, le capteur du milieu détecte du blanc, et le capteur de droite détecte du noir, tourner à gauche
    Serial.println("Tourner à gauche");
    g();
    delay(50);
  }
  else if (in1_val == LOW && in2_val == LOW && in3_val == HIGH) { // Si le capteur de gauche détecte du noir, le capteur du milieu détecte du blanc, et le capteur de droite détecte du noir, tourner à gauche
    Serial.println("Tourner à droite");
    d();
    delay(50);
  }
  else {
    arreter();
  }


}