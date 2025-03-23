#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int wt;  // Waiting Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
};

// Function to calculate Completion Time (CT)
void calculateCompletionTime(struct process p[], int n)
{
    p[0].ct = p[0].at + p[0].bt; // First process
    for (int i = 1; i < n; i++)
    {
        if (p[i].at > p[i - 1].ct) // If CPU is idle
        {
            p[i].ct = p[i].at + p[i].bt;
        }
        else
        {
            p[i].ct = p[i - 1].ct + p[i].bt;
        }
    }
}

// Function to calculate Waiting Time (WT)
void calculateWaitingTime(struct process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].wt = p[i].ct - p[i].at - p[i].bt;
        if (p[i].wt < 0)
            p[i].wt = 0; // To prevent negative waiting time
    }
}

// Function to calculate Turnaround Time (TAT)
void calculateTurnAroundTime(struct process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
    }
}

// Function to calculate and print average times
void calculateAVG(struct process p[], int n)
{
    calculateCompletionTime(p, n);
    calculateWaitingTime(p, n);
    calculateTurnAroundTime(p, n);

    float avg_tat = 0.0, avg_wt = 0.0;
    printf("\nPID | AT  | BT  | CT  | TAT | WT  \n");
    printf("----------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("%3d | %3d | %3d | %3d | %3d | %3d \n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
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

    // Sorting processes by Arrival Time (FCFS requirement)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    calculateAVG(p, n);

    return 0;
}
