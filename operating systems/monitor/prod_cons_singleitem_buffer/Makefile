all: start

start: main.o buffer.o
	gcc -o start main.o buffer.o

main.o: main.c buffer.h
	gcc -c main.c

buffer.o: buffer.c buffer.h
	gcc -c buffer.c

clean:
	rm start
	rm *.o