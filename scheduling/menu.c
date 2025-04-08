#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>

struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int remainingTime;
    int priority;
    int completed;
};

void FCFS();
void SJF();
void SRTF();
void RR();
void Priority();
void PriorityPreem();

void calculateEveryting(struct process p[], int n)
{
    p[0].ct = p[0].at + p[0].bt;
    for (int i = 1; i < n; i++)
    {
        if (p[i].at > p[i - 1].ct)
        {
            p[i].ct = p[i].at + p[i].bt;
        }
        else
        {
            p[i].ct = p[i - 1].ct + p[i].bt;
        }
    }
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void calculateForSJF(struct process p[], int n)
{
    int completed = 0, current = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
    }
    while (completed != n)
    {
        int index = -1;
        int greatestBT = 99;
        for (int i = 0; i < n; i++)
        {
            if (p[i].completed == 0 && p[i].at <= current && p[i].bt < greatestBT)
            {
                index = i;
                greatestBT = p[i].bt;
            }
        }
        if (index == -1)
            current++;
        else
        {
            completed++;
            current += p[index].bt;
            p[index].ct = current;
            p[index].completed = 1;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
        }
    }
}

void calculateForSRTF(struct process p[], int n)
{
    int completed = 0, current = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
        p[i].remainingTime = p[i].bt;
    }
    while (completed != n)
    {
        int index = -1;
        int greatestRemainingTime = 99;
        for (int i = 0; i < n; i++)
        {
            if (p[i].completed == 0 && p[i].at <= current && p[i].remainingTime < greatestRemainingTime && p[i].remainingTime > 0)
            {
                index = i;
                greatestRemainingTime = p[i].remainingTime;
            }
        }
        if (index == -1)
            current++;
        else
        {
            current++;
            p[index].remainingTime--;
            if (p[index].remainingTime == 0)
            {
                p[index].ct = current;
                p[index].completed = 1;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                completed++;
            }
        }
    }
}

void calculateForRR(struct process p[], int n)
{
    int quantum;
    printf("Enter time quantum : \t");
    scanf("%d", &quantum);
    int completed = 0, current = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
        p[i].remainingTime = p[i].bt;
    }
    while (completed != n)
    {
        int executed = 0;
        for (int i = 0; i < n; i++)
        {
            if (p[i].completed == 0 && p[i].at <= current && p[i].remainingTime > 0)
            {
                executed = 1;
                if (p[i].remainingTime > quantum)
                {
                    p[i].remainingTime -= quantum;
                    current += quantum;
                }
                else
                {
                    current += p[i].remainingTime;
                    p[i].completed = 1;
                    p[i].remainingTime = 0;
                    p[i].ct = current;
                    completed++;
                }
            }
        }
        if (executed == 0)
            current++;
    }
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void calculateForPriority(struct process p[], int n)
{
    int completed = 0, current = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
    }

    while (completed != n)
    {
        int index = -1;
        int lowestPriority = 99;
        for (int i = 0; i < n; i++)
        {
            if (p[i].completed == 0 && p[i].at <= current && p[i].priority < lowestPriority)
            {
                index = i;
                lowestPriority = p[i].priority;
            }
        }
        if (index == -1)
            current++;
        else
        {
            current += p[index].bt;
            p[index].completed = 1;
            completed++;
            p[index].ct = current;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
        }
    }
}

void calculateForPriorityPreem(struct process p[], int n)
{
    int completed = 0, current = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].completed = 0;
        p[i].remainingTime = p[i].bt;
    }
    while (completed != n)
    {
        int lowesrPriority = 99;
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current && p[i].completed == 0 && p[i].priority <= lowesrPriority && p[i].remainingTime > 0)
            {
                index = i;
                lowesrPriority = p[i].priority;
            }
        }
        if (index == -1)
            current++;
        else
        {
            current++;
            p[index].remainingTime--;
            if (p[index].remainingTime == 0)
            {
                completed++;
                p[index].ct = current;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
            }
        }
    }
}

void caclulateAVG(struct process p[], int n, int alogrithm)
{
    if (alogrithm == 1)
        calculateEveryting(p, n);
    else if (alogrithm == 2)
        calculateForSJF(p, n);
    else if (alogrithm == 3)
        calculateForSRTF(p, n);
    else if (alogrithm == 4)
        calculateForRR(p, n);
    else if (alogrithm == 5)
        calculateForPriority(p, n);
    else if (alogrithm == 6)
        calculateForPriorityPreem(p, n);
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
    while (1)
    {
        printf("\nMenu : \n1.FCFS\n2.SJf\n3.SRTF\n4.Round Robin\n5.Priority\n6.Priority-Preemptive\n7.Exit");
        int ch;
        printf("ENter the algorithm to perform : \t");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            SRTF();
            break;
        case 4:
            RR();
            break;
        case 5:
            Priority();
            break;
        case 6:
            PriorityPreem();
            break;
        case 7:
            printf("Exiting\n");
            exit(0);
        default:
            printf("Invalid choice");
            break;
        }
    }
    return 0;
}

void FCFS()
{
    printf("Enter number of process : \t");
    int n;
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        int at, bt;
        printf("ENter the AT : \t");
        scanf("%d", &at);
        printf("ENter the BT : \t");
        scanf("%d", &bt);
        p[i].at = at;
        p[i].bt = bt;
        p[i].pid = i + 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (p[j].at < p[i].at)
            {
                struct process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    int algorithm = 1;
    caclulateAVG(p, n, algorithm);
}

void SJF()
{
    printf("Enter number of process : \t");
    int n;
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        int at, bt;
        printf("ENter the AT : \t");
        scanf("%d", &at);
        printf("ENter the BT : \t");
        scanf("%d", &bt);
        p[i].at = at;
        p[i].bt = bt;
        p[i].pid = i + 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].at < p[i].at)
            {
                struct process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    int algorithm = 2;
    caclulateAVG(p, n, algorithm);
}

void SRTF()
{
    printf("Enter number of process : \t");
    int n;
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        int at, bt;
        printf("ENter the AT : \t");
        scanf("%d", &at);
        printf("ENter the BT : \t");
        scanf("%d", &bt);
        p[i].at = at;
        p[i].bt = bt;
        p[i].pid = i + 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].at < p[i].at)
            {
                struct process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    int algorithm = 3;
    caclulateAVG(p, n, algorithm);
}

void RR()
{
    printf("Enter number of process : \t");
    int n;
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        int at, bt;
        printf("ENter the AT : \t");
        scanf("%d", &at);
        printf("ENter the BT : \t");
        scanf("%d", &bt);
        p[i].at = at;
        p[i].bt = bt;
        p[i].pid = i + 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].at < p[i].at)
            {
                struct process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    int algorithm = 4;
    caclulateAVG(p, n, algorithm);
}

void Priority()
{
    printf("Enter number of process : \t");
    int n;
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        int at, bt, priority;
        printf("ENter the AT : \t");
        scanf("%d", &at);
        printf("ENter the BT : \t");
        scanf("%d", &bt);
        printf("ENter the prioritu : \t");
        scanf("%d", &priority);
        p[i].at = at;
        p[i].bt = bt;
        p[i].pid = i + 1;
        p[i].priority = priority;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].at < p[i].at)
            {
                struct process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    int algorithm = 5;
    caclulateAVG(p, n, algorithm);
}

void PriorityPreem()
{
    printf("Enter number of process : \t");
    int n;
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        int at, bt, priority;
        printf("ENter the AT : \t");
        scanf("%d", &at);
        printf("ENter the BT : \t");
        scanf("%d", &bt);
        printf("ENter the prioritu : \t");
        scanf("%d", &priority);
        p[i].at = at;
        p[i].bt = bt;
        p[i].pid = i + 1;
        p[i].priority = priority;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].at < p[i].at)
            {
                struct process tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    int algorithm = 6;
    caclulateAVG(p, n, algorithm);
}
