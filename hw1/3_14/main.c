#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int n = 0;
    int k = 0;

    pid_t pid;

    do
    {
        printf("Please enter a number > 0 : ");
        scanf("%d", &k);
    } while (k <= 0);

    pid = fork();

    if (pid == 0)
    {
        printf("Child is working...\n");
        printf("%d ",k);
        while (k != 1)
        {
            if (k%2 == 0)
                k = k/2;
            else if (k%2 == 1)
                k = 3*(k)+1;
            printf("%d ",k);
        }
        printf("\nChild process is done.\n");
    }
    else
    {
        printf("Parents is waiting on child process...\n");
        wait(NULL);
        printf("Parent process is done.\n");
    }
    return 0;
}