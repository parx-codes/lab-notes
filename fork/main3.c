#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    printf("Sono il processo padre con PID : %d\n", getpid());

    int p = fork();
    if(p == 0){
        printf("Sono il processo figlio con PID: %d\n", getpid());
        sleep(200);
    }

    return 0;
}