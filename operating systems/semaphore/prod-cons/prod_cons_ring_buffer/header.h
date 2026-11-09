			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#include <semaphore.h>

#define N 5

/* TODO: definire il nome dell'oggetto di shared memory che tutti gli eseguibili 
(start, produttore, consumatore) useranno per ritrovare la stessa area condivisa. */ 

#define SHM_NAME "/ex_shm_sem"

typedef struct{
	/* TODO: inserire i campi della struttura condivisa tra i processi: 
	il vettore di buffer di N elementi gestito come coda circolare, con i relativi indici di testa e coda (vedi testo), 
	e i semafori necessari a sincronizzare produttori e consumatore, che devono essere accessibili da tutti i processi. */ 
	int elemento[N];
	int testa;
	int coda;
	sem_t spazio_disponibile;
	sem_t buffer_pieno;
	sem_t mutex;
} BufferCircolare;

void produci_elemento(BufferCircolare* buf);
void consuma_elementi(BufferCircolare* buf);

#endif
