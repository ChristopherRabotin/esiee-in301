/**
 * @author: Christopher Rabotin
 * communication.h gère toutes les communications au sein du programme.
 * Grâce aux defines, ce header exécute les bonnes méthodes.
 * Les communications disponibles sont:
 * 		+ par fichiers: implémentation bouchon
 * 		+ par pipe (ou tube): implémentation demandée
 * 		+ par socket: implémentation supplémentaire
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "../casual_includes.h"
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 

#include logger.h
#include message.h
//TODO faire un struct pour stocker toutes les données des serveurs.
/**
 * server correspond 
 */
typedef struct server_struct {
	int sockfd,sin_size, my_port, max_conn;
	struct sockaddr_in local_addr;
	struct sockaddr_in dest_addr;

}server;

/**
 * Permet d'initialiser les serveurs des différents modules du programme.
 */
int init_servers(int nb_serveurs, server tr);
int init_clients();

/*
 * Envoi un message via le descripteur passé, en utilisant le moyen de
 * communication spécifié lors de la compilation
 * @param char* message le message à envoyer
 * @param void* id le nom du moyen de communication utilisé.
 *
 * Exemple: envoi(msg,"example"); // utilisera le descripteur nommé 'example' 
 */
void envoi(const char* message, const void* id);

/**
 * Thread s'occupant de lire tous les messages reçus par le moyen de communication
 * utilisé. Le message reçu sera probablement stocké dans un pipe le temps d'être
 * appelé par le reste du programme. TODO idée à revoir, potentiellement
 * Thread lancé dès le premier appel. Si on tente de le rappeller par la suite
 * il envoie un message sur std_err spécifiant qu'il est déjà lancé.
 * 
 */
char* recoit();

#endif /*COMMUNICATION_H_*/
