#include "casual_includes.h"
#include "../libcomm/communication.h"

int main(void){
	printf("Lancement du programme\n");
	init_log("bourse.log");
	server servers[3];
	init_one_server(&servers[0], 1200, 2, "execution",exec);
	init_one_server(&servers[1], 1201, 2, "acquisition",ack);
	init_one_server(&servers[2], 1202, 2, "interboursier",interb);
	sleep(100);
	printf("fin.\n");
	return 0;
}
