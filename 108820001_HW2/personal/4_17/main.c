#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_POINTS 1000000

void *runner(void *param);

/* Points in the circle (Global variable) */
int circle_count = 0;

int main(int argc, const char *argv[]) {
    int numOfPoints = NUMBER_OF_POINTS;
    pthread_t workers[1];

    srandom((unsigned)time(NULL));
    pthread_create(&workers[0], 0, runner, &numOfPoints);
    pthread_join(workers[0], NULL);

    double Pi = 4.0 * circle_count / NUMBER_OF_POINTS;

    printf("number of points = %d\n", NUMBER_OF_POINTS);
    printf("number of points in circle = %d\n", circle_count);
    printf("Pi = %f\n", Pi);
    
    return 0;
}

/* Generates a double precision random number */
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

void *runner(void *param) {
    int POINTS = *((int *)param);
    double x, y;
    for (int i = 0; i < POINTS; i++) {
        /* generate random numbers between -1.0 and +1.0 (exclusive) */
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;
        if (sqrt(x * x + y * y) < 1.0)
            ++circle_count;
    }
    pthread_exit(0);
}