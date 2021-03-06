
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <assert.h>


#include "CMWC.c"

#define BUFLEN 1024


int urandomfd;

void init () {
    urandomfd= open("/dev/urandom", O_RDONLY);
    if (urandomfd<0) {
	perror("open");
	exit(1);
    }
}

void readurandom (void*buf, ssize_t size) {
    ssize_t res;
    res= read(urandomfd, buf, size);
    if (res != size) {
	perror("read");
	exit(1);// ah I wanted a return value for that?
    }
}

void initQ () {
    readurandom(Q,sizeof(Q));
}


void usage(char*prg) {
    printf("usage: %s\n",prg);
    printf("  write an endless stream of random bytes to stdout\n");
    exit(1);
}

int main (int argc, char**argv) {
    unsigned long buf[BUFLEN];
    unsigned long mixin[2*BUFLEN];
    int mixin_start=BUFLEN;
    unsigned long v=0;

    if (argc!=1) {
	usage(argv[0]);
    }

    init();
    initQ();//
    while(1) {
	{
	    assert(mixin_start <= BUFLEN);
	    if (mixin_start == BUFLEN) {
		// fprintf(stderr,"re-reading mixin\n");
		readurandom(mixin,sizeof(mixin));
		mixin_start=0;
	    }
	    mixin_start++;
	}
	{
	    int i, mixin_i=mixin_start;
	    for (i=0; i<BUFLEN; i++) {
		v= CMWC() ^ mixin[mixin_i] ^ v;
		buf[i]= v;
		mixin_i++;
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

