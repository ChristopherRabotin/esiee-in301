#include "execution.h"

/**
 * Execution recoit les ordres, traite les transactions
 * et envoie les accusés de réception.
 */

int main(void){
	execution_msg(create_msg("0000000004", "Achat", "0001000001", "10"));
	return 0;

}

void execution_msg(msg *mess){
	execution(mess->emetteur,mess->type,mess->action,mess->valeur);
}

void execution(char* emetteur,char* type_transaction,char* id_action_ordre,char* quantite_ordre){
	printf("%s\n%s\n%s\n%s\n\n",emetteur,type_transaction,id_action_ordre,quantite_ordre);
	int i;
	//On va récupérer les informations dont l'action est concernée par l'ordre reçu

	//on ouvre le fichier actions contenant la liste des actions
	FILE* actions = NULL;
	actions = fopen("data/actions", "r");// Ouverture du fichier en lecture(entrée)


	char id_action[100];
	char valeur_action[100];
	char stock_action[100];
	char valeur_totale_transaction[100];
	int stock_restant = 26;


	//TODO: charger toutes les actions en mémoire



	//lecture de l'id_action de l'action

		fseek(actions,0,SEEK_SET);
		//On repère la ligne dont l'action est concernée par l'ordre
		while(fgets(id_action,25,actions)!=0 && strncmp(id_action_ordre,id_action,10)!=0) {
		}

		//on sépare l'id, la valeur et le stock de l'action

		//on ajoute un espace devant la chaine id_action(qui contient la ligne complète)
		//afin de pouvoir tronquer la chaine en 3
		char temp[100];

		strcpy(temp,id_action);
		strcpy(id_action,"");
		strcpy(valeur_action,"");
		strcpy(stock_action,"");
		i=0;
		int curseur=0;
		while (temp[curseur]!='\0')
		{
			if(temp[curseur]==' '){
				i++;
			}
			else{

				if(i==0)
					strncat(id_action,temp+curseur,1);
				if(i==1)
					strncat(valeur_action,temp+curseur,1);
				if(i==2)
					strncat(stock_action,temp+curseur,1);
			}
			curseur++;
		}
		fclose(actions);
		printf("id=%s\nval=%s\nquantité initiale=%s\nstock restant=%d\n",id_action,valeur_action,stock_action,stock_restant);




		//ACHAT
		if(strcmp(type_transaction,"Achat")==0){

			//On compare le nombres d'actions demandées et le stock

			//Si le stock est supérieur et prix d'achat a pu etre calculé:  envoi de l'accusé positif, maj du stock

			//Calcul du prix d'achat
			sprintf(valeur_totale_transaction,"%.3lf",PrixAchat(strtod(valeur_action,NULL),atoi(stock_action),atoi(quantite_ordre)));

			if(stock_restant>=atoi(quantite_ordre) && atoi(valeur_totale_transaction)!=-1){

				//envoi de l'accusé positif
				msg * accuse_positif = create_msg(emetteur, type_transaction, id_action, valeur_totale_transaction);
				//printf("msg2: %s", msg_to_str(ordre));
				//send_msg();
				log_msg("test d'accusé",accuse_positif);

				//maj du stock
				stock_restant += atoi(quantite_ordre);

				sprintf(stock_action,"%d",atoi(stock_action) - atoi(quantite_ordre));



			}
			//Si le stock est inférieur ou prix d'achat retourne erreur: envoi de l'accusé négatif
			else {
				strcpy(valeur_totale_transaction,"0");
			}
		}


		//VENTE
		if(strcmp(type_transaction,"Vente")==0){

		//On vérifie qu'il reste suffisamment de place de stockage

		//Si place suffisante: calcul du prix de vente, envoi de l'accusé positif,maj du stock
		sprintf(valeur_totale_transaction,"%.3lf",PrixVente(strtod(valeur_action,NULL),atoi(stock_action),atoi(quantite_ordre)));

		if(stock_restant>=atoi(quantite_ordre) && atoi(valeur_totale_transaction)!=-1){

			//envoi de l'accusé positif
			msg * accuse_positif = create_msg(emetteur, type_transaction, id_action, valeur_totale_transaction);
			//printf("msg2: %s", msg_to_str(ordre));
			//send_msg();
			log_msg("test d'accusé",accuse_positif);

			//maj du stock
			stock_restant -= atoi(quantite_ordre);

			sprintf(stock_action,"%d",atoi(stock_action) - atoi(quantite_ordre));



		}
		//Si le stock est inférieur ou prix d'achat retourne erreur: envoi de l'accusé négatif
		else {
			strcpy(valeur_totale_transaction,"0");
		}
		//Si place insuffisante: envoi de l'accusé négatif

		}

		printf("\nnouveau stock dispo en bourse:%d",stock_restant);
		printf("\nnouvelle quantité de cette action:%s",stock_action);

		printf("\n");
}
