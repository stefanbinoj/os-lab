#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int findLRU(int time[], int n)
{
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (time[i] < min)
        {
            pos = i;
            min = time[i];
        }
    }
    return pos;
}

void FIFO(int pages[], int framesCount, int n)
{
    int frames[framesCount];
    int front = 0, pageFault = 0;

    for (int i = 0; i < framesCount; i++)
    {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int hit = 0;
        for (int j = 0; j < framesCount; j++)
        {
            if (pages[i] == frames[j])
            {
                printf("Page hit found for %d \n", pages[i]);
                hit = 1;
                break;
            }
        }
        if (hit == 0)
        {
            printf("Page fault for %d \n", pages[i]);
            pageFault++;
            frames[front] = pages[i];
            front = (front + 1) % framesCount;
        }
        for (int z = 0; z < framesCount; z++)
        {
            printf("%d --> ", frames[z]);
        }
        printf("\n");
    }
    printf("Total noof page faults %d \n", pageFault);
}

void LRU(int pages[], int framesCount, int n)
{
    int frame[framesCount], time[framesCount];
    int count = 0, pageFaults = 0;

    for (int i = 0; i < framesCount; i++)
    {
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < framesCount; j++)
        {
            if (pages[i] == frame[j])
            {
                printf("Page hit found for %d\n", pages[i]);
                found = true;
                count++;
                time[j] = count;
                break;
            }
        }
        if (found == false)
        {
            printf("Page hit Nottt found for %d\n", pages[i]);
            int pos = -1;
            for (int z = 0; z < framesCount; z++)
            {
                if (frame[z] == -1)
                {
                    pos = z;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, framesCount);
            pageFaults++;
            frame[pos] = pages[i];
            count++;
            time[pos] = count;
        }
        for (int z = 0; z < framesCount; z++)
        {
            printf("%d -->", frame[z]);
        }
        printf("\n");
    }
    printf("Total noof page faults %d \n", pageFaults);
}

void LFU(int pages[], int framesCount, int n)
{
    int frame[framesCount], freq[framesCount];
    int pageFault = 0;

    for (int i = 0; i < framesCount; i++)
    {
        frame[i] = -1;
        freq[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < framesCount; j++)
        {
            if (pages[i] == frame[j])
            {
                printf("Page hit for %d\n", pages[i]);
                found = true;
                freq[j]++;
                break;
            }
        }
        if (found == false)
        {
            int pos = -1;
            printf("Page Not found for  for %d\n", pages[i]);

            for (int z = 0; z < framesCount; z++)
            {
                if (frame[z] == -1)
                {
                    pos = z;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(freq, framesCount);

            frame[pos] = pages[i];
            freq[pos] = 1;
            pageFault++;
        }
        printf("Step %d: ", i + 1);
        for (int j = 0; j < framesCount; ++j)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults (LFU): %d\n", pageFault);
}

void inputThings(int ch)
{
    int p, f;
    printf("Enter no.of pages \t");
    scanf("%d", &p);
    printf("Enter no.of frames \t");
    scanf("%d", &f);

    int pages[p];
    for (int i = 0; i < p; i++)
    {
        printf("Enter the page at %d the : \t", i + 1);
        scanf("%d", &pages[i]);
    }
    if (ch == 1)
        FIFO(pages, f, p);
    if (ch == 2)
        LRU(pages, f, p);
    if (ch == 3)
        LFU(pages, f, p);
}

int main()
{
    while (1)
    {
        printf("Enter the option : \n1.FIFO\n2.LRU\n3.LFU\n");
        int ch;
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            inputThings(ch);
            break;
        case 2:
            inputThings(ch);
            break;
        case 3:
            inputThings(ch);
            break;
        default:
            printf("Chose a valid options ");
        }
    }
    return 0;
}