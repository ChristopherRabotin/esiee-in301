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
#include <unistd.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <sys/wait.h> 

#include "logger.h"
#include "message.h"

#define MAXRECVDATA 1024 /* nombre de serveurs à être initialisés */

/**
 * server comprend toutes les données nécessaires au bon fonctionnement d'un serveur.
 */
typedef struct server_struct {
	int id; /* identifiant du serveur */
	char name[128]; /* nom du serveur (Acquisition, Execution, Terminal) */
	int sockfd; /* descripteur du socket */
	int my_port; /* port du serveur*/
	int max_conn; /* nombre maximal de connexions */
	int numbytes; /* nombre d'octets reçus par une connexion */
	socklen_t sin_size; /* taille du socket */
	struct sockaddr_in local_addr; /* adresse locale */
	struct sockaddr_in remote_addr; /* adresse distante*/
	char recvdata[MAXRECVDATA]; /* données reçues */
} server;

/**
 * Permet d'initialiser les serveurs des différents modules du programme.
 * Retourne un tableau des serveur initialisés (de taille NB_SERV puisqu'il y a NB_SERV serveurs)
 * @param servers tableau de serveurs dans lequel les données concernant ces serveurs sont stockées
 * @param nb_serv nombre de serveurs (correspond au nombre de cases dans le tableau servers)
 * @param port_start port du premier serveur. Les autres sont port_start+1.
 * @param max_connexions nombre maximal de connexions simultannées par serveur
 */
void init_servers(server* servers, const int nb_serv, int port_start, const int max_connexions);
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
