IDIR =include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = dhash.h mparser.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
FDEPS =$(_DEPS)

_OBJ =  mparser.o dhash.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(FDEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mparser: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
