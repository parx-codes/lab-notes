#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    printf("Sono il processo padre con PID %d\n", getpid());

    int p = fork();
    
    if(p==0){
        printf("Sono il processo figlio con PID %d\n", getpid());
        exit(1);
    }

    printf("Ciao!\n");

    return 0;
}