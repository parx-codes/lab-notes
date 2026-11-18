#ifndef __HEADER__
#define __HEADER__

#include <pthread.h>

typedef int Elem;

typedef struct {
	Elem * dati;	// puntatore ad un vettore dinamico di elementi
	int dim;		// dimensione dello Stack
	// TODO: variabili per la sincronizzazione (Monitor)
	int cont;
	pthread_mutex_t mutex;
	pthread_cond_t vuoto;
	pthread_cond_t pieno;
} Stack;

void StackInit(Stack * s, int dim);	// alloca dinamicamente "dim" elementi
void StackRemove(Stack * s);		// dealloca gli elementi
void StackPush(Stack * s, Elem e);	// inserimento nello Stack
Elem StackPop(Stack * s);		// estrazione dallo Stack
int StackSize(Stack * s);		// ritorna il numero attuale di elementi


#endif
