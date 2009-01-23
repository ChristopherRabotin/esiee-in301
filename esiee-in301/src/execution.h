#ifndef EXECUTION_
#define EXECUTION_

#include "../casual_includes.h"
#include "../libbourse/alea.h"
#include "../libcomm/logger.h"
#include "../libcomm/message.h"
#include "../libbourse/PrixAchatVente.h"

/**
 * Cette méthode permet de recevoir
 *
 */
void execution_msg(msg *mess);
void execution(char* emetteur,char* type_transaction,char* id_action_ordre,char* quantite_ordre);

#endif /*EXECUTION_*/
