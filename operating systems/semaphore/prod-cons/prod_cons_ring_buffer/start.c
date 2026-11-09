#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>

#include "header.h"

#define N_PROD 10
#define N_CONS 1
#define TOT_PROC (N_PROD + N_CONS)

int main(){
	// TODO: Definizione variabili locali

	// TODO: Creare la shared memory nominata rimuovendo prima un eventuale oggetto rimasto da un'esecuzione precedente
	shm_unlink(SHM_NAME);
	int fd = shm_open(SHM_NAME,O_CREAT|O_EXCL|O_RDWR,0600);
	if (fd < 0) { perror("SHM_OPEN Master"); exit(1); }

	// TODO: Impostare la dimensione della shared memory
	if (ftruncate(fd,sizeof(BufferCircolare)) < 0) { perror("FTRUNCATE Master"); exit(1); }

	// TODO: Mappare la struttura condivisa nel proprio spazio di indirizzamento
	BufferCircolare* buf = mmap(NULL,sizeof(BufferCircolare),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (buf == MAP_FAILED) { perror("MMAP Master"); exit(1); }

	// TODO: Chiudere il descrittore, non piu' necessario dopo il mapping
	close(fd);

	// TODO: Inizializzare il buffer circolare
	// TODO: Inizializzare i semafori, condivisi tra processi, con valori coerenti con lo stato iniziale del buffer
	buf->testa = 0;
	buf->coda = 0;
	sem_init(&buf->mutex,1,1);
	sem_init(&buf->spazio_disponibile,1,N);
	sem_init(&buf->buffer_pieno,1,0);

	srand(time(NULL)); // Per lo sleep casuale

	for(int i = 0; i < TOT_PROC; i++){
		// TODO: Creare i processi figli
		int pid = fork();

		//Gestione errore fork
		if (pid < 0) { perror("Fork fallita"); exit(1); }
		if(i < N_PROD){
			execl("./produttore","produttore",NULL);
			perror("EXECL Produttore.");
			exit(1);
		} else {
			execl("./consumatore","consumatore",NULL);
			perror("EXECL Consumatore.");
			exit(1);
		}
		sleep( (rand() % 3) + 1 );
		
	}
	// TODO: Attendere la terminazione dei processi figli
	for(int i = 0; i < TOT_PROC ; i++){
		int status;
		int pid_terminato = wait(&status);
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n", pid_terminato);
	}

	printf("[MASTER] Tutti i processi terminati. Pulizia.\n");
	// TODO: Distruggere i semafori
	sem_destroy(&buf->spazio_disponibile);
	sem_destroy(&buf->buffer_pieno);
	sem_destroy(&buf->mutex);

	// TODO: Rilasciare il mapping e rimuovere la shared memory
	munmap(buf, sizeof(BufferCircolare));
	shm_unlink(SHM_NAME);

	return 0;
}
