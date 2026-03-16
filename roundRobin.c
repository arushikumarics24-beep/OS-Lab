#include <stdio.h>

int main()
{
    int n, tq;
    int at[20], bt[20], rt[20];
    int ct[20], tat[20], wt[20];
    int time = 0, remain;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0;i<n;i++)
    {
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d",&at[i]);

        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    remain = n;

    while(remain != 0)
    {
        int executed = 0;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                executed = 1;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;
                    remain--;
                }
            }
        }

        if(executed == 0)
            time++;   // move time forward if no process arrived
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
