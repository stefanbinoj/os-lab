#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    int p, r;
    printf("Enter no.of process : \t");
    scanf("%d", &p);
    printf("Enter no.of resource types : \t");
    scanf("%d", &r);

    int allocated[p][r], max[p][r], need[p][r], resource[r];
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            printf("Enter the resources need for process-%d with resource type - %d \t:", i + 1, j + 1);
            scanf("%d", &allocated[i][j]);
        }
    }
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            printf("Enter the total resources needed for process-%d with resource type - %d \t:", i + 1, j + 1);
            scanf("%d", &max[i][j]);
        }
    }
    for (int j = 0; j < r; j++)
    {
        printf("Enter the total resources resource type - %d \t:", j + 1);
        scanf("%d", &resource[j]);
    }

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    printf("Printing ....\n");
    printf("Allocation : \n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            printf("%d  ", allocated[i][j]);
        }
        printf("\n");
    }
    printf("Max : \n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            printf("%d  ", max[i][j]);
        }
        printf("\n");
    }
    printf("Need : \n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }

    int count = 0;
    int sequence[p];
    bool finished[p];
    for (int i = 0; i < p; i++)
    {
        finished[i] = false;
    }

    int work[r];
    for (int j = 0; j < r; j++)
    {
        work[j] = resource[j];
    }

    while (count < p)
    {
        int process = -1;
        for (int i = 0; i < p; i++)
        {
            if (finished[i] == true)
            {
                continue;
            }
            bool canAllocate = true;
            for (int j = 0; j < r; j++)
            {
                if (need[i][j] > work[j])
                {
                    canAllocate = false;
                    break;
                }
            }
            if (canAllocate)
            {
                process = i;
                sequence[count] = i;
                finished[i] = true;
                count++;
                printf("Process %d completed \n", i + 1);
                for (int j = 0; j < r; j++)
                {
                    work[j] += allocated[i][j];
                }
                printf("The work is  \t");
                for (int j = 0; j < r; j++)
                {
                    printf("%d ", work[j]);
                }
            }
        }
        if (process == -1)
        {
            break;
        }
    }
    if (count != p)
    {
        printf("Couldnt find safe sequence exiting : \n");
    }
    else
    {
        printf("seq is : \n");
        for (int i = 0; i < p; i++)
        {
            printf("%d -> ", sequence[i]);
        }
    }

    return 0;
}