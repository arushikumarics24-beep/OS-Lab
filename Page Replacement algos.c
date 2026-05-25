#include <stdio.h>

int main()
{
    int frames, n, i, j, k;

    printf("Enter the number of Frames: ");
    scanf("%d", &frames);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    int ref[n];

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &ref[i]);
    }

    // ---------------- FIFO ----------------
    int fifo[frames];
    int front = 0, fifoFaults = 0;

    for(i = 0; i < frames; i++)
        fifo[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(fifo[j] == ref[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            fifo[front] = ref[i];
            front = (front + 1) % frames;
            fifoFaults++;
        }

        printf("PF No. %d: ", i + 1);

        for(j = 0; j < frames; j++)
        {
            if(fifo[j] != -1)
                printf("%d ", fifo[j]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("FIFO Page Faults: %d\n", fifoFaults);

    // ---------------- LRU ----------------
    int lru[frames], recent[frames];
    int lruFaults = 0;

    for(i = 0; i < frames; i++)
    {
        lru[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(lru[j] == ref[i])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if(!found)
        {
            int pos = 0, min = 9999;

            for(j = 0; j < frames; j++)
            {
                if(lru[j] == -1)
                {
                    pos = j;
                    break;
                }

                if(recent[j] < min)
                {
                    min = recent[j];
                    pos = j;
                }
            }

            lru[pos] = ref[i];
            recent[pos] = i;
            lruFaults++;
        }

        printf("PF No. %d: ", i + 1);

        for(j = 0; j < frames; j++)
        {
            if(lru[j] != -1)
                printf("%d ", lru[j]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("LRU Page Faults: %d\n", lruFaults);

    // ---------------- Optimal ----------------
    int opt[frames];
    int optFaults = 0;

    for(i = 0; i < frames; i++)
        opt[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(opt[j] == ref[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = -1;

            // Empty frame
            for(j = 0; j < frames; j++)
            {
                if(opt[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            // Replace optimal page
            if(pos == -1)
            {
                int farthest = -1;

                for(j = 0; j < frames; j++)
                {
                    int nextUse = 9999;

                    for(k = i + 1; k < n; k++)
                    {
                        if(opt[j] == ref[k])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest)
                    {
                        farthest = nextUse;
                        pos = j;
                    }
                }
            }

            opt[pos] = ref[i];
            optFaults++;
        }

        printf("PF No. %d: ", i + 1);

        for(j = 0; j < frames; j++)
        {
            if(opt[j] != -1)
                printf("%d ", opt[j]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("Optimal Page Faults: %d\n", optFaults);

    return 0;
}
