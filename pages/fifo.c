#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, frames;
    printf("Enter number of page references: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames];
    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    int front = 0, faults = 0;
    // Process each page reference
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        // Check if page already exists in frames
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        // If not found, replace page using FIFO logic
        if (!found)
        {
            frame[front] = pages[i];
            front = (front + 1) % frames; // circular increment
            faults++;
        }
    }

    printf("Total page faults (FIFO): %d\n", faults);
    return 0;
}
