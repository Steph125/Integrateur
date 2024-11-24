#include "Grove_I2C_Motor_Driver"

int captdroit = 2;
int captcent = 3;
int captgauche = 4;

void setup() {
  Serial.begin(9600);
// intitialisation de l'écoute des capteurs
  pinMode (captgauche, INPUT);
  pinMode (captcent, INPUT);
  pinMode (captdroit, INPUT);
}

void loop()
{
  delay(1000);
//digitalRead(captgauche);    // lecture de la valeur de l'entrée suiveur de ligne

Serial.print(digitalRead(captgauche));
Serial.print(" ");
Serial.print(digitalRead(captcent));
Serial.print(" ");
Serial.println(digitalRead(captdroit));
}