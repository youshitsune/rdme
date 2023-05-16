CC = cc

all: rdme

rdme:
	${CC} main.c -o rdme

install: clean rdme
	cp -f rdme /usr/bin/

uninstall:
	rm -f /usr/bin/rdme

clean:
	rm -f rdme
