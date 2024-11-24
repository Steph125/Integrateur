#include <VirtualWire.h>

int recepteur = ; // broche du récepteur

void setup() {
  Serial.begin(9600); // initialiser la communication série
  vw_set_rx_pin(recepteur); // indiquer la broche du récepteur
  vw_setup(2000); // régler la vitesse de transmission à 2000 bits par seconde
  vw_rx_start(); // démarrer la réception
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // tableau pour stocker le message reçu
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // variable pour indiquer la longueur du message reçu
  if (vw_get_message(buf, &buflen)) { // si un message est disponible sur le module récepteur
    Serial.print("Message reçu : "); // afficher "Message reçu : "
    for (int i = 0; i < buflen; i++) { // pour chaque caractère du message reçu
      Serial.print((char)buf[i]); // afficher le caractère sur le moniteur série
    }
    Serial.println(); // passer à la ligne
  }
}
