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

    int frame[frames], freq[frames], lastUsed[frames];
    // Initialize frames to -1, frequency to 0, and lastUsed to 0
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        freq[i] = 0;
        lastUsed[i] = 0;
    }

    int faults = 0;
    // Process each page reference
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        // Check if page is already in a frame
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                freq[j]++;       // Increase frequency count
                lastUsed[j] = i; // Update last used time
                break;
            }
        }
        if (!found)
        {
            int replaceIndex = -1;
            // First, check if there's an empty frame
            for (int j = 0; j < frames; j++)
            {
                if (frame[j] == -1)
                {
                    replaceIndex = j;
                    break;
                }
            }
            // If all frames are full, select the least frequently used page.
            if (replaceIndex == -1)
            {
                int minFreq = INT_MAX, minTime = INT_MAX;
                for (int j = 0; j < frames; j++)
                {
                    if (freq[j] < minFreq)
                    {
                        minFreq = freq[j];
                        minTime = lastUsed[j];
                        replaceIndex = j;
                    }
                    else if (freq[j] == minFreq)
                    {
                        // Tie-breaker: choose the one least recently used
                        if (lastUsed[j] < minTime)
                        {
                            minTime = lastUsed[j];
                            replaceIndex = j;
                        }
                    }
                }
            }
            // Replace the chosen frame
            frame[replaceIndex] = pages[i];
            freq[replaceIndex] = 1;     // Reset frequency for the new page
            lastUsed[replaceIndex] = i; // Update last used time
            faults++;
        }
    }

    printf("Total page faults (LFU): %d\n", faults);
    return 0;
}
