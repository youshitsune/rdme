CC = cc

all: rdme

rdme:
	${CC} main.c -o rdme

install: rdme
	cp -f rdme /usr/bin/

uninstall:
	rm -f /usr/bin/rdme

