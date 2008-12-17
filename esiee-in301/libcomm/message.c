#include "message.h"

int decoupe(char *message, char *emeteur, char *type, char *action,
		char *valeur) {
	int nb=sscanf(message, "|%[^|]|%[^|]|%[^|]|%[^|]|\n", emeteur, type,
			action, valeur);
	return !(nb==4);
	/* ancien code:
	 if (nb == 4)
	 return 0;
	 else 
	 return 1;*/
}

char* message(char *emeteur, char *type, char *action, char * valeur) {
	int longueur = strlen(emeteur) + strlen(type) + strlen(action)
			+ strlen(valeur) + 1+ 5+ 1;
	char *mess = calloc(longueur, sizeof(char));

	if (mess == NULL)
		return NULL;

	sprintf(mess, "|%s|%s|%s|%s|\n", emeteur, type, action, valeur);

	return mess;
}
