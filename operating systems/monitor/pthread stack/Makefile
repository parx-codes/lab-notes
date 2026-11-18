stack: stack.o stack_user.o
	gcc -pthread -o stack stack.o stack_user.o

stack.o: stack.c stack.h
	gcc -c -o stack.o stack.c

stack_user.o: stack_user.c stack.h
	gcc -c -o stack_user.o stack_user.c

clean:
	rm -f stack
	rm -f *.o
