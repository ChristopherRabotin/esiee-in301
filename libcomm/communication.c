#include "communication.h"

void init_servers(server* servers, const int nb_serv, int port_start, const int max_connexions) {
#ifdef DEBUG
	init_log("libcomm.log");
#endif

	int iteration;
	for(iteration=0; iteration < nb_serv; iteration++){
		servers[iteration].id = iteration;
		if ((servers[iteration].sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}
#ifdef DEBUG
		log_smth("création du serveur #%d",iteration);
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
		if(!fork()){ /* fils première génération - permet de revenir de la méthode par contre créé des zombies */
			while(1) { /* main accept() loop */
				servers[iteration].sin_size = sizeof(struct sockaddr_in);
				int new_fd; // descripteur lié au socket de la connexion courante
				if ((new_fd = accept(servers[iteration].sockfd, (struct sockaddr *)&(servers[iteration].remote_addr),
						&(servers[iteration].sin_size))) == -1) {
					perror("accept");
					continue;
				}
				printf("serveur: Reçu connection de %s\n",
						inet_ntoa(servers[iteration].remote_addr.sin_addr));
				if (!fork()) { /* fils seconde génération - permet d'être multiclient */
					char answer[128];
					// TODO non important: servers[iteration].id vaut (null) (iteration a disparu)
					sprintf(answer,"Hi! This is server %d answering.\n", servers[iteration].id);
					if (send(new_fd, answer, strlen(answer), 0) == -1)
						perror("send");
					close(new_fd);
					exit(0);
				}
				close(new_fd); /* Le parent n'a pas besoin de new_fd */

				while(waitpid(-1,NULL,WNOHANG) > 0); /* Nettoyage des processus fils */
			}
		}
	}
}
