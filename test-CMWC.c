
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "CMWC.c"

#define BUFLEN 1024


void initQ () {
    int fd= open("/dev/urandom", O_RDONLY);
    if (fd<0) {
	perror("open");
	exit(1);
    }
    {
	ssize_t res;
	res= read(fd, Q, sizeof(Q));
	if (res != sizeof(Q)) {
	    perror("read");
	    exit(1);// ah I wanted a return value for that?
	}
    }
}

int main () {
    unsigned long buf[BUFLEN];

    initQ();
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

