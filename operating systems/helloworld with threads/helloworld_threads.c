#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    long id;
    int n;
    int* shared;
} par;

void * hello(void * t){
    par* p = (par*) t;
    for (int i = 0; i < p->n; i++){
        printf("Ciao, sono il thread %ld, i=%d\n",p->id,i);
        (*p->shared)++;
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t th1, th2;

    int* shared = malloc(sizeof(int));
    *shared = 0;

    par* p1 = malloc(sizeof(par));
    p1->id =1; p1->n = 5; p1->shared = shared;
    pthread_create(&th1, NULL, hello, p1);
    par* p2 = malloc(sizeof(par));
    p2->id =2; p2->n = 7; p2->shared = shared;
    pthread_create(&th2, NULL, hello, p2);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    printf("Valore finale di shared: %d\n",*shared);
    return 0;
}
