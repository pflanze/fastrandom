fastrandom: fastrandom.c CMWC.c
	gcc -Wall -O3 -o fastrandom fastrandom.c

install: fastrandom
	install fastrandom /usr/local/bin/
