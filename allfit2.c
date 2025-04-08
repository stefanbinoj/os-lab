#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void collectThings(int);
void firstFit(int, int, int[], int[]);
void bestFit(int, int, int[], int[]);
void worstFit(int, int, int[], int[]);
void display(int sequence[], int process[], int p)
{
    printf("\nTable:\n");
    printf("Process Number | Process Size | Block Number\n");
    for (int i = 0; i < p; i++)
    {
        printf("%14d | %12d | ", i + 1, process[i]);
        if (sequence[i] != -1)
            printf("%12d\n", sequence[i] + 1);
        else
            printf(" Not Allocated\n");
    }
}

int main()
{
    while (1)
    {
        printf("Menu : \n1.First\n2.Besst\n3.Worst\n");
        int ch;
        printf("ENter the algorithm to perform : \t");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            collectThings(ch);
            break;
        case 2:
            collectThings(ch);
            break;
        case 3:
            collectThings(ch);
            break;

        default:
            printf("Invalid choice");
            break;
        }
    }
}

void collectThings(int ch)
{
    int b, p;
    printf("Entert no of blocks : \t");
    scanf("%d", &b);
    printf("Entert no of process : \t");
    scanf("%d", &p);

    int block[b];
    int process[p];

    for (int i = 0; i < b; i++)
    {
        printf("Enter memory at %dth n:\t", i + 1);
        scanf("%d", &block[i]);
    }
    for (int i = 0; i < p; i++)
    {
        printf("Enter process size at %dth n:\t", i + 1);
        scanf("%d", &process[i]);
    }

    if (ch == 1)
        firstFit(b, p, block, process);
    if (ch == 2)
        bestFit(b, p, block, process);
    if (ch == 3)
        worstFit(b, p, block, process);
}

void firstFit(int b, int p, int block[], int process[])
{
    int sequence[p];
    for (int i = 0; i < p; i++)
    {
        sequence[i] = -1; // Initialize to unallocated
    }
    for (int i = 0; i < p; i++)
    {
        int size = process[i];
        bool allocated = false;
        for (int j = 0; j < b; j++)
        {
            if (block[j] >= size)
            {
                allocated = true;
                block[j] -= size;
                sequence[i] = j;
                break;
            }
        }
        if (allocated == false)
        {
            printf("No space for %d \n", size);
        }
    }
    display(sequence, process, p);
}

void bestFit(int b, int p, int block[], int process[])
{
    int sequence[p];
    for (int i = 0; i < p; i++)
    {
        sequence[i] = -1; // Initialize to unallocated
    }
    for (int i = 0; i < p; i++)
    {
        int size = process[i];
        int index = -1;
        int bestSize = 999;
        for (int j = 0; j < b; j++)
        {
            if (block[j] >= size && block[j] < bestSize)
            {
                bestSize = block[j];
                index = j;
            }
        }
        if (index == -1)
        {
            printf("Couldnt allocate for size %d \n", size);
        }
        else
        {
            block[index] -= size;
            sequence[i] = index;
        }
    }
    display(sequence, process, p);
}

void worstFit(int b, int p, int block[], int process[])
{
    int sequence[p];
    for (int i = 0; i < p; i++)
    {
        sequence[i] = -1; // Initialize to unallocated
    }
    for (int i = 0; i < p; i++)
    {
        int size = process[i];
        int smallest = -1;
        int index = -1;
        for (int j = 0; j < b; j++)
        {
            if (block[j] >= size && block[j] > smallest)
            {
                smallest = block[j];
                index = j;
            }
        }
        if (index == -1)
        {
            printf("COudlnt find for : %d size", size);
        }
        else
        {
            block[index] -= size;
            sequence[i] = index;
        }
    }
    display(sequence, process, p);
}