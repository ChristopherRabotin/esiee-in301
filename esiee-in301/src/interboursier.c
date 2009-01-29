#include "interboursier.h"





/**
 * Interboursier reçoit des messages et les analyse afin de savoir vers quel serveur d'acquisition les diriger.
 */
void interboursier(char* emetteur,char* type_transaction,char* id_action_ordre,char* quantite_ordre){
	int i;
	//On regarde si le message est un ordre ou un accusé
	if(type_transaction[2]=='c'){ //c = 3è lettre de Accusé
	//Si c'est un accusé, on analyse les 4 premiers chiffres de l'emetteur
	//(banque où se trouve le commerçant).
		char bourse_origine[100];
		for(i=0;i<4;i++){
			strncat(bourse_origine,emetteur+i,1);
		}
		printf("bourse d'origine: %s",bourse_origine);

	}
	//Si c'est un ordre, on analyse les 4 premiers chiffres de l'identifiant
	//de l'action (banque où est cotée l'action).
	else {
		char bourse_cotation[100];
		for(i=0;i<4;i++){
			strncat(bourse_cotation,id_action_ordre+i,1);
		}
		printf("bourse de cotation:%s",bourse_cotation);
	}
}
