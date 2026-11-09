#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int* counter;
int loops;

void worker(){
    for(int i=0; i<loops; i++){
        (*counter)++;
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "usage: race <loops>\n");
        exit(1);
    }
    loops = atoi(argv[1]);

    counter = mmap(NULL, sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);


    printf("initial value: %d\n",*counter);

    if(fork()==0){
        worker();
        exit(0);
    }

    if(fork()==0){
        worker();
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    munmap(counter,0);

    printf("final value: %d\n",*counter);
    return 0;

}
