#include "execution.h"

/**
 * Execution recoit les ordres, traite les transactions
 * et envoie les accusés de réception.
 */

int main(void){
	execution("0002000002");


	return 0;

}


void execution(char* id_action_ordre){
	int i;
	//On va récupérer les informations dont l'action est concernée par l'ordre reçu

	//on ouvre le fichier actions contenant la liste des actions
	FILE* actions = NULL;
	actions = fopen("./actions", "r");// Ouverture du fichier en lecture(entrée)


	char id_action[100];
	char valeur_action[100];
	char nombre_action[100];


	//lecture de l'id_action de l'action
	//TODO: virer nombre_actions mais génère un segfault
		int nombre_actions;

		fseek(actions,0,SEEK_SET);
		//On repère la ligne dont l'action est concernée par l'ordre
		while(fgets(id_action,25,actions)!=0 && strncmp(id_action_ordre,id_action,10)!=0) {
		}

		printf("id_action: %s\n",id_action);
		//on sépare l'id, la valeur et le stock de l'action

		//on ajoute un espace devant la chaine id_action(qui contient la ligne complète)
		//afin de pouvoir tronquer la chaine en 3
		char* temp;



//Provoque un putain de sexfault!
		strcpy(temp," ");
		strcat(temp,id_action);
		strcpy(id_action,temp);
		temp = strtok (id_action," ");
		strcpy(id_action,temp);





		i=0;
		while (temp != NULL)
		{
		    temp = strtok (NULL, " ");
		    if(temp!=NULL) {
				  switch(i){
					  case(0):strcpy(valeur_action,temp);break;
					  case(1):strcpy(nombre_action,temp);break;
				  }
				  i++;
		    }
		}
		fclose(actions);
		printf("id=%s\nval=%s\nstock=%s\n",id_action,valeur_action,nombre_action);


		//TODO: il faut surement définir le stock ailleurs!
		char valeur_total_transaction[100];
		int stock_restant = 21;

		//ACHAT
		//On compare le nombres d'actions demandées et le stock



		//Si le stock est supérieur: calcul du prix d'achat, envoi de l'accusé positif, maj du stock
		if(stock_restant>=nombre_actions){
			//calcul du prix d'achat

			//envoi de l'accusé positif
			msg * accuse_positif = create_msg("emetteur", "Achat", id_action, valeur_total_transaction);
			//printf("msg2: %s", msg_to_str(ordre));
			//send_msg();
			log_msg("test d'accusé",accuse_positif);


			//maj du stock
			stock_restant -= nombre_actions;

		}
		//Si le stock est inférieur: envoi de l'accusé négatif
		else {
			strcpy(valeur_total_transaction,"0");
		}

		//VENTE
		//On vérifie qu'il reste suffisamment de place de stockage

		//Si place suffisante: calcul du prix de vente, envoi de l'accusé positif,maj du stock

		//Si place insuffisante: envoi de l'accusé négatif

		char stock[100];
		sprintf(stock,"%d",stock_restant);
		printf("nouveau stock:%s",stock);


}
