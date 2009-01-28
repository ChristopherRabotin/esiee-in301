#include "terminal.h"

/**
 * Terminal permet d'envoyer un ordre conçu aléatoirement à partir des annuaires (commerçants,actions)
 * et de valeurs aléatoires.
 * Il reçoit et affiche à l'écran un accusé de réception provenant du serveur d'acquisition
 *
 * Il prend 2 descripteurs de fichiers en paramètres vers lesquels il redirige son entrée et sa sortie standarts.
 */

void terminal(FILE* accuse){
	//on ouvre les fichiers commercants et actions contenant les listes de commercants
	//et d'actions dispos
	FILE* commercants = NULL;
	FILE* actions = NULL;
	commercants = fopen("./commercants", "r");// Ouverture du fichier en lecture(entrée)
	actions = fopen("./actions", "r");// Ouverture du fichier en lecture(entrée)


	char id_commercant[100];
	char id_action[100];
	char type_transaction[100];
	char valeur[100];
	//lecture de l'id_commercant du commercant
	if (commercants!=NULL && actions!=NULL) {
		int nombre_commercants=0;
		//char id_commercant[11];
		fseek(commercants,0,SEEK_SET);
		//récupération du nombre de lignes = nombre de commercants dans le fichier
		while(fgets(id_commercant,25,commercants)!=0) {
			printf("%s",id_commercant);
			nombre_commercants++;
		}

		//on tire un commercant aléatoirement dans le fichier de commercants
		fseek(commercants,0,SEEK_SET);
		aleainit();
		int i;
		int commercant_aleatoire = alea(1,nombre_commercants);
		for(i=0;i<commercant_aleatoire;i++){
			fgets(id_commercant,25,commercants);
		}
		//on récupère uniquement l'identifiant du commercant
		  char* pch;
		  pch = strtok (id_commercant," ");
		  while (pch != NULL)
		  {
		    pch = strtok (NULL, " ");
		    if(pch!=NULL)
				  strcpy(id_commercant,pch);
		  }
		//on remplace le \n qui est a la fin de la chaine
		id_commercant[10] = ' ';

		fclose(commercants);

	//lecture de l'id_action de l'action
		int nombre_actions=0;

		fseek(actions,0,SEEK_SET);
		//récupération du nombre de lignes = nombre d'actions dans le fichier
		while(fgets(id_action,12,actions)!=0) {
			nombre_actions++;
		}
		//on tire une action aléatoirement dans le fichier des actions
		fseek(actions,0,SEEK_SET);
		aleainit();
		int action_aleatoire = alea(1,nombre_actions);
		for(i=0;i<action_aleatoire;i++){
			fgets(id_action,12,actions);
		}
		//on remplace le \n qui est a la fin de la chaine
		id_action[10] = ' ';

		fclose(actions);

	//type_transaction défini aléatoirement
		aleainit();
		int type_aleatoire = alea(1,2);
		for(i=0;i<type_aleatoire;i++){
			switch(i){
				case(0):strcpy(type_transaction,"Achat");break;
				case(1):strcpy(type_transaction,"Vente");break;
			}
		}


		//valeur de la transaction définie aléatoirement
			aleainit();
			sprintf(valeur,"%d",alea(1,50));

		printf("commercant tiré aléatoirement: %s ordre: %s action: %s\n",id_commercant,type_transaction,id_action);


		msg * ordre = create_msg(id_commercant, type_transaction, id_action, valeur);
		//printf("msg2: %s", msg_to_str(ordre));
		//send_msg();
		log_msg("test d'ordre",ordre);
	}


	//lecture de l'accusé de réception
	if (accuse!=NULL) {
		char accuse_de_reception[20];
		fseek(accuse,0,SEEK_SET);
		fgets(accuse_de_reception,12,accuse);

		//on remplace le \n qui est a la fin de la chaine
		accuse_de_reception[10] = ' ';
		printf("Lecture de l'accusé: %s",accuse_de_reception);

		fclose(accuse);
	}

}




















//int main(void){
//	int fd0 = open("./commercants", O_RDONLY); // Ouverture du fichier en lecture(entrée)
//
//	int fd1 = open("./accuse_de_reception", O_RDWR); // Ouverture du fichier en écriture(sortie)
//
//	terminal(fd0,fd1);
//	return 0;
//}
//
//int terminal(int in, int out){

//	char buf;
//	char id_commercant[10];
//	   if (-1 == in)
//		   {
//		      perror("open(entrée) ");
//		      exit(EXIT_FAILURE);
//		   }
//	   else {
//		   int i;
//		   for (i = 0 ; i < 10 ; i++)
//		   {
//			read(in, &buf,sizeof(char));
//
//			printf("%d%c\n",i,buf);
//
//			id_commercant[i]=buf;
//		   }
//			printf("\n%s\n",id_commercant);
//			close(in);
//	   }
//	   if (-1 == out)
//		   {
//		      perror("open(sortie) ");
//		      exit(EXIT_FAILURE);
//		   }
//	   else {
//		   int i;
//		   char accuseString[] = "accuse de reception positif";
//		   char c = 'a';
//		   for (i = 0 ; i < sizeof(accuseString)/sizeof(char) ; i++)
//		   {
//			   // TODO : résoudre le pb pour écrire dans le fichier la chaine de caractères
//			   buf = accuseString[i];
//			   printf("%c",buf);
//			   write(out, &buf, sizeof(char));
//		   }
//		   printf("\n");
//			close(out);
//	   }
//	   return 0;
//}
