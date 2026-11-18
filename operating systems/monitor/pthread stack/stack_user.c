#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DIM_STACK 4

void *Inserisci(void * s)
{

	int i;
	Elem v;
    
    Stack * stack = (Stack *) s;

	for(i=0; i<4; i++) {
		v = rand() % 11;
		StackPush(stack, v);
		printf("Inserimento: %d\n", v);
		sleep(1);
	}

	// TODO: Terminazione thread
	pthread_exit(NULL);
}


void *Preleva(void * s)
{

	int i;
	Elem v1, v2;

    Stack * stack = (Stack *) s;
    
	for(i=0; i<10; i++) {
		v1=StackPop(stack);
		printf("Prelievo: %d\n", v1);

		v2=StackPop(stack);
		printf("Prelievo: %d\n", v2);

		printf("Somma: %d\n", v1+v2);

		sleep(3);
	}

	// TODO: Terminazione thread
	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{
	// TODO: Definire i thread
	pthread_t threads[6];
	int i;

	srand(time(NULL));

	// TODO: Allocare e istanziare lo stack
	Stack* s = (Stack*)malloc(sizeof(Stack));
	StackInit(s,DIM_STACK);

	// TODO: Attributi thread

	for(i=0; i<5; i++) {
		pthread_create(&threads[i],NULL,Inserisci,s);
	}

	// TODO: Creazione thread per il prelievo
	pthread_create(&threads[5],NULL,Preleva,s);

	for(i=0; i<6; i++) {
		// TODO: Attesa terminazione thread
		pthread_join(threads[i],NULL);
	}
	// TODO: Distruzione thread

	// TODO: Rimozione stack
	StackRemove(s);
	free(s);
}

