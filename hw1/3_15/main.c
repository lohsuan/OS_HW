#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv){

    const int SIZE = 4096;
    const char *name ="OS";
    const int BUFFER_SIZE = 1024;
    int shm_fd;
    void *ptr;

    /* create shared memory area. */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* Truncate the file */
    ftruncate(shm_fd,SIZE);

    /* Map the file into memory */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    /* now we create process*/
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr,"Failed to fork a child.\n");
        shm_unlink(name);
        exit(1);
    } else if (pid == 0) { /* child process */

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(char)*BUFFER_SIZE);
        char *buffer_p = &buffer[0];

        if (argc == 1 || argc > 2){
            fprintf(stderr,"Pass invaild args!\n");
            shm_unlink(name);
            return 1;
        }

        int num = atoi(argv[1]);
        buffer_p += sprintf(buffer_p, "%d,", num); 
        while (num != 1){
            if (num % 2 == 0) {
                num = num / 2;
                if (num == 1) {
                    buffer_p += sprintf(buffer_p, "%d\n", num);
                } 
                else {
                    buffer_p += sprintf(buffer_p, "%d,", num);
                } 
            }
            else {
                num = 3*num + 1;
                buffer_p += sprintf(buffer_p, "%d,", num);
            }
        }
        sprintf(ptr, "%s", buffer);
        printf("Child: write data to shared memory done.\n");
    } else { /*Parent process*/
        wait(NULL);
        printf("Parent: start read from shared memory.\n");

        shm_fd = shm_open(name, O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("%s", (char *)ptr);
        shm_unlink(name);
    }
    return 0;
}