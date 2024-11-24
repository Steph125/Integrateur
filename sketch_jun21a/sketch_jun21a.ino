#include <VirtualWire.h>

int emetteur = ; // broche de l'émetteur
int noeud = 1; // numéro du noeud

void setup() {
  vw_set_tx_pin(emetteur); // indiquer la broche de l'émetteur
  vw_setup(2000); // régler la vitesse de transmission à 2000 bits par seconde
}

void loop() {
  char message[10]; // tableau pour stocker le message
  sprintf(message,"Nœud : %d",noeud); // créer le message avec le numéro du noeud
  vw_send((uint8_t *)message, strlen(message)); // envoyer le message sur le module émetteur
  vw_wait_tx(); // attendre que le message soit envoyé
  noeud++; // incrémenter le numéro du noeud
  if (noeud > 12) { // si on a envoyé tous les noeuds
    sprintf(message,"Nœud : FIN"); // créer le message de fin
    vw_send((uint8_t *)message, strlen(message)); // envoyer le message sur le module émetteur
    vw_wait_tx(); // attendre que le message soit envoyé
    noeud = 1; // réinitialiser le numéro du noeud
  }
}
