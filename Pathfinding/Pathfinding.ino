#include "Grove_I2C_Motor_Driver.h"

// ****************************Constantes***************************** //


//Différents ports utilisés
#define Capteur_Gauche 4
#define Capteur_Milieu 3
#define Capteur_Droite 2
#define I2C_ADRESSE 0x0f

const int IN3 = 6; // L293D - premier moteur pin 1 (Gauche)
const int IN4 = 7; // L293D - premier moteur pin 2 (Gauche)
int ENA = 11;
const int IN2 = 12; // L293D - second moteur pin 1 (Droite)
const int IN1 = 10; // L293D - second moteur pin 2 (Droite)
int ENB = 9; // L293D - les 2 pins enable
#define DESTINATION 14
// ********************************************************************** //


void setup() {

  // Initialisations
  // Serial.begin(9600);
  pinMode(Capteur_Gauche, INPUT);
  pinMode(Capteur_Milieu, INPUT);
  pinMode(Capteur_Droite, INPUT);
  Motor.begin(I2C_ADRESSE);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.begin(9600);

  //Determination de l'itineraire
  initItineraire(DESTINATION);
}


// *********************Fonction determination d'itineraire********************//
//                Initialise le tableau 'itineraire' en fonction                 //
//                           de la valeur de l'arrivée                           //
// ******************************************************************************//


//Le tableau qui va stocker l'itineraire à suivre
int itineraire[15];

void initItineraire(int arrivee) {

  /* Correspondances des valeurs dans l'itineraire :
  * 0 => Stop
  * 1 => Gauche
  * 2 => Haut
  * 3 => Droite
  
  */
  switch (arrivee) {
    case (1):
      itineraire[0] = 0;
      break;
    
    case (2):
      itineraire[0] = 2;
      itineraire[1] = 0;
      break;

    case (3):
      itineraire[0] = 2;
      itineraire[1] = 0;
      itineraire[2] = 2;
      itineraire[3] = 0;
      break;

    case (4):
      itineraire[0] = 2;
      itineraire[1] = 0;
      itineraire[2] = 2;
      itineraire[3] = 1;
      itineraire[4] = 2;
      itineraire[5] = 0;
      break;

    case (5):
      itineraire[0] = 2;
      itineraire[1] = 0;
      itineraire[2] = 2;
      itineraire[3] = 1;
      itineraire[4] = 2;
      itineraire[5] = 0;  
      itineraire[6] = 2; 
      itineraire[7] = 0;   
      break;

    case (6):
      itineraire[0] = 2;
      itineraire[1] = 0;
      itineraire[2] = 2;
      itineraire[3] = 1;
      itineraire[4] = 2;
      itineraire[5] = 0;  
      itineraire[6] = 2; 
      itineraire[7] = 1;
      itineraire[8] = 2;
      itineraire[9] = 0;      
      break;

    case (7):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0;
      itineraire[3] = 2;
      itineraire[4] = 3;
      itineraire[5] = 2;
      itineraire[6] = 0;
      itineraire[7] = 2;
      itineraire[8] = 1;
      itineraire[9] = 2; 
      itineraire[10] = 0;        
      break;

    case (8):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0;
      itineraire[3] = 2;
      itineraire[4] = 3; 
      itineraire[5] = 2;
      itineraire[6] = 1;
      itineraire[7] = 2; 
      itineraire[8] = 0;     
      break;

    case (9):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0;
      itineraire[3] = 2;
      itineraire[4] = 0;
      itineraire[5] = 2;
      itineraire[6] = 0;
      break;

    case (10):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0;
      itineraire[3] = 2;
      itineraire[4] = 0;
      break;

    case (11):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0;
      break;

    case (12):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 3;
      itineraire[3] = 2;
      itineraire[4] = 0;
      break;

    case (13):
      itineraire[0] = 2;
      itineraire[1] = 1;
      itineraire[2] = 2;
      itineraire[3] = 3;
      itineraire[4] = 2; 
      itineraire[5] = 0;     
      break;

    case (14):
      itineraire[0] = 2;
      itineraire[1] = 1;
      itineraire[2] = 2; 
      itineraire[3] = 0;     
      break;

    case (15):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0; 
      itineraire[3] = 2; 
      itineraire[4] = 3;
      itineraire[5] = 2;  
      itineraire[6] = 0; 
      break;

    case (16):
      itineraire[0] = 1;
      itineraire[1] = 2;
      itineraire[2] = 0;
      itineraire[0] = 2;
      itineraire[0] = 3;
      itineraire[0] = 2; 
      itineraire[0] = 0;  
      itineraire[0] = 2;
      itineraire[0] = 0;   
      break;
  }
}



// ****************************Fonction principale***************************** //
// Verifie l'état des différents capteurs et déplace le véhicule en fonction //

//On initialise la première étape à 0, car c'est un tableau
int etape = 0;

void loop() {

  //Aucun capteur -> tout droit
  if (digitalRead(Capteur_Droite) == LOW && digitalRead(Capteur_Milieu) == LOW && digitalRead(Capteur_Gauche) == LOW) {
    continuer();
  }
  //Recalibrage vers la droite
  else if (digitalRead(Capteur_Droite) == HIGH) {
    decalerDroite();
  }

  //Recalibrage vers la gauche
  else if (digitalRead(Capteur_Gauche) == HIGH) {
    decalerGauche();
  }



  //Application de l'itineraire :
  //Capteur gauche ou droite ->réaliser l'etape actuelle et passer à l'etape suivante de l'itinéraire
  if ((digitalRead(Capteur_Gauche) == HIGH || digitalRead(Capteur_Droite) == HIGH) && etape < 15) {
    //Etape = 2 , donc continuer tout droit
    if (itineraire[etape] == 2) {

      //Continuer tout droit tant que le capteur qui a detecté l'intersection ne s'est pas eteint
      while (digitalRead(Capteur_Gauche) == HIGH || digitalRead(Capteur_Droite) == HIGH) {
        continuer();

        //Recalibrage vers la gauche
        if (digitalRead(Capteur_Droite) == HIGH) {
          decalerDroite();
        }

        //Recalibrage vers la droite
        else if (digitalRead(Capteur_Gauche) == HIGH) {
          decalerGauche();
        }
      }

    }
    //Etape = 3 , donc tourner à droite
    else if (itineraire[etape] == 3) {
      tournerDroite();

    }
    //Etape = 1 , donc tourner à gauche
    else if (itineraire[etape] == 1) {
      tournerGauche();
    }

    //Etape = 0 , donc arrêt
    else if (itineraire[etape] == 0) {
      arreter();
    }
    etape += 1;
  }
}


// ****************************Fonctions de déplacements***************************** //
//              - continuer()         - tournerGauche()         - tournerDroite()      //
//              - arreter()           - decalerGauche()         - decalerDroite()      //
// ************************************************************************************ //

void continuer() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
}


void tournerDroite() {
  int in2_val = digitalRead(Capteur_Milieu); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, HIGH);
  analogWrite(ENA, -100);
  analogWrite(ENB, 100);
  while (in2_val == LOW){
    delay(10);
    in2_val = digitalRead(Capteur_Milieu); 

  }
}


void tournerGauche() {
  int in2_val = digitalRead(Capteur_Milieu); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, -100);
  while (in2_val == LOW){
    delay(10);
    in2_val = digitalRead(Capteur_Milieu); 

  }
}



void decalerDroite() {
  int in2_val = digitalRead(Capteur_Milieu); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, HIGH);
  analogWrite(ENA, -100);
  analogWrite(ENB, 100);
  while (in2_val == LOW){
    delay(10);
    in2_val = digitalRead(Capteur_Milieu); 

  }
}



void decalerGauche() {
  int in2_val = digitalRead(Capteur_Milieu); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, -100);
  while (in2_val == LOW){
    delay(10);
    in2_val = digitalRead(Capteur_Milieu); 

  }
}


void arreter() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}