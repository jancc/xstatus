VERSION = 0.2.0-pre

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -DVERSION=\"${VERSION}\"
X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib
LIBS = -L${X11LIB} -lX11
INCLUDE = -I${X11INC}
OBJ = xstatus.o
BIN = xstatus
PREFIX = /usr/local

prog: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) $(OBJ) -o $(BIN)

debug: CFLAGS += -DDEBUG -g
debug: prog

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $<

${OBJ}: config.h

config.h:
	cp config.def.h $@

clean:
	rm *.o
	cd ..
	rm $(BIN)

install: prog
	mkdir -p ${PREFIX}/bin
	cp -f xstatus ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/xstatus

uninstall:
	rm -f ${PREFIX}/bin/xstatus

format:
	clang-format -i *.c *.h

.PHONY: clean install uninstall format
