#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct process
{
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int wt;  // Waiting Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int completed;
};

void calculateCompletionTime(struct process p[], int n)
{
    int current_time = 0, completed = 0;

    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
    }

    while (completed < n)
    {
        int idx = -1;
        int min_bt = INT_MAX;

        // finding smalled bt
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed && p[i].at <= current_time && p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1)
        {
            current_time++;
        }
        else
        {
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
    printf("\nPID | AT  | BT  | CT  | TAT | WT  \n");
    printf("------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("%3d | %3d | %3d | %3d | %3d | %3d \n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
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
    }

    calculateAVG(p, n);

    return 0;
}