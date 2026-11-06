#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    printf("Ciao, sono %d\n",getpid());
    int fd = shm_open("/ex_1_shm",O_CREAT|O_EXCL|O_RDWR,0644);
    int* p;
    if(fd>0){
        ftruncate(fd,sizeof(int));
        p = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        *p = getpid();
    } else {
        int fd = shm_open("/ex_1_shm",O_RDWR,0);
        p = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    }

    printf("Contenuto della memoria: %d\n",*p);
    munmap(p,sizeof(int));
    close(fd);
    shm_unlink("/ex_1_shm");
}

