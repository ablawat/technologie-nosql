CC     = gcc
CFLAGS = -O2

LIBS   = $(shell pkg-config --libs libmongoc-1.0)
MONGOC = $(shell pkg-config --cflags libmongoc-1.0)

aggregations: main.o queries.o
	$(CC) $(CFLAGS) -o aggregations main.o queries.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c $(MONGOC)

queries.o: queries.c
	$(CC) $(CFLAGS) -c -o queries.o queries.c $(MONGOC)

clean:
	rm -f *.o aggregations
