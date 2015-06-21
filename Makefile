SRC=$(wildcard *.c)
OBJ=$(subst .c,.o,$(SRC))

CFLAGS=-Wall -fPIC
SHARLIB=.dylib

.PHONY: all clean

all:

lv3: lv3.o
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $@$(SHARLIB) $^

clean: clear

clear:
	rm -rf $(OBJ) *$(SHARLIB)
