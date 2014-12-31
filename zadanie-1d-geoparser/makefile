CC     = gcc
CFLAGS = -O2

geoparser: main.o calculations.o
	$(CC) $(CFLAGS) -o geoparser main.o calculations.o -ljson

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

calculations.o: calculations.c
	$(CC) $(CFLAGS) -c -o calculations.o calculations.c

clean:
	rm -f *.o
	rm -f geoparser
