#ifndef TERMINAL_H_
#define TERMINAL_H_
// includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libbourse/alea.h"
#include "libcomm/logger.h"
#include "libcomm/message.h"

// prototypes
void terminal();
void envoie_ordre();
#endif /*TERMINAL_H_*/



