/*PROCESSO CONSUMATORE*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


int main(){
	// TODO: Definizione variabili locali

	printf("[Consumatore] Sono il processo consumatore con pid %d\n", getpid());

	// TODO: Aprire la shared memory creata dal master (dopo la exec va ritrovata tramite il suo nome)
	int fd = shm_open(SHM_NAME,O_RDWR,0600);
	if (fd < 0) { perror("SHM_OPEN Consumatore (avviare tramite ./start)"); exit(1); }

	// TODO: Mappare la struttura condivisa nel proprio spazio di indirizzamento
	BufferCircolare* buf = mmap(NULL,sizeof(BufferCircolare),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	if (buf == MAP_FAILED) { perror("MMAP Consumatore"); exit(1); }
	// TODO: Chiudere il descrittore, non piu' necessario dopo il mapping
	close(fd);

	// Effettua 2 accessi
	printf("[Consumatore] --- Primo Accesso ---\n");
	// TODO: Consumare gli elementi del buffer
	consuma_elementi(buf);

	sleep(1); // Attendi 1 secondo

	printf("[Consumatore] --- Secondo Accesso ---\n");
	// TODO: Consumare gli elementi del buffer
	consuma_elementi(buf);

	// TODO: Rilasciare il mapping della shared memory
	munmap(buf,sizeof(BufferCircolare));

	return 0;
}
