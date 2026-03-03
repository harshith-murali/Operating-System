#include <stdio.h>

struct process
{
    int p_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} p[100];

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].p_id = i;
        printf("Enter Arrival Time and Burst Time for process %d: ", i);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);

        if (i == 0)
        {
            p[i].completion_time = p[i].arrival_time + p[i].burst_time;
        }
        else
        {
            if (p[i - 1].completion_time < p[i].arrival_time)
                p[i].completion_time = p[i].arrival_time + p[i].burst_time;
            else
                p[i].completion_time = p[i - 1].completion_time + p[i].burst_time;
        }

        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }

    double avg_tt = 0, avg_wt = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        avg_tt += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].p_id,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);
    }

    avg_tt /= n;
    avg_wt /= n;

    printf("\nAverage Turn Around Time : %.2f\n", avg_tt);
    printf("Average Waiting Time : %.2f\n", avg_wt);

    return 0;
}