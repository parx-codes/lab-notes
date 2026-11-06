#include <pthread.h>
#include "buffer.h"

void produci(buffer* b, int m){
    pthread_mutex_lock(&b->mutex);
    
    while(b->contatore == N){
        pthread_cond_wait(&b->vuoto,&b->mutex);
    }

    b->msg[b->coda] = m;
    b->coda = (b->coda+1)%N;
    b->contatore++;

    pthread_cond_signal(&b->pieno);
    pthread_mutex_unlock(&b->mutex);
}

int consuma(buffer* b){
    pthread_mutex_lock(&b->mutex);

    int m;
    while(b->contatore == 0){
        pthread_cond_wait(&b->pieno,&b->mutex);
    }

    m = b->msg[b->testa];
    b->testa = (b->testa+1)%N;
    b->contatore--;

    pthread_cond_signal(&b->vuoto);
    pthread_mutex_unlock(&b->mutex);
    return m;
}