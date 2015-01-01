CC     = gcc
CFLAGS = -O2

LIBS   = $(shell pkg-config --libs libmongoc-1.0) -ljson
MONGOC = $(shell pkg-config --cflags libmongoc-1.0)

zapytanie-1: main.o
	$(CC) $(CFLAGS) -o zapytanie-1 main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c $(MONGOC)

clean:
	rm -f *.o zapytanie-1
