#include "stack.h"

#include <stdlib.h>

void StackInit(Stack * s, int dim) {

	// TODO: Allocare il vettore, inizializzarlo e inizializzare le variabili di sincronizzazione
	s->dati = malloc(dim * sizeof(Elem));
	s->dim = dim;
	s->cont = 0;

	for(int i=0;i<dim;i++){
		s->dati[i] = rand()%11;
	}

	pthread_mutex_init(&s->mutex,NULL);
	pthread_cond_init(&s->pieno,NULL);
	pthread_cond_init(&s->vuoto,NULL);

}


void StackRemove(Stack * s) {

	// TODO: Distruggere le variabili di sincronizzazione e deallocare il vettore
	pthread_mutex_destroy(&s->mutex);
	pthread_cond_destroy(&s->pieno);
	pthread_cond_destroy(&s->vuoto);

	free(s->dati);
}

void StackPush(Stack * s, Elem e) {

	// TODO: Entrare nella sezione critica
	pthread_mutex_lock(&s->mutex);

	// TODO: Effettuare l' inserimento dell' elemento in cima allo stack tenendo conto della sincronizzazione
	while(s->cont == s->dim){
		pthread_cond_wait(&s->vuoto,&s->mutex);
	}

	s->dati[s->cont] = e;
	s->cont++;

	// TODO: Uscire dalla sezione critica
	pthread_cond_signal(&s->pieno);
	pthread_mutex_unlock(&s->mutex);
}


Elem StackPop(Stack * s) {

	Elem elemento;

	// TODO: Entrare nella sezione critica
	pthread_mutex_lock(&s->mutex);

	// TODO: Effettuare il prelievo dell' elemento dalla cima dello stack tenendo conto della sincronizzazione
	while(s->cont == 0){
		pthread_cond_wait(&s->pieno,&s->mutex);
	}

	s->cont--;
	elemento = s->dati[s->cont];
	

	// TODO: Uscire dalla sezione critica
	pthread_cond_signal(&s->vuoto);
	pthread_mutex_unlock(&s->mutex);
	return elemento;
}

int StackSize(Stack * s) {
	int size;

	// TODO: Entrare nella sezione critica
	pthread_mutex_lock(&s->mutex);

	// TODO: Leggere il valore della testa
	size = s->cont;

	// TODO: Uscire dalla sezione critica
	pthread_mutex_unlock(&s->mutex);
	return size;
}
