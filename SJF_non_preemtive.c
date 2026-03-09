#include <stdio.h>

int main()
{
    int n,i,j;
    int at[10],bt[10],ct[10],tat[10],wt[10];
    int completed[10];
    int time=0,min_bt,idx;
    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        completed[i]=0;
    }

    int count=0;

    while(count<n)
    {
        min_bt=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && completed[i]==0)
            {
                if(bt[i]<min_bt)
                {
                    min_bt=bt[i];
                    idx=i;
                }
            }
        }

        if(idx!=-1)
        {
            time+=bt[idx];
            ct[idx]=time;

            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            completed[idx]=1;
            count++;

            avg_wt+=wt[idx];
            avg_tat+=tat[idx];
        }
        else
        {
            time++;
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avg_tat/n);

    return 0;
}
