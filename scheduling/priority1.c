#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process
{
    int pid;       // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int prio;      // Priority (lower number => higher priority)
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
    int completed; // Flag to indicate if process has been executed
};

void calculateCompletionTime(struct process p[], int n)
{
    int current_time = 0, completed = 0;

    // Initialize all processes as not completed
    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
    }

    while (completed < n)
    {
        int idx = -1;
        int highest_priority = INT_MAX; // Lower values mean higher priority

        // Find process with highest priority among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed && p[i].at <= current_time && p[i].prio < highest_priority)
            {
                highest_priority = p[i].prio;
                idx = i;
            }
        }

        // If no process has arrived yet, increment current time
        if (idx == -1)
        {
            current_time++;
        }
        else
        {
            // Process is executed to completion
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
        }
    }
}

void calculateAVG(struct process p[], int n)
{
    calculateCompletionTime(p, n);

    float avg_tat = 0.0, avg_wt = 0.0;
    printf("\nPID | AT  | BT  | PRIO | CT  | TAT | WT\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("%3d | %3d | %3d | %4d | %3d | %3d | %3d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].prio, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details for Process %d:\n", i + 1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (lower value means higher priority): ");
        scanf("%d", &p[i].prio);
    }

    calculateAVG(p, n);

    return 0;
}
