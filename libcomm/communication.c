#include "communication.h"

void init_servers(server* servers, const int nb_serv, int port_start,
		const int max_connexions) {
	int iteration, bourse=1, type;
	for (iteration=0; iteration < nb_serv; iteration++) {
		char name[128];
		if (iteration==0){
			sprintf(name, "Réseau inter-boursier"); type=interb;
		}else {
			if (iteration%2==0){
				sprintf(name, "Acquisition #000%d", bourse++); type=ack;
			}else{
				sprintf(name, "Exécution #000%d", bourse); type=exec;
			}
		}
		init_one_server(&servers[iteration], port_start++, max_connexions, name,type);
	} // fin du for
} // fin init_servers

void init_one_server(server* srv, const int port_start,
		const int max_connexions, const char* name, const int type) {
	srv->isAlive = 1;
	strcpy(srv->name, name);
	if ((srv->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	srv->local_addr.sin_family = AF_INET; /* host byte order */
	srv->local_addr.sin_port = htons(port_start); /* short, network byte order */
	srv->local_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
	bzero(&(srv->local_addr.sin_zero), 8); /* zero pour le reste de struct */

	if (bind(srv->sockfd,( struct sockaddr *)&(srv->local_addr),sizeof(struct sockaddr))
			== -1) {
		perror("bind");
		exit(1);
	}

	if (listen(srv->sockfd, max_connexions) == -1) {
		perror("listen");
		exit(1);
	}
	log_srv(*srv,"créé.");
	if(!fork()) { /* fils première génération - permet de revenir de la méthode par contre créé des zombies */
		while(1) { // boucle d'accept() pour recevoir les connexions
			int pid; // pid du fil
			srv->sin_size = sizeof(struct sockaddr_in);
			int new_fd; // descripteur lié au socket de la connexion courante
			if ((new_fd = accept(srv->sockfd, (struct sockaddr *)&(srv->remote_addr),
					&(srv->sin_size))) == -1) {
				perror("accept");
				continue;
			}
			if(!srv->isAlive) {
				close(new_fd); //si une connexion arrive alors que le programme est terminé, on sort
				exit(0);
			}
			char tmp[128];
			sprintf(tmp, "connexion entrante depuis %s:%d",inet_ntoa(srv->remote_addr.sin_addr),srv->remote_addr.sin_port);
			log_srv(*srv,tmp);
			if (!(pid=fork())) { /* fils seconde génération - permet d'être multiclient */
				while(srv->isAlive) {
					char answer[MAXRECVDATA];
					sprintf(answer,"Serveur %s. En attente d'un msg (voir libcomm/message.h).\n", srv->name);
					if (send(new_fd, answer, strlen(answer), 0) == -1)
						perror("send");

					srv->recvdata = (msg*) malloc (sizeof (msg));
					bzero(srv->recvdata,sizeof (msg));
					if (srv->isAlive && (srv->numbytes=recv(new_fd, srv->recvdata, MAXRECVDATA, 0)) == -1) {
						perror("recv");
						log_srv(*srv,"erreur lors du recv!");
						exit(1);
					}

					sprintf(tmp,"Reception par %s %s:%d",srv->name, inet_ntoa(srv->remote_addr.sin_addr),srv->remote_addr.sin_port);
					log_msg(tmp,srv->recvdata);
					switch(type){
					case ack: break;
					case exec: /*execution_msg(srv->recvdata);*/ break;
					default: log_smth("Tentative de démarrage d'un serveur non typé!");
					}
					//TODO ajouter l'exec() pour appeler le bon processus de gestion
				} // fin du while pour le recv()
				close(new_fd);
				exit(0);
			}
			close(new_fd); // le parent n'a pas besoin de new_fd

			while(waitpid(-1,NULL,WNOHANG) > 0); // nettoyage des processus fils
			srv->isAlive=0;
			kill(pid,SIGKILL);
			exit(0);
		} // fin while du "accept"
	} // fin fils première génération
}

void init_clients(client* clients, const int nb_serv, int port_start) {
	int iteration;
	for (iteration=0; iteration < nb_serv; iteration++) {
		char name[128];
		sprintf(name, (iteration==0 ? "Acquisition"
				: (iteration==1 ? "Execution" : "Terminal")));
		init_one_client(&clients[iteration], port_start++, name);
	}
}

void init_one_client(client* clt, const int port_start, const char* name) {
	strcpy(clt->name, name);

	if ((clt->he=gethostbyname("localhost")) == NULL) {
		herror("gethostbyname");
		log_clt(*clt, "erreur hôte introuvable");
	}

	if ((clt->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		log_clt(*clt, "erreur lors de l'init du socket");
	}

	clt->remote_addr.sin_family = AF_INET; /* host byte order */
	clt->remote_addr.sin_port = htons(port_start); /* short, network byte order */
	clt->remote_addr.sin_addr = *((struct in_addr *)(clt->he)->h_addr);
	bzero(&(clt->remote_addr.sin_zero), 8); /* zero pour le reste de struct */

	log_clt(*clt,"créé.");
	if (connect(clt->sockfd,( struct sockaddr *)&(clt->remote_addr),
			sizeof(struct sockaddr)) == -1) {
		perror("connect");
		log_clt(*clt,"déjà connecté ou impossible de se connecter");
	}
}

void send_msg(client clt, msg* damsg) {
	if (damsg == NULL) {
		log_clt(clt, "Tentative d'envoi d'un message NULL");
		return;
	}
	char tmp[128];
	sprintf(tmp, "Envoi vers %s", inet_ntoa(clt.remote_addr.sin_addr));
	log_msg(tmp, damsg);

	if (send(clt.sockfd, damsg, sizeof(msg), 0) == -1) {
		perror("send");
		log_clt(clt, "erreur lors de l'envoi du message");
	}
	//close(clt.sockfd);
}

void log_srv(const server srv, char* un_msg) {
	char logged[1024];
	sprintf(logged, "Serveur %s %s", srv.name, un_msg);
	private_write_log(comm_type, logged);
}

void log_clt(const client clt, char* un_msg) {
	char logged[1024];
	sprintf(logged, "Client %s %s", clt.name, un_msg);
	private_write_log(comm_type, logged);
}

