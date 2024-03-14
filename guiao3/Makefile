CC = gcc
CFLAGS = -Wall -g

all: guiao3 controlador auxiliares

mysystem.o: mysystem.c mysystem.h
	$(CC) $(CFLAGS) -c mysystem.c -o mysystem.o

guiao3.o: guiao3.c mysystem.h
	$(CC) $(CFLAGS) -c guiao3.c -o guiao3.o

guiao3: guiao3.o mysystem.o
	$(CC) $(CFLAGS) guiao3.o mysystem.o -o guiao3

controlador: controlador.o mysystem.o
	$(CC) $(CFLAGS) controlador.o mysystem.o -o controlador

controlador.o: controlador.c mysystem.h
	$(CC) $(CFLAGS) -c controlador.c -o controlador.o

auxiliares: auxiliar.c
	$(CC) $(CFLAGS) auxiliar.c -o a.out
	$(CC) $(CFLAGS) auxiliar.c -o b.out
	$(CC) $(CFLAGS) auxiliar.c -o c.out

clean:
	rm -rf *.dSYM *.o guiao3 controlador a.out b.out c.out