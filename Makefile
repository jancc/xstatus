CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
OBJ = dwmstatus.o
BIN = dwmstatus
PREFIX = /usr/local

prog: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

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
