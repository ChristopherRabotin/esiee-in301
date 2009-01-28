#ifndef EXECUTION_
#define EXECUTION_

#include "casual_includes.h"
#include "../libbourse/alea.h"
#include "../libcomm/logger.h"
#include "../libcomm/message.h"
#include "../libbourse/PrixAchatVente.h"

/**
 * Execution recoit les ordres provenant du serveur d'acquisition, traite les transactions
 * et envoie les accusés de réception.
 *
 * Il prend en argument deux desripteurs de fichiers (0 et 1 pour tester dans le terminal)
 */
void execution_msg(msg *mess);
void execution(char* emetteur,char* type_transaction,char* id_action_ordre,char* quantite_ordre);

#endif /*EXECUTION_*/
