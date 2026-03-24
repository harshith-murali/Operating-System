#include <stdio.h>

struct process
{
    int p_id;
    int arrival_time;
    int burst_time;
    int priority;
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
        printf("Enter AT, BT and Priority for process %d: ", i);
        scanf("%d%d%d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
    }

    // Sorting (Arrival time + Priority)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time ||
               (p[i].arrival_time == p[j].arrival_time &&
                p[i].priority > p[j].priority))
            {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
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

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        avg_tt += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].p_id,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].priority,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);
    }

    printf("\nAverage Turn Around Time : %.2f\n", avg_tt / n);
    printf("Average Waiting Time : %.2f\n", avg_wt / n);

    return 0;
}