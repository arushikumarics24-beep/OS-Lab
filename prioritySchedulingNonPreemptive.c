#include <stdio.h>

int main()
{
    int n, i, j;
    int at[10], bt[10], pr[10];
    int wt[10], tat[10], ct[10], completed[10];
    int time = 0, min_pr, idx;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time, Burst Time and Priority for P%d: ",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
        completed[i] = 0;
    }

    int count = 0;

    while(count < n)
    {
        min_pr = 9999;
        idx = -1;

        for(i=0;i<n;i++)
        {
            if(at[i] <= time && completed[i]==0)
            {
                if(pr[i] < min_pr)
                {
                    min_pr = pr[i];
                    idx = i;
                }
            }
        }

        if(idx != -1)
        {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            completed[idx] = 1;
            count++;

            avg_wt += wt[idx];
            avg_tat += tat[idx];
        }
        else
        {
            time++;
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f",avg_tat/n);

    return 0;
}
