#include "logger.h"

char *filename;

int init_log(const char *fn) {
	FILE *fp = fopen(fn, "a+");
	if (fp== NULL)
		return 0; // échec
	fclose(fp);
	filename=fn;
	return 1; // succès
}

void log_call(const char *msg, char *func_name, const char *args, ...) {
	char fctNargs[256] = { 0 };
	sprintf(fctNargs, "%s%s", func_name, argsfmt); // concaténation
	va_list arglist; // nouveau struct qui va contenir les arguments
	va_start(arglist, argsfmt);
	// extraction des arguments et/ou de leurs type
	private_log_call(msg, fctNargs, arglist);
	va_end(arglist);
}

void log(const char *msg) {
	FILE *fp = fopen(filename, "a+");
	if (fp == NULL)
		return; // ne devrait pas arriver vu la vérif dans init_log
	fprintf(fp, "%s", private_start_log(call_type));
	fprintf(fp, "\t%s", msg);
	fwrite("\n", 1, 1, fp);
	fflush(fp);
	fclose(fp);
}

// début des fonctions/méthodes non détaillées dans l'API
enum LOG_TYPES { call_type, msg_type, unkown_type };
/**
 * Permet de logguer l'appel à une fonction, avec des paramètres.
 * Il n'est pas conseillé d'appeler cetter fonction directement! Passez plutôt par "log" qui s'occupe de tout.
 * @param *msg le message à être loggué
 * @param *func_name nom de la fonction
 * @param *args arguments passés à la fonction
 */
void private_log_call(const char *msg, const char *func_name, va_list args) {
	FILE *fp = fopen(filename, "a+");
	if (fp == NULL)
		return; // ne devrait pas arriver vu la vérif dans init_log

	fprintf(fp, "%s", private_start_log(call_type));
	vfprintf(fp, fmt, args); // détermine le type de variable et l'affiche
	fprintf(fp, "\t%s", msg);
	fwrite("\n", 1, 1, fp);
	fflush(fp);
	fclose(fp);
}
/**
 * Permet de mettre en forme le début du log.
 * @param log_type type de log, voir l'enum plus haut
 * @return une chaine de caractères représentant le but
 */
char *private_start_log(int log_type) {
	time_t curTime;
	time(&curTime);

	char timeStamp[32] = { 0 }, rtn[32] = { 0 }, tmp[3]= { 0 };
	strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", localtime(&curTime));
	switch(log_type) {
		case call_type: tmp="[*]"; break;
		case msg_type: tmp="[M]"; break;
		default: tmp="[U]";
	}
	sprintf(rtn,"%s <%s>",tmp, timeStamp);
	return rtn;
}
