#include "../src/terminal.h"

int main(void){

	//on charge les entrées/sorties
	FILE* accuse = NULL;
	FILE* ordre = NULL;

	accuse = fopen("../data/accuse_de_reception", "r");// Ouverture du fichier en écriture(sortie)
	ordre = fopen("../data/ordre", "w");// Ouverture du fichier en écriture(sortie)

	terminal(accuse);

	return 0;

}
