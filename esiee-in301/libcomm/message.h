#ifndef MESSAGE_H_
#define MESSAGE_H_

/**
 * decoupe: Decoupe du message
 * @param *emeteur émeteur du message
 * @param *type type du message
 * @param *action identificateur de l'action
 * @param *valeur valeur associée au message 
 * @return 0 si erreur, 1 sinon
 * <b>ATTENTION:</b>
 * Les paramètres étant des pointeurs, les variables associées DOIVENT
 * être allouées avant l'appel de la fonction
 */

int decoupe(char *message, char *emeteur, char *type, char *action,
		char *valeur);

/** 
 * message: Construction du message. Le message est alloué dans la fonction.
 * @param *emeteur émeteur du message
 * @param *type type du message
 * @param *action identificateur de l'action
 * @param *valeur valeur associée au message
 * @return le message construit suivant le protocole à partir des arguments
 */
char* message(char *emeteur, char *type, char *action, char *valeur);

#endif // MESSAGE_H_
