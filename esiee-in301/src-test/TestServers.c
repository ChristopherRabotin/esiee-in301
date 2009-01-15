#include "../libcomm/communication.h"

/**
 * Programme de test des serveurs
 */
int main(int argc, char **argv) {
	server servers[3];
	init_servers(servers, 3, 1200, 2);
	printf("fin.\n");
}
