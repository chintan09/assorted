# Excellent makefile tutorial : http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

# Couldn't figure out how this works. 
#_DEPS = helper.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ = helper.o main.o 
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

DEPS=helper.h
OBJ=helper.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ main *.o
