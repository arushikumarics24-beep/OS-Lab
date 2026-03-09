#include <stdio.h>
#include <limits.h>

int main()
{
    int n,i,time=0,smallest,count=0;
    int at[10],bt[10],pr[10],rt[10];
    int wt[10],tat[10],finish;
    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time, Burst Time and Priority for P%d: ",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
        rt[i]=bt[i];
    }

    pr[9]=INT_MAX;

    while(count!=n)
    {
        smallest=9;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && pr[i]<pr[smallest] && rt[i]>0)
            {
                smallest=i;
            }
        }

        rt[smallest]--;
        time++;

        if(rt[smallest]==0)
        {
            count++;
            finish=time;

            tat[smallest]=finish-at[smallest];
            wt[smallest]=tat[smallest]-bt[smallest];

            avg_wt+=wt[smallest];
            avg_tat+=tat[smallest];
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
