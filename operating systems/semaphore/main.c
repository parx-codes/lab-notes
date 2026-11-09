#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>


typedef struct sh_mem{
    int counter;
    sem_t mutex;
}sh_mem;

int loops;


void worker(sh_mem* mem){
    for(int i=0; i<loops; i++){
        sem_wait(&mem->mutex);
        mem->counter++;
        sem_post(&mem->mutex);
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "usage: race <loops>\n");
        exit(1);
    }
    loops = atoi(argv[1]);

    sh_mem* mem = mmap(NULL, sizeof(sh_mem),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    sem_init(&mem->mutex,1,1);


    printf("initial value: %d\n",mem->counter);

    if(fork()==0){
        worker(mem);
        exit(0);
    }

    if(fork()==0){
        worker(mem);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    sem_destroy(&mem->mutex);
    munmap(mem,0);

    printf("final value: %d\n",mem->counter);
    return 0;

}
