#include "logger.h"

char *filename= NULL;

int init_log(const char *fn) {
	FILE *fp = fopen(fn, "a+");
	if (fp== NULL)
		return 0; // échec
	fclose(fp);
	filename =( char*)malloc( strlen(fn + 1) );
	strcpy(filename, fn);
	return 1; // succès
}

void log_call(const char *msg, char *func_name, const char *args, ...) {
	char fctNargs[256] = { 0 };
	sprintf(fctNargs, "%s%s", func_name, args); // concaténation
	va_list arglist; // nouveau struct qui va contenir les arguments
	va_start(arglist, args);
	// extraction des arguments et/ou de leurs type
	private_log_call(msg, fctNargs, arglist);
	va_end(arglist);
}

void log_smth(const char *msg) {
	private_write_log(unkown_type, msg);
}

// début des fonctions/méthodes non détaillées dans l'API
// elles ne sont pas dans l'API pour ne pas chargée cette dernière de fonctions réservées au code interne

void private_log_call(const char *msg, const char *func_name, va_list args) {
	char vspft[32] = { 0 }, new_msg[256] = { 0 };
	vsprintf(vspft, func_name, args); // détermine le type de variable et l'affiche
	sprintf(new_msg, "%s %s", vspft, msg);
	private_write_log(call_type, new_msg);
}

void private_write_log(int log_type, const char* msg) {
	// TODO: ajouter un sémaphore pour ne pas avoir des logs qui déconnent
	// on commence par déterminer l'heure à laquelle le log a lieu (en secondes)
	time_t curTime;
	time(&curTime);

	char tmp[3]= { 0 }, timeStamp[32] = { 0 };
	int test = strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", localtime(&curTime));
	switch(log_type) {
		case call_type: strcpy(tmp,"[*]"); break;
		case msg_type: strcpy(tmp,"[M]"); break; // 'M' comme Message
		default: strcpy(tmp,"[U]"); // 'U' comme Unkown
	}
	FILE *fp = fopen(filename, "a+"); // ouverture du fichier de log en mode "append" (ajout)
	if (fp == NULL) {
		// ne devrait pas arriver vu la vérif dans init_log, sauf si les permissions changent pendant le 
		// déroulement du programme...
		// si on ne peut pas logger, alors on affiche erreur puis le message à être loggué dans stderr
		fprintf(stderr, "Erreur lors de l'ouverture du fichier \"%s\" en mode append!",filename);
		fprintf(stderr, "[F] %s", msg);
		return;
	}
	fprintf(fp, "%s <%s>", tmp, timeStamp);
	fprintf(fp, "\t%s", msg);
	fwrite("\n", 1, 1, fp);
	fflush(fp);
	fclose(fp);

	}
