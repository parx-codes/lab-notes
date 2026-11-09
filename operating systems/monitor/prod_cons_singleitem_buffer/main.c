#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "buffer.h"

#define NUM_PROD 6
#define NUM_CONS 6

void* produttore(void* p){

    buffer* b = (buffer*) p;
    int m = rand()%100;
    produci(b,m);
        printf("Sono il PRODUTTORE, valore prodotto: %d\n",m);
    pthread_exit(NULL);

}

void* consumatore(void* p){

    buffer* b = (buffer*) p;
    int m = consuma(b);
    printf("Sono il CONSUMATORE, valore consumato: %d\n",m);
    pthread_exit(NULL);

}

int main(){

    pthread_t threads[NUM_CONS+NUM_PROD];

    buffer* buf = (buffer*)malloc(sizeof(buffer));
    buf->msg = 0;
    buf->buffer_pieno = 0;
    buf->buffer_vuoto = 1;
    pthread_mutex_init(&buf->mutex,NULL);
    pthread_cond_init(&buf->pieno,NULL);
    pthread_cond_init(&buf->vuoto,NULL);


    for(int i=0;i<NUM_CONS;i++){
        pthread_create(&threads[i],NULL,consumatore,buf);
    }

    for(int i=NUM_PROD;i<NUM_PROD+NUM_CONS;i++){
        pthread_create(&threads[i],NULL,produttore,buf);
    }

    for(int i = 0; i<NUM_PROD+NUM_CONS;i++){
        pthread_join(threads[i],NULL);
    }

    pthread_mutex_destroy(&buf->mutex);
    pthread_cond_destroy(&buf->pieno);
    pthread_cond_destroy(&buf->vuoto);
    free(buf);
    return 0;

}