#include "../libcomm/communication.h"

/**
 * Programme de test des serveurs
 */
int main(int argc, char **argv) {
	init_log("TestServers.log");
	server servers[3]; client clients[3];
	init_servers(servers, 3, 1200, 2); init_clients(clients, 3, 1200);
	// fin init
	char valeur[5];
	sprintf(valeur, "%d", alea(1, 50));
	msg * msg1 = create_msg("1", "Achat", "0001000012", valeur);
	msg * msg2 = create_msg("2", "Vente", "0001000012", valeur);
	msg * msg3 = create_msg("3", "Vente", "0001000012", valeur);
	msg * msg4 = create_msg("4", "Vente", "0001000012", valeur);
	send_msg(clients[ack],msg1);
	send_msg(clients[ack],msg2);
	send_msg(clients[exec],msg3);
	send_msg(clients[term],msg4);
	send_msg(clients[term],msg1);

	printf("fin.\n");
}
