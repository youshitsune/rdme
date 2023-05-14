CC = cc

all: rdme

rdme:
	${CC} main.c -o rdme

install: rdme
	cp rdme /usr/bin/

uninstall:
	rm -f /usr/bin/rdme

