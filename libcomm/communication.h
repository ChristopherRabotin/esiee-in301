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
#include <netdb.h> 

//#include "logger.h" déjà inclus dans message.h
#include "message.h"

#define MAXRECVDATA 1024 /* nombre de serveurs à être initialisés */
/**
 * server comprend toutes les données nécessaires au bon fonctionnement d'un serveur.
 */
typedef struct server_struct {
	int isAlive; /* permet de savoir si le serveur tourne ou non */
	int id; /* identifiant du serveur */
	char name[128]; /* nom du serveur (Acquisition, Execution, Terminal) */
	int sockfd; /* descripteur du socket */
	int my_port; /* port du serveur*/
	int max_conn; /* nombre maximal de connexions */
	int numbytes; /* nombre d'octets reçus par une connexion */
	socklen_t sin_size; /* taille du socket */
	struct sockaddr_in local_addr; /* adresse locale */
	struct sockaddr_in remote_addr; /* adresse distante*/
	msg *recvdata; /* données reçues */
} server;

/**
 * client comprend toutes les données nécessaires au bon fonctionnement d'un client.
 * Par la suite, lors de l'appel de la fonction d'envoie de message, nous passerons donc le tableau
 * de clients et l'identifiant du client et enfin le message (msg) à envoyer.
 */
typedef struct client_struct {
	int id; /* identifiant du client */
	char name[128]; /* nom du client (Acquisition, Execution, Terminal) */
	int sockfd; /* descripteur du socket */
	int my_port; /* port de connexion au serveur*/
	int numbytes; /* nombre d'octets reçus par une connexion */
	socklen_t sin_size; /* taille du socket */
	struct hostent *he; /* informations de l'hôte */
	struct sockaddr_in local_addr; /* adresse locale */
	struct sockaddr_in remote_addr; /* adresse distante*/
} client;

enum ORDRE {ack,exec,term};
/**
 * Permet d'initialiser les serveurs des différents modules du programme.
 * Retourne un tableau des serveurs initialisés.
 * @param servers tableau de serveurs dans lequel les données concernant ces serveurs sont stockées
 * @param nb_serv nombre de serveurs (correspond au nombre de cases dans le tableau servers)
 * @param port_start port du premier serveur. Les autres sont port_start+i.
 * @param max_connexions nombre maximal de connexions simultannées par serveur
 */
void init_servers(server* servers, const int nb_serv, int port_start,
		const int max_connexions);

/**
 * Permet d'initialiser les clients des différents modules du programme.
 * Retourne un tableau des clients initialisés. Il faut conserver ce tableau pour envoyer
 * des messages par la suite!
 * @param clients tableau des clients
 * @param nb_serv nombre de serveurs à être initialisés 
 * @param port_start port de connexion du premier serveur. Les autres devraient être à port_start+i.
 */
void init_clients(client* clients, const int nb_serv, int port_start);

/**
 * Envoi d'un message par socket vers le bon serveur. Il suffit de passer en paramètre
 * le bon client (toAck,toExec,toTerm) et le message (msg) à envoyer.
 * @param clt le client qui envoit le message
 * @param damsg le message à envoyer
 */
void send_msg(const client clt, msg* damsg);

/*
 * Ferme la connexion d'un client.
 * <b>Attention</b> ceci est permanent!
 * @param clt le client dont on doit fermer la connexion
 */
void kill_client(const client clt);

/**
 * Permet de tuer un serveur.
 * <b>Attention</b> ceci est permanent!
 * @param srv le serveur à tuer.
 */
void kill_server(server *srv);
/**
 * Permet de logguer les communications des serveurs. Placé dans communication.h puisque
 * utilisé uniquement pour la communication par socket.
 * @param srv le serveur d'où le log émane
 * @param un_msg message d'explication lié à l'ordre de transaction 
 */
void log_srv(const server srv, char* un_msg);

/**
 * Permet de logguer les communications des clients. Placé dans communication.h puisque
 * utilisé uniquement pour la communication par socket.
 * @param clt le client d'où le log émane 
 * @param un_msg message d'explication lié 
 */
void log_clt(const client clt, char* un_msg);
#endif /*COMMUNICATION_H_*/
