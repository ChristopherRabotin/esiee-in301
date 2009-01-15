#include "../libcomm/communication.h"

/**
 * Programme de test des serveurs
 */
int main(int argc, char **argv) {
	init_log("TestServers.log");
	server servers[3];
	client clients[3];
	char valeur[5];
	sprintf(valeur, "%d", alea(1, 50));
	msg * msg1 = create_msg("0033125218", "Achat", "0001000012", valeur);
	init_servers(servers, 3, 1200, 2);
	init_clients(clients, 3, 1200);
	send_msg(clients[toAck],msg1);
	msg * msg2 = create_msg("2", "Vente", "0001000012", valeur);
	send_msg(clients[toAck],msg2);
	send_msg(clients[toAck],msg2);
	send_msg(clients[toTerm],msg2);
	kill_client(clients[toAck]); kill_client(clients[toExec]); kill_client(clients[toTerm]);
	bzero(servers, sizeof(server)*3);
	printf("fin.\n");
}