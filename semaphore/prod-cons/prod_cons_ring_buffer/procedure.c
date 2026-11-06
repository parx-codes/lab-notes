			/*----IMPLEMENTAZIONE DELLE PROCEDURE----*/
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

//Calcolo statistiche
double media(int* v){
	int i;
	double somma;
	somma = 0.0;
	for(i = 0; i < N;i++){
		somma += v[i];
	}
	return somma/N;
}

// Deviazione standard campionaria
double dev_std(int* v,double media){
	int i;
	double somma,scarto;
	somma = 0.0;
	for(i = 0; i < N;i++){
		scarto = v[i] - media;
		somma += scarto*scarto;
	}
	return sqrt(somma/(N-1));
}

// Consumo
void consuma_elementi(BufferCircolare* buf){
	// TODO: Definizione variabili locali
	float m;
	int val[N];
	// Sincronizzazione Consumatore
	printf("[Consumatore %d] In attesa che il buffer sia pieno...\n", getpid());
	for (int j = 0; j < N; j++) {
		// TODO: sospendere il consumatore finche' il vettore di buffer non è pieno
		sem_wait(&buf->buffer_pieno);
	}
	printf("[Consumatore %d] Buffer pieno. Inizio consumo.\n", getpid());
	
	// TODO: Una volta sbloccato, prelevare tutti gli elementi accedendo al buffer in mutua esclusione e consumare tutti gli elementi del buffer
	// --- INIZIO SEZIONE CRITICA ---
	sem_wait(&buf->mutex);
	for (int j = 0; j < N; j++) {
		// TODO: Gestione coda circolare e stampa del valore letto
		val[j] = buf->elemento[buf->coda];
		buf->coda = (buf->coda + 1) % N;
		printf("[Consumatore %d] letto %d da pos. %d\n", getpid(), val[j] , buf->coda );

		// TODO: Per ogni elemento consumato, segnala uno spazio libero
		sem_post(&buf->spazio_disponibile);
	}
	// --- FINE SEZIONE CRITICA ---
	// TODO: Segnalare la fine della sezione critica
	sem_post(&buf->mutex);

	m = media(val);
	printf("[Consumatore %d] media %f, deviazione standard %f\n",getpid(),m,dev_std(val,m));
}

//Produzione
void produci_elemento(BufferCircolare* buf){
	int val;
	val = (1+rand()%10); // valore casuale tra 1 e 10

	// TODO: Aspettare uno spazio disponibile per produrre
	sem_wait(&buf->spazio_disponibile);

	// TODO: Accesso in mutua esclusione al buffer circolare
	sem_wait(&buf->mutex);

	// --- INIZIO SEZIONE CRITICA ---
	// TODO: Produrre l'elemento e aggiornare la coda circolare
	buf->elemento[buf->testa] = val;
	buf->testa = (buf->testa + 1) % N;
	printf("[Produttore %d] ho prodotto %d in posizione %d\n", getpid(), val , buf->testa);
	// --- FINE SEZIONE CRITICA ---
	// TODO: Segnalare la fine della sezione critica
	sem_post(&buf->mutex);
	// TODO: Segnalare al consumatore la presenza del nuovo elemento
	sem_post(&buf->buffer_pieno);
}
