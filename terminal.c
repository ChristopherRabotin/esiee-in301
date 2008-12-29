#include "terminal.h"


/**
 * Terminal prend deux descripteurs de fichiers en paramètre
 * vers lesquels il redirige son entrée et sa sortie standards.
 */
int main(void){
	int fd0 = open("./commercants", O_RDONLY); // Ouverture du fichier en lecture(entrée)

	int fd1 = open("./accuse_de_reception", O_WRONLY); // Ouverture du fichier en écriture(sortie)

	terminal(fd0,fd1);
	return 0;
}

int terminal(int in, int out){

	char buf;
	char identifiant[10];
	   if (-1 == in)
		   {
		      perror("open(entrée) ");
		      exit(EXIT_FAILURE);
		   }
	   else {
		   int i;
		   for (i = 0 ; i < 10 ; i++)
		   {
			read(in, &buf,sizeof(char));
			printf("%d%c\n",i,buf);
			identifiant[i]=buf;
		   }
			printf("\n%s\n",identifiant);
			close(in);
	   }
	   if (-1 == out)
		   {
		      perror("open(sortie) ");
		      exit(EXIT_FAILURE);
		   }
	   else {
		   int i;
		   char accuseString[] = "accusé de réception positif";
		   for (i = 0 ; i < sizeof(accuseString)/sizeof(char) ; i++)
		   {
			   // TODO : résoudre le pb pour écrire dans le fichier la chaine de caractères
			   buf = accuseString[i];
			   printf("%c",buf);
			   write(out, &buf, sizeof(char));
		   }
			printf("\n%s\n",identifiant);
			close(out);
	   }
	   return 0;
}
