			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#include <semaphore.h>

#define SIZE 4

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define NPROD 3
#define NCONS 3

#define SHM_NAME "/ex_autoval1"

typedef struct{
	int chiave;
	int valore;
} ElemBuffer;

typedef struct{
	ElemBuffer elementi[SIZE];
	int stati[SIZE];
	// TODO inserire i semafori necessari per la gestione della sincronizzazione e del buffer
	sem_t spazio_disponibile;
	sem_t messaggio_disponibile_1;
	sem_t messaggio_disponibile_2;
	sem_t messaggio_disponibile_3;
	sem_t mutex_p;
	sem_t mutex_c;
} Buffer;

void produci(Buffer* buf, int chiave);
void consuma(Buffer* buf, int chiave);

#endif
