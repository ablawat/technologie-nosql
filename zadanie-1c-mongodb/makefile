CC     = gcc
CFLAGS = -O2
DEBUG  = -g

LIBS   = $(shell pkg-config --libs libmongoc-1.0) -ljson
MONGOC = $(shell pkg-config --cflags libmongoc-1.0)

debug: CFLAGS = $(DEBUG)
debug: zadanie-mongodb

zadanie-mongodb: main.o linked-list-tag.o queries.o
	$(CC) $(CFLAGS) -o zadanie-mongodb main.o linked-list-tag.o queries.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c $(MONGOC)

linked-list-tag.o: linked-list-tag.c linked-list-tag.h
	$(CC) $(CFLAGS) -c -o linked-list-tag.o linked-list-tag.c

queries.o: queries.c queries.h
	$(CC) $(CFLAGS) -c -o queries.o queries.c $(MONGOC)

clean:
	rm -f zadanie-mongodb *.o
