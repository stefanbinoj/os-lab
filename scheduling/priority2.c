#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process
{
    int pid;       // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int prio;      // Priority (lower value means higher priority)
    int rt;        // Remaining Time (for preemption)
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
    int completed; // Flag to indicate completion
};

// Function to calculate completion time using preemptive priority scheduling
void calculateCompletionTimePreemptive(struct process p[], int n)
{
    int current_time = 0, completed = 0;

    // Initialize remaining times and completed flag for each process
    for (int i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    while (completed < n)
    {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Check all processes to find the one with highest priority (lowest prio value)
        // among those that have arrived and are not yet finished.
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed && p[i].at <= current_time && p[i].rt > 0)
            {
                if (p[i].prio < highest_priority)
                {
                    highest_priority = p[i].prio;
                    idx = i;
                }
                // Tie-breaking: if priority is the same, choose the one with earlier arrival time.
                else if (p[i].prio == highest_priority)
                {
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // No process is ready to execute; increment time
            current_time++;
        }
        else
        {
            // Execute the selected process for 1 time unit
            p[idx].rt--;
            current_time++;

            // If the process is finished, update its completion time and mark it complete.
            if (p[idx].rt == 0)
            {
                p[idx].ct = current_time;
                p[idx].completed = 1;
                completed++;
            }
        }
    }
}

// Function to calculate Turnaround Time and Waiting Time for each process
void calculateWaitingTurnaroundPreemptive(struct process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// Function to compute average times and print process details
void calculateAVGPreemptive(struct process p[], int n)
{
    calculateCompletionTimePreemptive(p, n);
    calculateWaitingTurnaroundPreemptive(p, n);

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

    calculateAVGPreemptive(p, n);

    return 0;
}
