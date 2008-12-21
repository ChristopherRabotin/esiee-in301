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

msg *create_msg(char *emetteur, char *type, char *action, char *valeur) {
	msg *rtn;
	if (strcmp(type, "Achat") != 0&& strcmp(type, "Vente") != 0&& strcmp(type,
			"AccuseVente") != 0&& strcmp(type, "AccuseAchat") != 0) {
		log_call("Un message de type invalide a été rencontré!", "create_msg",
				"(\"emetteur=%s,type=%s,action=%s,valeur=%s\")", emetteur,
				type, action, valeur);
		return NULL;
	}
#ifdef DEBUG
	log_call("Création d'un message", "create_msg",
			"(\"emetteur=%s,type=%s,action=%s,valeur=%s\")", emetteur, type,
			action, valeur);
#endif
	strcpy(rtn->action, action);
	strcpy(rtn->type, type);
	strcpy(rtn->emetteur, emetteur);
	strcpy(rtn->valeur, valeur);
	return rtn;
}

char *msg_to_str(msg *msg) {
	int longueur = strlen(msg->emetteur) + strlen(msg->type)
			+ strlen(msg->action)+ strlen(msg->valeur) + 1+ 5+ 1;
	char *mess = calloc(longueur, sizeof(char));
	decoupe(mess, msg->emetteur, msg->type, msg->action, msg->action);
#ifdef DEBUG
	log_call("decoupe un msg", "*msg_to_str", "\t renvoie [%s]", mess);
#endif
	return mess;
}
