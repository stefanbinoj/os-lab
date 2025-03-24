#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

    int frame[frames], lastUsed[frames];
    // Initialize frames to -1 and lastUsed to 0
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        lastUsed[i] = 0;
    }

    int faults = 0;
    // Process each page reference and update usage time
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        // Check if the page is already in frames
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                lastUsed[j] = i; // update last used time
                break;
            }
        }
        if (!found)
        {
            // Find the frame with the least recently used page
            int minIndex = 0, minTime = INT_MAX;
            for (int j = 0; j < frames; j++)
            {
                if (lastUsed[j] < minTime)
                {
                    minTime = lastUsed[j];
                    minIndex = j;
                }
            }
            frame[minIndex] = pages[i];
            lastUsed[minIndex] = i; // update the time for new page
            faults++;
        }
    }

    printf("Total page faults (LRU): %d\n", faults);
    return 0;
}
