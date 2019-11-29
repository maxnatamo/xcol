CC = gcc
NAME = xcol
VERSION = v1.0

LIB = `pkg-config --libs x11`
INC = `pkg-config --cflags x11`
CFLAGS = -Wall -DVERSION=\"${VERSION}\"

SRC = xcol.c util.c

all: options build

options:
	@echo "${NAME} BUILD OPTIONS"
	@echo "SRC      ${SRC}"
	@echo "CC       ${CC}"
	@echo "CFLAGS   ${CFLAGS}"
	@echo "LIB      ${LIB}"
	@echo "INC      ${INC}"
	@echo ""

build:
	${CC} ${SRC} ${LIB} ${INC} ${CFLAGS} -o ${NAME}

install:
	mkdir -p /usr/local/bin
	cp -f ${NAME} /usr/local/bin
	chmod 755 /usr/local/bin/${NAME}
	mkdir -p /usr/local/share/man/man1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > /usr/local/share/man/man1/${NAME}.1
	chmod 644 /usr/local/share/man/man1/${NAME}.1

uinstall:
	rm -f /usr/local/bin/${NAME}
	rm -f /usr/local/share/man/man1/${NAME}.1

clean:
	rm -rf ${NAME}

.PHONY: all options build clean install uninstall
