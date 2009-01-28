#ifndef TERMINAL_H_
#define TERMINAL_H_
// includes
#include "../casual_includes.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libbourse/alea.h"
#include "../libcomm/logger.h"
#include "../libcomm/message.h"

/**
 * Terminal permet d'envoyer un ordre conçu aléatoirement à partir des annuaires (commerçants,actions)
 * et de valeurs aléatoires.
 * Il reçoit et affiche à l'écran un accusé de réception provenant du serveur d'acquisition
 *
 * Il prend 2 descripteurs de fichiers en paramètres vers lesquels il redirige son entrée et sa sortie standarts.
 */

// prototypes
void terminal();

#endif /*TERMINAL_H_*/
