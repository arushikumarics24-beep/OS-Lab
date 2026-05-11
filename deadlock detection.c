/* Deadlock Detection Algorithm in C */

#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    printf("Enter number of processes -- ");
    scanf("%d", &n);

    printf("Enter number of resources -- ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];
    int finish[n], safeSeq[n];

    /* Input Allocation and Request Matrix */
    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for P%d\n", i);

        printf("Enter allocation -- ");
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter request -- ");
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    }

    /* Input Available Resources */
    printf("\nEnter Available Resources -- ");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    /* Initially all processes are unfinished */
    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                /* Check if request <= available */
                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    /* Process can complete */
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;

                    printf("P%d is visited(", i);
                    for(k = 0; k < m; k++)
                        printf("%d ", avail[k]);
                    printf(")\n");
                }
            }
        }

        if(found == 0)
            break;
    }

    /* Check deadlock */
    if(count == n)
    {
        printf("\nSYSTEM IS NOT IN DEADLOCK\n");
        printf("Safe Sequence is -- ");
        for(i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
    }
    else
    {
        printf("\nSYSTEM IS IN DEADLOCK\n");
        printf("Deadlocked Processes are -- ");

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
                printf("P%d ", i);
        }
    }

    return 0;
}
