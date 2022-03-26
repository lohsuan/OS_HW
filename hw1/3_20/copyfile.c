#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {
	int fd[2];
	pid_t childId;

	char readBuff[BUFFER_SIZE];

	if(pipe(fd) == -1) {
		fprintf(stderr, "Pipe failed");
		exit(1);
	}

	if(argc < 3) {
	    printf("need at least 2 parameters");
	    exit(1);
	}

	int fileOpen = open(argv[1], 0);
    int targetFile = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0666);

    if(fileOpen == -1) {
        perror("Source file can't be opened");
        exit(1);
    }
    if(targetFile == -1) {
        perror("Destination file can't be opened");
        exit(1);
    }

	childId = fork();

	/* child process (consumer) */
	if(childId == 0) { 
	    /* close the unused end of the pipe */
		close(fd[WRITE_END]);

		 while (read(fd[READ_END], readBuff, sizeof(readBuff)) > 0) {
		    // write read string to the targetFile
            write(targetFile, readBuff, strlen(readBuff)-1);
        }

        close(fd[READ_END]);
        close(targetFile);

	    // read(fd[READ_END], readBuff, sizeof(readBuff));
	    // printf("read :\n %s\n", readBuff);

	    // write(targetFile, readBuff, strlen(readBuff) - 1);

		// close(fd[READ_END]);

	} 
	/* parent process (producer) */
	else { 
	    /* close the unused end of the pipe */
	    close(fd[READ_END]);

		// read string from fileOpen to readBuff
	    while(read(fileOpen, readBuff, sizeof(readBuff)) > 0)  {
			// pass readBuff to pipe
			write(fd[WRITE_END], readBuff, sizeof(readBuff));
			memset(readBuff, 0, BUFFER_SIZE);
		}

		close(fd[WRITE_END]);
		close(fileOpen);
		wait(NULL);
	}
}