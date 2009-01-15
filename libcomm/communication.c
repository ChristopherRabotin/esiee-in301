#include "communication.h"

void init_servers(server* servers, const int nb_serv, int port_start,
		const int max_connexions) {
#ifdef DEBUG
	init_log("libcomm.log");
#endif

	int iteration;
	for (iteration=0; iteration < nb_serv; iteration++) {
		servers[iteration].id = iteration;
		strcpy(servers[iteration].name, (iteration==0 ? "Acquisition"
				: (iteration==1 ? "Execution" : "Terminal")));
		if ((servers[iteration].sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}
#ifdef DEBUG
		log_smth("création du serveur %s (#%d)", servers[iteration].name,
				servers[iteration].id);
#endif
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
		if(!fork()) { /* fils première génération - permet de revenir de la méthode par contre créé des zombies */
			while(1) { /* main accept() loop */
				servers[iteration].sin_size = sizeof(struct sockaddr_in);
				int new_fd; // descripteur lié au socket de la connexion courante
				if ((new_fd = accept(servers[iteration].sockfd, (struct sockaddr *)&(servers[iteration].remote_addr),
				&(servers[iteration].sin_size))) == -1) {
					perror("accept");
					continue;
				}
				log_smth("%s (#%d) connexion de %s", servers[iteration].name, servers[iteration].id,
				inet_ntoa(servers[iteration].remote_addr.sin_addr));
				if (!fork()) { /* fils seconde génération - permet d'être multiclient */
					char answer[MAXRECVDATA];
					sprintf(answer,"Bienvenue sur le serveur %s (#%d).\nEnvoyer votre message de type msg.\n", servers[iteration].name, servers[iteration].id);
					if (send(new_fd, answer, strlen(answer), 0) == -1)
					perror("send");

					//do{
					//bzero(,MAXRECVDATA);
					servers[iteration].recvdata =( msg*) malloc (sizeof (msg));
					if ((servers[iteration].numbytes=recv(new_fd, servers[iteration].recvdata, MAXRECVDATA, 0)) == -1) {
						perror("recv");
						exit(1);
					}
					//servers[iteration].recvdata[servers[iteration].numbytes] = '\0'; // on ajoute un NULL pour terminer la chaine
					/*log_smth("%s (#%d) %s envoie: \"%s\"", servers[iteration].name, servers[iteration].id,
					 inet_ntoa(servers[iteration].remote_addr.sin_addr),servers[iteration].recvdata);*/
					char tmp[128];
					sprintf(tmp,"réception %s (#%d) %s",servers[iteration].name, servers[iteration].id,
					inet_ntoa(servers[iteration].remote_addr.sin_addr));
					log_msg(tmp,servers[iteration].recvdata);
					printf("%s",msg_to_str(servers[iteration].recvdata));

					//} while (strcmp(servers[iteration].recvdata,"exit")!=0 && servers[iteration].recvdata[servers[iteration].numbytes-1] != '\4');
					/* tant que l'on ne reçoit pas "exit" ou le caractère de fin de transmission (EOT), la connexion reste ouverte. */
					close(new_fd);
					exit(0);

				}
				close(new_fd); /* Le parent n'a pas besoin de new_fd */

				while(waitpid(-1,NULL,WNOHANG) > 0); /* Nettoyage des processus fils */
			}
		}
	}
}

void init_clients(client* clients, const int nb_serv, int port_start) {
	if ((clients[0].he=gethostbyname("localhost")) == NULL) {
		herror("gethostbyname");
		exit(1);
	}

	if ((clients[0].sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
//TODO: vérifier le nombre de clients à créer vu qu'il y en a un par serveur.
// pour le moment, celui-ci se connecte sur le serveur d'Acquisition puisqu'il contacte le port port_start.

	clients[0].remote_addr.sin_family = AF_INET; /* host byte order */
	clients[0].remote_addr.sin_port = htons(port_start); /* short, network byte order */
	clients[0].remote_addr.sin_addr = *((struct in_addr *)(clients[0].he)->h_addr);
	bzero(&(clients[0].remote_addr.sin_zero), 8); /* zero pour le reste de struct */

	if (connect(clients[0].sockfd, (struct sockaddr *)&(clients[0].remote_addr),
	sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}
	//close(sockfd); on garde la connexion ouverte
}

void send_msg(client* clients, const int id, msg* damsg) {
	if (send(clients[id].sockfd, damsg, sizeof(msg), 0) == -1)
		perror("send");
}

void kill_client(client* clients, const int id){
	log_smth("Fermeture de la connexion du client %d", id);
	close(clients[id].sockfd);
}

