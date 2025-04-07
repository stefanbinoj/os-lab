#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t p = fork();
    if (p > 0)
    {
        printf("\nparent");
        printf("\nParent : %d", getpid());
        printf("\nChild : %d", p);
    }
    else if (p == 0)
    {
        printf("\n child");
        printf("\nChild : %d", getpid());
        printf("\nParent : %d", getppid());
    }

    else
    {
        printf("\nfail");
        perror("Fork failed");
        return 1;
    }
    return 0;
}