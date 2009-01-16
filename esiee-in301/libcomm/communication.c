#include "communication.h"

void init_servers(server* servers, const int nb_serv, int port_start,
		const int max_connexions) {
	int iteration;
	for (iteration=0; iteration < nb_serv; iteration++) {
		servers[iteration].id = iteration;
		servers[iteration].isAlive = 1; 
		strcpy(servers[iteration].name, (iteration==0 ? "Acquisition"
				: (iteration==1 ? "Execution" : "Terminal")));
		if ((servers[iteration].sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}
		servers[iteration].local_addr.sin_family = AF_INET; /* host byte order */
		servers[iteration].local_addr.sin_port = htons(port_start++); /* short, network byte order */
		servers[iteration].local_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
		bzero(&(servers[iteration].local_addr.sin_zero), 8); /* zero pour le reste de struct */

		if (bind(servers[iteration].sockfd,( struct sockaddr *)&(servers[iteration].local_addr),sizeof(struct sockaddr))
		== -1) {
			perror("bind");
			exit(1);
		}

		if (listen(servers[iteration].sockfd, max_connexions) == -1) {
			perror("listen");
			exit(1);
		}
		log_srv(servers[iteration],"créé.");
		if(!fork()) { /* fils première génération - permet de revenir de la méthode par contre créé des zombies */
			while(1) { // boucle d' accept() pour recevoir les connexions
				servers[iteration].sin_size = sizeof(struct sockaddr_in);
				int new_fd; // descripteur lié au socket de la connexion courante
				if ((new_fd = accept(servers[iteration].sockfd, (struct sockaddr *)&(servers[iteration].remote_addr),
				&(servers[iteration].sin_size))) == -1) {
					perror("accept");
					continue;
				}
				if(!servers[iteration].isAlive) {
					close(new_fd); //si une connexion arrive alors que le programme est terminé, on sort
					break; return;
				}
				char tmp[128];
				sprintf(tmp, "connexion entrante depuis %s:%d",inet_ntoa(servers[iteration].remote_addr.sin_addr),servers[iteration].remote_addr.sin_port);
				log_srv(servers[iteration],tmp);
				if (!fork()) { /* fils seconde génération - permet d'être multiclient */
					if(!servers[iteration].isAlive) {
						close(new_fd); //si une connexion arrive alors que le programme est terminé, on sort
						return;
					}
					char answer[MAXRECVDATA];
					sprintf(answer,"Serveur %s (#%d). En attente d'un msg (voir libcomm/message.h).\n", servers[iteration].name, servers[iteration].id);
					if (send(new_fd, answer, strlen(answer), 0) == -1)
					perror("send");

					servers[iteration].recvdata = (msg*) malloc (sizeof (msg));
					bzero(servers[iteration].recvdata,sizeof (msg));
					if ((servers[iteration].numbytes=recv(new_fd, servers[iteration].recvdata, MAXRECVDATA, 0)) == -1) {
						perror("recv");
						log_srv(servers[iteration],"erreur lors du recv!");
						exit(1);
					}

					sprintf(tmp,"reçu par %s (#%d) %s:%d",servers[iteration].name, servers[iteration].id,
					inet_ntoa(servers[iteration].remote_addr.sin_addr),servers[iteration].remote_addr.sin_port);
					log_msg(tmp,servers[iteration].recvdata);
					// la connexion avec le client reste ouverte
				}
				close(new_fd); // le parent n'a pas besoin de new_fd

				while(waitpid(-1,NULL,WNOHANG) > 0); // nettoyage des processus fils
			} // fin while du "accept"
		} // fin fils première génération
	} // fin du for
} // fin init_servers

void init_clients(client* clients, const int nb_serv, int port_start) {
	int iteration;
	for (iteration=0; iteration < nb_serv; iteration++) {
		clients[iteration].id = iteration;
		strcpy(clients[iteration].name, (iteration==0 ? "Acquisition"
				: (iteration==1 ? "Execution" : "Terminal")));

		if ((clients[iteration].he=gethostbyname("localhost")) == NULL) {
			herror("gethostbyname");
			log_clt(clients[iteration],"erreur hôte introuvable");
		}

		if ((clients[iteration].sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			log_clt(clients[iteration],"erreur lors de l'init du socket");
		}

		clients[iteration].remote_addr.sin_family = AF_INET; /* host byte order */
		clients[iteration].remote_addr.sin_port = htons(port_start++); /* short, network byte order */
		clients[iteration].remote_addr.sin_addr = *((struct in_addr *)(clients[iteration].he)->h_addr);
		bzero(&(clients[iteration].remote_addr.sin_zero), 8); /* zero pour le reste de struct */

		log_clt(clients[iteration],"créé.");
		
		if (connect(clients[iteration].sockfd,( struct sockaddr *)&(clients[iteration].remote_addr),
		sizeof(struct sockaddr)) == -1) {
			perror("connect");
			log_clt(clients[iteration],"déjà connecté ou impossible de se connecter");
		}
		// on garde la connexion ouverte
	}
}

void send_msg(client clt, msg* damsg) {
	if (damsg == NULL) {
		log_clt(clt,"tentative d'envoi d'un message NULL");
		return;
	}

	if (send(clt.sockfd, damsg, sizeof(msg), 0) == -1){
		perror("send");
		log_clt(clt,"erreur lors de l'envoi du message");
	}
}

void kill_client(const client clt) {
	log_clt(clt,"Fermeture de la connexion");
	close(clt.sockfd);
}

void kill_server(server *srv){
	srv->isAlive=0;
	log_srv(*srv,"Fin du démon");
}

void log_srv(const server srv, char* un_msg) {
	char logged[1024];
	sprintf(logged, "Serveur %s (#%d) %s", srv.name, srv.id, un_msg);
	private_write_log(comm_type, logged);
}

void log_clt(const client clt, char* un_msg) {
	char logged[1024];
	sprintf(logged, "Client %s (#%d) %s", clt.name, clt.id, un_msg);
	private_write_log(comm_type, logged);
}

