#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

typedef struct{
    int buffer;
    sem_t spazio_disponibile;
    sem_t messaggio_disponibile;
}buf_t;

void Produttore(buf_t* p){
    
    sem_wait(&p->spazio_disponibile);
    int mess = rand()%10;
    p->buffer = mess;
    printf("Produttore: ho prodotto il messaggio %d\n",mess);
    sem_post(&p->messaggio_disponibile);

}

void Consumatore(buf_t* p){
    
    sem_wait(&p->messaggio_disponibile);
    int mess = p->buffer;
    printf("Consumatore: ho consumato il messaggio %d\n",mess);
    sem_post(&p->spazio_disponibile);

}

int main(){

    srand(time(NULL));
    shm_unlink("/ex_prod_cons");

    int fd = shm_open("/ex_prod_cons",O_CREAT|O_EXCL|O_RDWR,0600);
    if(fd<0) {perror("shm_open"); return -1;}

    ftruncate(fd,sizeof(buf_t));
    
    buf_t* p = mmap(NULL,sizeof(buf_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);

    sem_init(&p->spazio_disponibile,1,1);
    sem_init(&p->messaggio_disponibile,1,0);

    if(fork() == 0){
        Produttore(p);
        exit(0);
    }

    if(fork() == 0){
        Consumatore(p);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    sem_destroy(&p->spazio_disponibile);
    sem_destroy(&p->messaggio_disponibile);
    munmap(p,sizeof(buf_t));
    shm_unlink("/ex_prod_cons");
    return 0;

}