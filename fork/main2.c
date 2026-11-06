#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    printf("Sono il processo padre, pid: %d\n", getpid());

    int var = 0;

    printf("Valore iniziale variabile: %d\n", var);

    int p = fork();

    if(p == 0){
        var++;
        printf("Sono il processo figlio, pid: %d , var: %d\n", getpid(),var);
        exit(1);
    }

    printf("Valore finale variabile: %d\n", var);
    
    return 0;
}