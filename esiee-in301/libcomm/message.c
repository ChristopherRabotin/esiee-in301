#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	    )
{
  int nb=sscanf(message, "|%[^|]|%[^|]|%[^|]|%[^|]|\n", 
	 emeteur, type, action, valeur);
  /*if (nb == 4)
    return 0;
  else 
    return 1;*/
  return !(nb==4);
}

/** 
 * Construction du message
 * Retourne le message construit suivant le protocole
 * a partir des arguments
 * Le message est allou� dans la fonction
 */
char* message(char *emeteur, char *type, char *action, 
	      char * valeur)
{
  int longueur = strlen(emeteur) + strlen(type) + strlen(action) 
    + strlen(valeur) + 1 + 5 + 1;
  char *mess = calloc(longueur,sizeof(char));

  if (mess == NULL)
    return NULL;
  
  sprintf(mess, "|%s|%s|%s|%s|\n", emeteur, type, action,
	  valeur);

  return mess;
}
