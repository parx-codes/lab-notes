#ifndef __BUFFER_H
#define __BUFFER_H

#include <pthread.h>
#define N 3

typedef struct{
    int msg[N];
    int contatore;
    int testa;
    int coda;
    pthread_mutex_t mutex;
    pthread_cond_t pieno;
    pthread_cond_t vuoto;
}buffer;

void produci(buffer* b, int m);
int consuma(buffer* b);

#endif