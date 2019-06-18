CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib
LIBS = -L${X11LIB} -lX11
INCLUDE = -I${X11INC}
OBJ = dwmstatus.o
BIN = dwmstatus
PREFIX = /usr/local

prog: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) $(OBJ) -o $(BIN)

debug: CFLAGS += -DDEBUG
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
	cp -f dwmstatus ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/dwmstatus

uninstall:
	rm -f ${PREFIX}/bin/dwmstatus


.PHONY: clean install uninstall
