/**
 * @author Christopher Rabotin
 * Logger permet de logguer l'activité du programme.
 * Les méthodes présentes ici permettrons d'éviter d'utiliser printf() afin de savoir précisément
 * d'où l'appel a été effectué et l'heure de cet appel.
 * --
 * La fonction de trace est basée sur un code C++: http://www.codeproject.com/KB/cpp/cmtrace.aspx
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Permet d'initialiser le fichier de log en vérifiant si le fichier peut-être ouvert en écriture.
 * Si DEBUG_TO_STDOUT est défini, alors l'appel à cette fonction n'est pas nécessaire avant de logguer.
 * Au contraire, un message sera affiché dans stderr si la fonction de log est appelée avec l'init. 
 * @param *filename nom du fichier
 * @return Bernouilli: 0 <=> échec  1 <=> succès
 */
int init_log(const char *filename);

/**
 * Permet de tracer une fonction, avec les paramètres passés, puis appelle private_log_call().
 * Si DEBUG_TO_STDOUT est défini, alors le message de log est affiché dans stdout.
 * Tous les logs concernant les fonctions seront précédés d'un [*].
 * @param *msg le message à être loggué
 * @param *func_name nom de la fonction
 * @param *args arguments passés à la fonction
 * @param ... signifie qu'il peut y avoir plusieurs arguments. Pour les extraire, on utilisera stdarg.h
 * 
 * Exemple d'utilisation:
 * log_call("si erreur, vérifier paramètres", fct, fct_arg1, fct_arg2, fct_arg3);
 */
void log_call(const char *msg, char *func_name, const char *args, ...);

/**
 * Permet de logguer un message divers.
 * @param msg le message à être loggué
 */
void log_smth(const char *msg);
//TODO log_msg pour logger les ordres de transactions

// ce qui concerne le fonctionnement interne du logguer
// il n'est pas conseillé d'appeler les fonctions ci-dessous directement (d'où le préfixe "private_")
enum LOG_TYPES {call_type, msg_type, unkown_type};
/**
 * Permet de logguer l'appel à une fonction, avec des paramètres.
 * Il n'est pas conseillé d'appeler cetter fonction directement! Passez plutôt par "log" qui s'occupe de tout.
 * @param *msg le message à être loggué
 * @param *func_name nom de la fonction
 * @param *args arguments passés à la fonction
 */
void private_log_call(const char *msg, const char *func_name, va_list args);

/**
 * Permet d'écrire le log d'un message passé, suivant le type de log
 * @param log_type type de log, voir l'enum plus haut
 * @param msg le message à être loggué
 */
void private_write_log(int log_type, char* msg);

#endif /*LOGGER_H_*/
