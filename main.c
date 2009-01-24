#include "casual_includes.h"
#include "../libcomm/communication.h"

int main(void){
	printf("Lancement du programme\n");
	init_log("bourse.log");
	server *execution; server *acquisition;
	init_one_server(execution, 1200, 2, "execution");
	init_one_server(acquisition, 1200, 2, "acquisition");
	sleep(100);
	printf("fin.\n")
	return 0;
}
