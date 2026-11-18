#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

#include "header.h"


int main(){
	pid_t pid_ex,pid;
	int st,i;
	Buffer* buf;

	/* La memoria condivisa può essere un mapping ANONIMO, senza nome. */
	shm_unlink(SHM_NAME);

	int fd = shm_open(SHM_NAME,O_CREAT|O_EXCL|O_RDWR,0600);
	if(fd<0){perror("shm error"); exit(-1);}

	if(ftruncate(fd,sizeof(Buffer))<0){perror("ftruncate error"); exit(-1);}

	//TODO mappare il buffer
	buf = mmap(NULL,sizeof(Buffer),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(buf==MAP_FAILED){perror("map error"); exit(-1);}

	printf("[MASTER] - Buffer condiviso inizializzato\n");

	// TODO: Inizializzare i semafori
	sem_init(&buf->spazio_disponibile,1,4);
	sem_init(&buf->messaggio_disponibile_1,1,0);
	sem_init(&buf->messaggio_disponibile_2,1,0);
	sem_init(&buf->messaggio_disponibile_3,1,0);

	sem_init(&buf->mutex_c,1,1);
	sem_init(&buf->mutex_p,1,1);

	// TODO: Inizializzare il buffer
	for(int i=0;i<SIZE;i++){
		buf->stati[i]=LIBERO;
	}

	srand(time(NULL));
	int val;

	for(i = 0; i < NCONS+NPROD; i++){
		// TODO: Creare i processi figli (produttori e consumatori)
		if(i<3){
			if(fork() == 0){
				produci(buf,i+1);
				exit(0);	
			}
		}else{
			if(fork() == 0){
				consuma(buf,(i%3)+1);
				exit(0);
			}
		}

		val =  (1+rand()%3);
		sleep(val);

	}

	for(i = 0; i < NCONS+NPROD ; i++){
		// TODO: Attendere il completamento dei processi figli
		pid_ex = wait(NULL);
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n",pid_ex);
	}

	// TODO: RIMOZIONE RISORSE
	sem_destroy(&buf->spazio_disponibile);
	sem_destroy(&buf->messaggio_disponibile_1);
	sem_destroy(&buf->messaggio_disponibile_2);
	sem_destroy(&buf->messaggio_disponibile_3);

	sem_destroy(&buf->mutex_c);
	sem_destroy(&buf->mutex_p);

	munmap(buf,sizeof(Buffer));
	shm_unlink(SHM_NAME);

	return 0;
}
