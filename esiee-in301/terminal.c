#include "terminal.h"


/**
 * Terminal prend deux descripteurs de fichiers en paramètre
 * vers lesquels il redirige son entrée et sa sortie standart.
 */
int main(void){
	terminal();
	return 0;
}

int terminal(){

	char buf;
	char identifiant[1];
	   int fd; // Notre file descriptor
	   if (-1 == (fd = open("./commercants", O_RDONLY))) // Lecture du fichier
	   {
	      perror("open() ");
	      exit(EXIT_FAILURE);
	   }
	   else {
		   int i;
		   for (i = 0 ; i < 2 ; i++)
		   {
			read(fd, &buf,sizeof(char));
			printf("%c\n",buf);
			identifiant[i]=buf;
		   }
			printf("\n%s\n",identifiant);
			close(fd);
	   }
	   return 0;
}
