#ifndef EXECUTION_
#define EXECUTION_

#include "casual_includes.h"
#include "../libcomm/logger.h"
#include "../libcomm/message.h"
#include "../libcomm/communication.h"

/**
 * Interboursier reçoit des messages et les analyse afin de savoir vers quel serveur d'acquisition les diriger.
 */
void interboursier(char* emetteur,char* type_transaction,char* id_action_ordre,char* quantite_ordre);

#endif /*EXECUTION_*/
