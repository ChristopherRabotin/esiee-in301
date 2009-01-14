#include "terminal.h"


/**
 * Terminal prend deux descripteurs de fichiers en paramètre
 * vers lesquels il redirige son entrée et sa sortie standards.
 */

int main(void){
	FILE* commercants = NULL;
	FILE* actions = NULL;
	FILE* accuse = NULL;
	FILE* ordre = NULL;

	commercants = fopen("./commercants", "r");// Ouverture du fichier en lecture(entrée)
	actions = fopen("./actions", "r");// Ouverture du fichier en lecture(entrée)

	accuse = fopen("./accuse_de_reception", "w");// Ouverture du fichier en écriture(sortie)
	ordre = fopen("./ordre", "w");// Ouverture du fichier en écriture(sortie)
	terminal(commercants,actions);

	envoie_ordre(ordre);
	return 0;

}

void terminal(FILE* commercants, FILE* actions){
	//printf("commercants: %d\n actions: %d",commercants,actions);
	char id_commercant[100];
	char id_action[100];
	//lecture de l'id_commercant du commercant
	if (commercants!=NULL && actions!=NULL) {
		int nombre_commercants=0;
		//char id_commercant[11];
		fseek(commercants,0,SEEK_SET);
		//récupération du nombre de lignes = nombre de commercants dans le fichier
		while(fgets(id_commercant,12,commercants)!=0) {
			nombre_commercants++;
		}
		//on tire un commercant aléatoirement dans le fichier de commercants
		fseek(commercants,0,SEEK_SET);
		aleainit();
		int i;
		int commercant_aleatoire = alea(1,nombre_commercants);
		for(i=0;i<commercant_aleatoire;i++){
			fgets(id_commercant,12,commercants);
		}
		//on remplace le \n qui est a la fin de la chaine
		id_commercant[10] = ' ';

		printf("id_commercant=%s\n",id_commercant);
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
		printf("id_action=%s\n",id_action);
		//on remplace le \n qui est a la fin de la chaine
		id_action[10] = ' ';



		//TODO: affichage de l'identifiant;
		printf("commercant tiré aléatoirement: %s ordre: %s action: %s\n",id_commercant,"vente",id_action);
		fclose(commercants);
		fclose(actions);

		log_smth(create_msg(id_commercant,"achat", id_action, id_action));
	}

//	//écriture de l'accusé de réception
//	if (out!=NULL){
//	char accuseString[] = "accuse de reception positif";
//	fprintf(out,accuseString);
//	fclose(out);
//	}

	envoie_ordre();

}

void envoie_ordre(FILE* out){
//	//log_msg();
//	aleainit();
//	char id_commercant[10]="";
//	int i =0;
//	for (i=0; i<10;i++)
//		id_commercant[i] = alea(0,9);
//	printf("%s",id_commercant);
//
//	//écriture de l'accusé de réception
//	if (out!=NULL){
//	fprintf(out,accuseString);
//	fclose(out);
//	}
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
