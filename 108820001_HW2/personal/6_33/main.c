#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_POINTS 1000000
#define NUMBER_OF_THREADS 10

/* Points in the circle (Global variable) */
int circle_count = 0;
pthread_mutex_t mutex;

void *runner(void *param);


int main(int argc, const char *argv[]) {
    int points_per_thread = NUMBER_OF_POINTS / NUMBER_OF_THREADS;
    pthread_attr_t attr; /* set of thread attributes */
    pthread_t workers[NUMBER_OF_THREADS];

    srandom((unsigned)time(NULL));
    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_create(&workers[i], 0, runner, &points_per_thread);

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(workers[i], NULL);

    double Pi = 4.0 * circle_count / NUMBER_OF_POINTS;

    printf("number of points = %d\n", NUMBER_OF_POINTS);
    printf("number of points in circle = %d\n", circle_count);
    printf("Pi = %f\n", Pi);

    pthread_mutex_destroy(&mutex);
    
    return 0;
}

/* Generates a double precision random number */
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

void *runner(void *param) {
    int POINTS = *((int *)param);
    double x, y;
    
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < POINTS; i++) {
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;
        if (sqrt(x * x + y * y) < 1.0)
            ++circle_count;
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}