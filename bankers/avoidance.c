#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, r;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &r);

    int allocation[n][r], maximum[n][r], need[n][r], available[r];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix (each row for a process):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process P%d: ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("\nEnter Maximum Matrix (each row for a process):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process P%d: ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < r; j++)
    {
        scanf("%d", &available[j]);
    }

    // Calculate Need Matrix = Maximum - Allocation
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Banker's Algorithm: Finding a Safe Sequence
    bool finish[n];
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }

    int safeSeq[n]; // To store safe sequence
    int count = 0;

    // Work vector holds available resources at each step
    int work[r];
    for (int j = 0; j < r; j++)
    {
        work[j] = available[j];
    }

    while (count < n)
    {
        bool found = false;
        // Try to find an unfinished process whose needs can be met by current work
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
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
                    // If process can be allocated resources, simulate its execution
                    for (int j = 0; j < r; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        // If no process was found in this loop, system is not in a safe state.
        if (!found)
        {
            break;
        }
    }

    // Print result
    if (count == n)
    {
        printf("\nSystem is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in a safe state. Deadlock may occur.\n");
    }

    return 0;
}
