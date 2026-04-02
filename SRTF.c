#include <stdio.h>

struct process
{
    int p_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
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
        printf("Enter AT and BT for process %d: ", i);
        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    int completed = 0, time = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_rt = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0)
            {
                if (p[i].remaining_time < min_rt)
                {
                    min_rt = p[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            p[idx].remaining_time--;
            time++;

            if (p[idx].remaining_time == 0)
            {
                p[idx].completion_time = time;
                completed++;
            }
        }
        else
        {
            time++;
        }
    }

    double avg_tt = 0, avg_wt = 0;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

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

    printf("\nAverage Turn Around Time : %.2f\n", avg_tt / n);
    printf("Average Waiting Time : %.2f\n", avg_wt / n);

    return 0;
}