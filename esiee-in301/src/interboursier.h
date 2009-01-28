#ifndef EXECUTION_
#define EXECUTION_

#include "casual_includes.h"
#include "../libbourse/alea.h"
#include "../libcomm/logger.h"
#include "../libcomm/message.h"
#include "../libbourse/PrixAchatVente.h"

/**
 * Interboursier reçoit des messages et les analyse afin de savoir vers quel serveur d'acquisition les diriger.
 */
void interboursier();

#endif /*EXECUTION_*/
