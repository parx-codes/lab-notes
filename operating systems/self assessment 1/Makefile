all: start

start: start.o procedure.o
	gcc -o start start.o procedure.o -lpthread

start.o: start.c header.h
	gcc -c start.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f start
