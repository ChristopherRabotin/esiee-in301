#include "../src/execution.h"

int main(int argc, char *argv[]){
	char em[100],ty[100],ac[100],qu[100];
	while(1){
	if(argc!=1){
	printf("Veuillez entrer un ordre:\n");

	scanf("%s%s%s%s",em,ty,ac,qu);
	execution(em,ty,ac,qu);
	}
	//execution_msg(create_msg("0000000004", "Vente", "0001000001", "10"));
	}
	return 0;

}
