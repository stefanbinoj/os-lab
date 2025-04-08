#include <stdio.h>
#include <stdlib.h>

// Structure for a process
struct process
{
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time (used in Round Robin)
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Function to calculate Completion, Turnaround, and Waiting Times using Round Robin Scheduling
void calculateTimes(struct process p[], int n, int tq)
{
    int current_time = 0;
    int completed = 0;
    int i;

    // Initialize remaining time for each process
    for (i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
    }

    // Run until all processes are completed
    while (completed != n)
    {
        int executed = 0; // Flag to check if any process was executed in this round

        // Traverse each process in the list
        for (i = 0; i < n; i++)
        {
            // Only consider processes that have arrived and are not yet finished
            if (p[i].rt > 0 && p[i].at <= current_time)
            {
                executed = 1; // A process is available for execution

                if (p[i].rt > tq)
                {
                    // If remaining time is more than time quantum, execute for tq
                    p[i].rt -= tq;
                    current_time += tq;
                }
                else
                {
                    // Process can finish execution within this time slice
                    current_time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = current_time; // Completion time is updated when process finishes
                    completed++;
                }
            }
        }
        // If no process was executed in the loop (i.e., no process has arrived yet), increment time
        if (!executed)
            current_time++;
    }

    // Calculate Turnaround Time and Waiting Time for each process
    for (i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// Function to print the process table and average times
void calculateAVG(struct process p[], int n, int tq)
{
    calculateTimes(p, n, tq);

    float avg_tat = 0.0, avg_wt = 0.0;
    printf("\nPID | AT  | BT  | CT  | TAT | WT\n");
    printf("------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("%3d | %3d | %3d | %3d | %3d | %3d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
}

int main()
{
    int n, tq;
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

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    calculateAVG(p, n, tq);

    return 0;
}
