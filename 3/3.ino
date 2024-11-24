#include <VirtualWire.h>
#include <string.h>
// Tableau de correspondance
char correspondance[][2] = {
   {'a', 'z'}, {'b', 'y'}, {'c', 'x'}, {'d', 'w'}, {'e', 'v'}, {'f', 'u'},
    {'g', 't'}, {'h', 's'}, {'i', 'r'}, {'j', 'q'}, {'k', 'p'}, {'l', 'o'},
    {'m', 'n'}, {'n', 'm'}, {'o', 'l'}, {'p', 'k'}, {'q', 'j'}, {'r', 'i'},
    {'s', 'h'}, {'t', 'g'}, {'u', 'f'}, {'v', 'e'}, {'w', 'd'}, {'x', 'c'},
    {'y', 'b'}, {'z', 'a'}
  
};

void setup()
{
    Serial.begin(9600);  // Ouvre le port série, définit le débit de données à 9600 bps
    Serial.println("*** Début de la réception ***"); //Permet de lire "*** Début de la réception ***", et permet de rentrer dans la boucle

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); //  DR3100
    vw_setup(2000);  // Réception en bit par seconde (bauds)
    vw_rx_start();       // Démarrer le récepteur en cours d'exécution
}

void loop()
{

uint8_t messageCrypte[sizeof(correspondance)];

  if (vw_get_message(messageCrypte, sizeof(messageCrypte))) {
    char message[sizeof(messageCrypte)];

    // Décryptage du message
    for (int i = 0; i < sizeof(messageCrypte); i++) {
      char caractere = messageCrypte[i];

      // Recherche de la correspondance inverse dans le tableau
      for (int j = 0; j < sizeof(correspondance) / 2; j++) {
        if (correspondance[j][1] == caractere) {
          caractere = correspondance[j][0];
          break;
        }
      }

      message[i] = caractere;
    }

    //Serial.println("ACAR:"+message);  // Affiche le message décrypté
    String text = "ACAR: " + String(message);
  Serial.println(text.c_str());
  }
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
      // On attend de recevoir un message
  //vw_wait_rx();
  
    //if (vw_get_message(buf, &buflen)) // On copie le message, qu'il soit corrompu ou non 
    //{
  //int i;

       //digitalWrite(11, true); //  montre que le bon message a été reçu
  // Message with a good checksum received, dump it.
  
  //Serial.print("ACAR: "); // Permet d'afficher "ACAR" devant le message reçu
 // for (i = 0; i < buflen; i++)
  //{
      // Serial.print(buf[i], HEX);
     // Serial.print(char(buf[i]));
  //}
  //Serial.println("");
        //digitalWrite(11, false);
        
 // }
}
