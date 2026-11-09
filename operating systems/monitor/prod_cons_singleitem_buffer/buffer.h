#ifndef __BUFFER_H
#define __BUFFER_H

#include <pthread.h>

typedef struct{
    int msg;
    int buffer_pieno;
    int buffer_vuoto;
    pthread_mutex_t mutex;
    pthread_cond_t pieno;
    pthread_cond_t vuoto;
}buffer;

void produci(buffer* b,int m);
int consuma(buffer* b);


#endif