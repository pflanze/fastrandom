
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "CMWC.c"

#define BUFLEN 1024

int main () {
    unsigned long buf[BUFLEN];
    
    while(1) {
	{
	    int i;
	    for (i=0; i<BUFLEN; i++) {
		buf[i]= CMWC();
	    }
	}
	{
	    ssize_t res= write(1,buf,sizeof(buf));
	    if (res != sizeof(buf)) {
		perror("write");
		exit(1);
	    }
	}
    }
    return 0;
}

