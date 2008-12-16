#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "alea.h"

void aleainit() {
	srand((unsigned)time( NULL ) + getpid() );
}

int alea(int min, int max) {
	int lgr;
	lgr = max-min+1;
	return ((int)((double)rand()/RAND_MAX*lgr+min));
}

