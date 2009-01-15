#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../casual_includes.h"
#include "./logger.h"
/**
 * msg correspond aux données qui transitent sur le réseau interboursier. Ces données sont nommés
 * <i>messages</i> dans le sujet du projet.
 */
typedef struct msg_struct {
	char emetteur[32]; //  l’identiﬁant de l’émetteur de l’ordre ;
	char type[11]; // – T...T est le type du message: ’Achat’ ’Vente’ ’AccuseVente’ ’AccuseAchat’
	char action[20]; // t l’identiﬁcateur de l’action sur laquelle porte l’ordre ou l’accusé de réception
	char valeur[5];
} msg;

/** 
 * create_msg: Construction du message. Le message est alloué dans la fonction.
 * @param *emetteur émeteur du message
 * @param *type type du message
 * @param *action identificateur de l'action
 * @param *valeur valeur associée au message
 * @return le message de type msg
 */
msg* create_msg(const char *emetteur, const char *type, const char *action, const char *valeur);

/**
 * msg_to_str: transforme le message msg en une chaine de caractères suivant le protocole utilisé
 * Fait appel à message()
 */
char* msg_to_str(msg *msg);

/**
 * decoupe: Decoupe du message
 * @param *message le texte du message
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

/**
 * Permet de logguer les ordres de transaction. Placé dans message.h puisque
 * utilisé uniquement pour les messages.
 * @param un_msg message d'explication lié à l'ordre de transaction 
 * @param damsg l'ordre à être loggué.
 */
void log_msg(const char *un_msg, msg *damsg);

#endif // MESSAGE_H_
