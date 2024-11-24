int sensor = 12;
int etatSensor ;
unsigned long start_time=0;
unsigned long end_time=0;

int nb_trous=20;
int etat_old=1;
int etat_new=1;
int compt=0;
//float vit=0;
int vit =0;
int temps;
const int IN1= 10;
const int IN4= 7;
const int ENA = 11;
const int ENB = 9;

void av(){
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,HIGH);
  analogWrite(ENA,50);
  analogWrite(ENB, 50);
          
}

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT);
  temps=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  av();
  compt=0;
  start_time=millis();
  end_time=start_time+1000;
  temps=millis();

  while(millis()<end_time){
    etat_new = digitalRead(sensor);
    if (etat_old != etat_new) {
      etat_old=etat_new;
      compt=compt+1;
    }
  }
  vit = float(compt)/(2*nb_trous); 
  //Serial.print(" vitesse: ");
  Serial.println(vit+);  


}
