all: start produttore consumatore

start: start.o
	gcc -o start start.o -lrt -lpthread

produttore: produttore.o procedure.o
	gcc -o produttore produttore.o procedure.o -lrt -lpthread -lm

consumatore: consumatore.o procedure.o
	gcc -o consumatore consumatore.o procedure.o -lrt -lpthread -lm

start.o: start.c header.h
	gcc -c start.c

produttore.o: produttore.c header.h
	gcc -c produttore.c

consumatore.o: consumatore.c header.h
	gcc -c consumatore.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f start
	rm -f produttore
	rm -f consumatore
