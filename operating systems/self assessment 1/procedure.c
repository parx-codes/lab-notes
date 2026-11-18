			/*----IMPLEMENTAZIONE DELLE PROCEDURE----*/


#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"


// Consumo 
// TODO: nella funzione controllare la chiave per consumare il messaggio giusto
void consuma(Buffer* buf, int chiave){
	printf("[Consumatore %d] iniziato con chiave %d \n",getpid(), chiave);
	int value;
	int index;
	int val_sleep; 

	for(int i=0; i<3; i++){
		// TODO completare consumazione

		switch(chiave){
		case 1: sem_wait(&buf->messaggio_disponibile_1); break;
		case 2: sem_wait(&buf->messaggio_disponibile_2); break;
		case 3: sem_wait(&buf->messaggio_disponibile_3); break;
		default: break;
		}

		sem_wait(&buf->mutex_c);
		index = 0;
		while(index<SIZE && buf->stati[index]!=OCCUPATO && buf->elementi[index].chiave==chiave){
			index++;
		}

		buf->stati[index] = IN_USO;
		sem_post(&buf->mutex_c);

		printf("[Consumatore %d] consumo elemento in posizione %d\n",getpid(), index);
		// TODO
		
		value = buf->elementi[index].valore;
		buf->stati[index]=LIBERO;
		
		val_sleep =  (1+rand()%3);
		sleep(val_sleep);
		// TODO
		
		sem_post(&buf->spazio_disponibile);

		printf("[Consumatore %d] valore letto: %d\n",getpid(), value);
	}
}

//Produzione
// TODO: nella funzione controllare la chiave per segnalare la produzione del messaggio giusto
void produci(Buffer* buf, int chiave){

	printf("[Produttore %d] iniziato con chiave %d\n",getpid(), chiave);
	int val_sleep;
	int value;
	int index;

	for(int i=0; i<3; i++){
		// TODO COMPLETARE PRODUZIONE
		sem_wait(&buf->spazio_disponibile);

		printf("[Produttore %d] entrato con chiave %d \n",getpid(), chiave);

		sem_wait(&buf->mutex_p);
		index = 0;

		while(index<SIZE && buf->stati[index]!=LIBERO){
			index++;
		}

		buf->stati[index]=IN_USO;
		sem_post(&buf->mutex_p);

		value = rand() % 100;
		buf->elementi[index].valore = value;
		buf->elementi[index].chiave = chiave;
		buf->stati[index]=OCCUPATO;

		val_sleep =  (1+rand()%3);
		sleep(val_sleep);
		// TODO

		switch(chiave){
		case 1: sem_post(&buf->messaggio_disponibile_1); break;
		case 2: sem_post(&buf->messaggio_disponibile_2); break;
		case 3: sem_post(&buf->messaggio_disponibile_3); break;
		default: break;
		}
		
		printf("[Produttore %d] ho prodotto %d, con chiave %d, in posizione %d\n",getpid(),value, chiave, index);
	}
}
