CC     = gcc
CFLAGS = -O2

json-parser: main.o calculations.o
	$(CC) $(CFLAGS) -o json-parser main.o calculations.o -ljson

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

calculations.o: calculations.c
	$(CC) $(CFLAGS) -c -o calculations.o calculations.c

clean:
	rm -f *.o
	rm -f json-parser
