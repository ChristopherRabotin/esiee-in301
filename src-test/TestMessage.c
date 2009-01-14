#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../libcomm/message.h"
#include "../libbourse/alea.h"

/**
 * Programme de test des fonctions messages
 */
int main(int argc, char **argv) {
	char emetteur[255], type[255], action[255], valeur[255];
	int erreur;
#ifdef DEBUG
	init_log("./TestMessage.log");
#endif
	aleainit();
	// Creation d'un ordre demandant l'achat d'un nombre aléatoire d'actions

	sprintf(valeur, "%d", alea(1, 50));
	printf("L'ordre porte sur %s actions\n", valeur);

	char *msg1 = message("0033125218", "Achat", "0001000012", valeur);
	printf("msg1: %s",msg1);
	msg * msg2 = create_msg("0033125218", "Achat", "0001000012", valeur);
	printf("msg2: %s", msg_to_str(msg2));
	log_msg("Je loggue le msg1",msg2);
	return 0;
}

