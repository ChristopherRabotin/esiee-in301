#include <stdlib.h>
#include <stdio.h>
#include "../libcomm/logger.c"

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
	if(!init_log("./TestLogger.log")){
		fprintf(stderr, "Impossible de toucher à ../TestLogger.log");
	}
	log_smth("Okeille c'est bon, l'init est passé youpi!");
	testParamInt(2,5);
	
	return 0;
}
