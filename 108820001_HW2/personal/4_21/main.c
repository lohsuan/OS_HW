#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;

int fib[30]; /* this data is shared by the thread(s) */
int in = 0;
void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[]) {

    pthread_attr_t attr; /* set of thread attributes */

    if (argc != 2) {
        fprintf(stderr, "Please follow the usage: fibthread < integer between 1 to 30 >\n");
        return -1;
    }

    int count = atoi(argv[1]);
    if (count < 1 || count >30) {
        fprintf(stderr, "Please input number between 1 to 30.\n");
        return -1;
    }

    pthread_attr_init(&attr); /* set the default attributes of the thread */
    pthread_mutex_init(&mutex, NULL); /* Mutex Lock */

    // create each thread to compute fibonacci
    for (long i = 1; i <= count; i++) {
        pthread_t tid; /* the thread identifier */ 
        pthread_create(&tid, &attr, runner, (void *)i); /* create the thread */
        pthread_join(tid, NULL); /* wait for the thread to exit */
    }

    // print resulting array
    for (int i = 0; i < in; i++) {
        printf("%d ", fib[i]);
    }

    printf("\n");

    pthread_mutex_destroy(&mutex);
}

int fibonacci(int x) {
    if (x == 1) {
        return 1;
    } else if(x == 0){
        return 0;
    }
    return fibonacci(x - 1) + fibonacci(x - 2);
}

void *runner(void *param) {
    // mutex lock is to ensure fib array's concurrency
    // since child thread is concurrent and independent
    pthread_mutex_lock(&mutex);

    fib[in++] = fibonacci((long)param);

    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}