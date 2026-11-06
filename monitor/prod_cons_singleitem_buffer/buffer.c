#include <pthread.h>
#include "buffer.h"

void produci(buffer* b,int m){

    pthread_mutex_lock(&b->mutex);
    while(b->buffer_pieno)          
        pthread_cond_wait(&b->vuoto,&b->mutex);
    
    b->msg = m;
    b->buffer_pieno = 1;
    b->buffer_vuoto = 0;
    pthread_cond_signal(&b->pieno);
    pthread_mutex_unlock(&b->mutex);

}


int consuma(buffer* b){

    int m;
    pthread_mutex_lock(&b->mutex);
    while(b->buffer_vuoto)          
        pthread_cond_wait(&b->pieno,&b->mutex);
    
    m = b->msg;
    b->buffer_pieno = 0;
    b->buffer_vuoto = 1;
    pthread_cond_signal(&b->vuoto);
    pthread_mutex_unlock(&b->mutex);
    return m;

}
