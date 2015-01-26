CC     = gcc
CFLAGS = -O2

LIBS = $(shell xml2-config --libs)
XML2 = $(shell xml2-config --cflags)

xml-json-parser: main.o calculations.o
	$(CC) $(CFLAGS) -o xml-json-parser main.o calculations.o $(LIBS) -ljson

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c $(XML2)

calculations.o: calculations.c
	$(CC) $(CFLAGS) -c -o calculations.o calculations.c

clean:
	rm -f *.o
	rm -f xml-json-parser
