#include <stdio.h>
#include <unistd.h>

int main(){

    int pid, ppid;
    pid = getpid();

    printf("Sono il processo con PID %d\n", pid);

    ppid = getppid();

    printf("Il mio genitore è il processo con PID %d\n", ppid);
}