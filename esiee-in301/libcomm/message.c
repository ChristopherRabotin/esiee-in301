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
	msg *rtn =( msg*) malloc (sizeof (msg));
	if (strcmp(type, "Achat") != 0 && strcmp(type, "Vente") != 0&& strcmp(type,
			"AccuseVente") != 0 && strcmp(type, "AccuseAchat") != 0) {
		log_call("Un message de type invalide a été rencontré!", "create_msg",
		"(\"emetteur=%s,type=%s,action=%s,valeur=%s\")", emetteur,
		type, action, valeur);
		return NULL;
	}
#ifdef DEBUG
	log_call("Creation d'un message", "create_msg",
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
#ifdef DEBUG
	log_msg("traduction en char*", msg);
#endif
	return message(msg->emetteur, msg->type, msg->action, msg->valeur);
}

void log_msg(const char *un_msg, msg *damsg) {
	char loggedmsg[1024];
	sprintf(loggedmsg,"%s par %s: action=%s valeur=%s %s",
			damsg->type, damsg->emetteur, damsg->action, damsg->valeur, un_msg);
	private_write_log(msg_type, loggedmsg);
}
