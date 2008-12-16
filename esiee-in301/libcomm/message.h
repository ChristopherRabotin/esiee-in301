#ifndef _MESSAGEH_
#define _MESSAGEH_

/**
 * Decoupe du message 
 * Retourne 1 si il n'y a pas eu de probl�me
 * Retourne 0 si il y a eu un probl�me
 * ATTENTION:
 *   Les variables emeteur, destinataire, commande, identifiant
 *   et sms doivent �tre allou�es avant l'appel � decoupe
 */

int decoupe(char *message,      /* Source a d�couper */
	    char *emeteur,      /* Emeteur du message */
	    char *type,         /* Type du message */
	    char *action,       /* Idebtificateur de l'action */
	    char *valeur        /* Valeur associ�e au message */
	    );

/** 
 * Construction du message
 * Retourne le message construit suivant le protocole
 * a partir des arguments
 * Le message est allou� dans la fonction
 */
char* message(char *emeteur, char *type, char *action, 
	      char *valeur);

#endif // _MESSAGEH_
