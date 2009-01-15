#include "communication.h"

server[] init_servers(int port_start, const int max_connexions) {
	server[] servers;
	
	// TODO ajouter un for() pour le NB_SERV
	if ((servers[0]->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	servers[0]->local_addr.sin_family = AF_INET; /* host byte order */
	servers[0]->local_addr.sin_port = htons(port_start++); /* short, network byte order */
	servers[0]->local_addr.sin_addr.s_addr = INADDR_ANY; /* auto-remplissage avec mon IP */
	bzero(&(servers[0]->local_addr.sin_zero), 8); /* zero pour le reste de struct */

	if (bind(servers[0]->sockfd, (struct sockaddr *)&(servers[0]->local_addr), sizeof(struct sockaddr))
			== -1) {
		perror("bind");
		exit(1);
	}

	if (listen(servers[0]->sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	while(1) { /* main accept() loop */
		servers[0]->sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(servers[0]->sockfd, (struct sockaddr *)servers[0]->remote_addr,
								&(servers[0]->sin_size))) == -1) {
			perror("accept");
			continue;
		}
		printf("serveur: Reçu connection de %s\n",
				inet_ntoa(servers[0]->remote_addr.sin_addr));
		if (!fork()) { /* processus fils */
			if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
			perror("send");
			close(new_fd);
			exit(0);
		}
		close(new_fd); /* Le parent n'a pas besoin de cela */

		while(waitpid(-1,NULL,WNOHANG) > 0); /* Nettoyage des processus fils */
	}
}
