#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct memory
{
    int size;
    struct memory *next;
    int num;
};
struct memory *head = NULL;

struct process
{
    int size;
    int allocated;
    struct process *next;
    int num;
};
struct process *h2 = NULL;
void collectThings();
void freeMem()
{
    struct memory *temp = head;
    while (temp != NULL)
    {
        printf("%d -- > ", temp->size);
        temp = temp->next;
    }
}
void firstFit()
{
    printf("Frist Bit \n");
    printf("Process No. \tProcess Size. \tBlock No.\n");
    struct process *temp2 = h2;

    while (temp2 != NULL)
    {
        if (temp2->allocated == 1)
        {
            temp2 = temp2->next;
            continue;
        }
        struct memory *temp1 = head;
        while (temp1 != NULL)
        {
            if (temp1->size >= temp2->size)
            {
                printf("%d \t %d \t %d \n", temp2->num, temp2->size, temp1->num);
                temp1->size -= temp2->size;
                temp2->allocated = 1;
                break;
            }
            temp1 = temp1->next;
        }
        if (temp2->allocated == 0)
        {
            printf("Could not allocate memory for process of size %d\n", temp2->size);
        }
        temp2 = temp2->next;
    }
}

void bestFit()
{
    printf("Best Bit \n");
    printf("Process No. \tProcess Size. \tBlock No.\n");
    struct process *temp2 = h2;
    while (temp2 != NULL)
    {
        if (temp2->allocated == 0)
        {
            struct memory *temp1 = head;
            struct memory *best = NULL;
            int smallest = 999;
            while (temp1 != NULL)
            {
                if (temp1->size >= temp2->size)
                {
                    if (temp1->size < smallest)
                    {
                        best = temp1;
                        smallest = temp1->size;
                    }
                }
                temp1 = temp1->next;
            }
            if (best)
            {
                printf("%d \t %d \t %d \n", temp2->num, temp2->size, best->num);
                temp2->allocated = 1;
                best->size -= temp2->size;
            }
            else
            {
                printf("Couldn't find memeory for %d , \n", temp2->num);
            }
        }
        temp2 = temp2->next;
    }
}

void worstFit()
{
    printf("Worst Bit \n");
    printf("Process No. \tProcess Size. \tBlock No.\n");
    struct process *temp2 = h2;
    while (temp2 != NULL)
    {
        if (temp2->allocated == 1)
        {
            temp2 = temp2->next;
            continue;
        }
        struct memory *temp1 = head;
        struct memory *heighest = NULL;
        int largest = 0;
        while (temp1 != NULL)
        {
            if (temp1->size >= temp2->size)
            {
                if (temp1->size > largest)
                {
                    largest = temp1->size;
                    heighest = temp1;
                }
            }
            temp1 = temp1->next;
        }
        if (heighest != NULL)
        {
            printf("%d \t %d \t %d \n", temp2->num, temp2->size, heighest->num);
            heighest->size -= temp2->size;
            temp2->allocated = 1;
            temp2 = temp2->next;
        }
        else
        {
            printf("Couldn't find memeory for %d , \n", temp2->num);
            temp2 = temp2->next;
        }
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
            collectThings();
            firstFit();
            freeMem();
            break;
        case 2:
            collectThings();
            bestFit();
            freeMem();
            break;
        case 3:
            collectThings();
            worstFit();
            freeMem();
            break;

        default:
            printf("Invalid choice");
            break;
        }
    }
}

void collectThings()
{
    head = NULL;
    h2 = NULL;

    int n;
    printf("ENter no of memory blocks : \t");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter teh size of %d memory : \t", i + 1);
        struct memory *m1 = (struct memory *)malloc(sizeof(struct memory));
        scanf("%d", &m1->size);
        m1->next = NULL;
        m1->num = i + 1;
        if (head == NULL)
        {
            head = m1;
        }
        else
        {
            struct memory *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = m1;
        }
    }

    int n2;
    printf("ENter no of process : \t");
    scanf("%d", &n2);

    for (int i = 0; i < n2; i++)
    {
        struct process *p1 = (struct process *)malloc(sizeof(struct process));
        p1->allocated = 0;
        p1->next = NULL;
        p1->num = i + 1;
        printf("ENter th process size for %dth process : \t", i + 1);
        scanf("%d", &p1->size);
        if (h2 == NULL)
        {
            h2 = p1;
        }
        else
        {
            struct process *temp = h2;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = p1;
        }
    }
}