#include <stdlib.h>
#include <stdio.h>
#include "../libcomm/logger.h"

/**
 * author Christopher Rabotin
 */

void testParamChar(const char* str){
	log_call("dans testParamChar", "testParamChar", "(\"%s\")", str);
	printf("Blah: %s\n", str);
}

int testParamInt(int arg1, int arg2){
	log_call("dans testParamInt", "testParamInt", "(%d,%d)", arg1, arg2);
	testParamChar("le message");
	return arg1+arg2;
}

int main(int argc, char **argv) {
	char *fn = "./TestLogger.log";
	if(!init_log(fn)){
		fprintf(stderr, "Impossible de modifier le fichier %s\n",fn);
		exit(0);
	}
	log_smth("Okeille c'est bon, l'init est passé youpi!");
	testParamInt(2,5);
	
	return 0;
}
