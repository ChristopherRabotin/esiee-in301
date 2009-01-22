#ifndef EXECUTION_
#define EXECUTION_

#include "casual_includes.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libbourse/alea.h"
#include "libcomm/logger.h"
#include "libcomm/message.h"
#include "libbourse/PrixAchatVente.h"

/**
 * Cette méthode permet de recevoir
 *
 */
void received_order(FILE*);

void execution();

#endif /*EXECUTION_*/
