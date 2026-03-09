#include <stdio.h>
#include <limits.h>

int main()
{
    int n,i,time=0,smallest;
    int at[10],bt[10],rt[10];
    int ct[10],tat[10],wt[10];
    int complete=0;
    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        rt[i]=bt[i];   // remaining time
    }

    rt[9]=INT_MAX;

    while(complete!=n)
    {
        smallest=9;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]<rt[smallest] && rt[i]>0)
            {
                smallest=i;
            }
        }

        rt[smallest]--;
        time++;

        if(rt[smallest]==0)
        {
            complete++;

            ct[smallest]=time;
            tat[smallest]=ct[smallest]-at[smallest];
            wt[smallest]=tat[smallest]-bt[smallest];

            avg_wt+=wt[smallest];
            avg_tat+=tat[smallest];
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avg_tat/n);

    return 0;
}
