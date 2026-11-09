/* PROCESSO PRODUTTORE */

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


int main(){
	// TODO: Definizione variabili locali

	printf("[PRODUTTORE] <%d> Avviato\n", getpid());

	// TODO: Aprire la shared memory creata dal master (dopo la exec va ritrovata tramite il suo nome)
	int fd = shm_open(SHM_NAME,O_RDWR,0600);
	if (fd < 0) { perror("SHM_OPEN Produttore (avviare tramite ./start)"); exit(1); }

	// TODO: Mappare la struttura condivisa nel proprio spazio di indirizzamento
	BufferCircolare* buf = mmap(NULL,sizeof(BufferCircolare),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	if (buf == MAP_FAILED) { perror("MMAP Produttore"); exit(1); }
	// TODO: Chiudere il descrittore, non piu' necessario dopo il mapping
	close(fd);

	// Seed per rand() in produci_elemento
	srand(getpid());

	// TODO: Produrre 1 elemento
	produci_elemento(buf);
		
	// TODO: Rilasciare il mapping della shared memory
	munmap(buf,sizeof(BufferCircolare));

	return 0;
}
