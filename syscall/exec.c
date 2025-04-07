#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("The parent is : %d\n", getpid());

    pid_t p = fork();
    if (p < 0)
    {
        perror("failed\n");
        return 1;
    }
    if (p == 0)
    {
        printf("chlid %d executinggg\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Parent %d completed child %d", getpid(), p);
    }
    return 0;
}