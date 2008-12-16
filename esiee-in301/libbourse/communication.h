/**
 * communication.h gère toutes les communications au sein du programme.
 * Grâce aux defines, ce header exécute les bonnes méthodes.
 * Les communications disponibles sont:
 * 		+ par fichiers: implémentation bouchon
 * 		+ par pipe (ou tube): implémentation demandée
 * 		+ par socket: implémentation supplémentaire
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

void envoi(const char* message, const void* id);
char* recoit();

#endif /*COMMUNICATION_H_*/
