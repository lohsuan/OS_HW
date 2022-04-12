#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_POINTS 1000000
#define NUMBER_OF_THREADS 2

void *runner(void *param);

/* Points in the circle (Global variable) */
int circle_count = 0;

int main(int argc, const char *argv[]) {
    int points_per_thread = NUMBER_OF_POINTS / NUMBER_OF_THREADS;
    int i;
    double Pi;

    pthread_t workers[NUMBER_OF_THREADS];

    /* seed the random number generator */
    srandom((unsigned)time(NULL));
    clock_t begin = clock();

    for (i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_create(&workers[i], 0, runner, &points_per_thread);

    for (i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(workers[i], NULL);

    /* caculate Pi */
    Pi = 4.0 * circle_count / NUMBER_OF_POINTS;

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("NUMBER OF POINTS = %d\n", NUMBER_OF_POINTS);
    printf("Pi = %f\n", Pi);
    printf("time = %f\n", time_spent);
    
    return 0;
}

/* Generates a double precision random number */
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

void *runner(void *param) {
    int POINTS;
    POINTS = *((int *)param);
    int i;
    int hit_count = 0;
    double x, y;

    for (i = 0; i < POINTS; i++) {
        /* generate random numbers between -1.0 and +1.0 (exclusive) */
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;

        /* check (x, y) point is in the circle */
        if (sqrt(x * x + y * y) < 1.0)
            ++hit_count;
    }

    circle_count += hit_count;

    pthread_exit(0);
}