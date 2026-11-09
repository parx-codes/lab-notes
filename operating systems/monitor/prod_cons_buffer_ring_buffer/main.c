#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "buffer.h"

#define prod 6
#define cons 6

void* produttore(void* p){
    buffer* b = (buffer*) p;
    int m = rand()%100;
    produci(b,m);
    printf("[Produttore] Ho prodotto: %d\n",m);
    pthread_exit(NULL);
}

void* consumatore(void* p){
    buffer* b = (buffer*) p;
    int m = consuma(b);
    printf("[Consumatore] Ho consumato: %d\n",m);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[prod+cons];
    buffer* buf = (buffer*)malloc(sizeof(buffer));
    for(int i=0;i<N;i++){buf->msg[i] = 0;}
    buf->testa = 0;
    buf->coda = 0;
    pthread_mutex_init(&buf->mutex,NULL);
    pthread_cond_init(&buf->pieno,NULL);
    pthread_cond_init(&buf->vuoto,NULL);

    for(int i=0;i<prod+cons;i++){
        if(i<prod){
            pthread_create(&threads[i],NULL,produttore,buf);
        } else{
            pthread_create(&threads[i],NULL,consumatore,buf);
        }
    }

     for(int i=0;i<prod+cons;i++){
        pthread_join(threads[i],NULL);
     }

     pthread_mutex_destroy(&buf->mutex);
     pthread_cond_destroy(&buf->pieno);
     pthread_cond_destroy(&buf->vuoto);
     free(buf);
     return 0;

}