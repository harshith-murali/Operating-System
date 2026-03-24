#include <stdio.h>

struct process
{
    int p_id;
    int arrival_time;
    int burst_time;
    int type; // 0 = System, 1 = User
    int completion_time;
    int turnaround_time;
    int waiting_time;
} p[100], sys[100], user[100];

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter PID, AT, BT, TYPE (0=System,1=User): ");
        scanf("%d%d%d%d", &p[i].p_id, &p[i].arrival_time, &p[i].burst_time, &p[i].type);
    }

    int sc = 0, uc = 0;

    // Step 1: Separate processes
    for (int i = 0; i < n; i++)
    {
        if (p[i].type == 0)
            sys[sc++] = p[i];
        else
            user[uc++] = p[i];
    }

    // Step 2: Sort both queues by Arrival Time (FCFS)
    for (int i = 0; i < sc - 1; i++)
    {
        for (int j = i + 1; j < sc; j++)
        {
            if (sys[i].arrival_time > sys[j].arrival_time)
            {
                struct process temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }

    for (int i = 0; i < uc - 1; i++)
    {
        for (int j = i + 1; j < uc; j++)
        {
            if (user[i].arrival_time > user[j].arrival_time)
            {
                struct process temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }

    int time = 0;

    // Step 3: Execute System Queue
    for (int i = 0; i < sc; i++)
    {
        if (time < sys[i].arrival_time)
            time = sys[i].arrival_time;

        time += sys[i].burst_time;

        sys[i].completion_time = time;
        sys[i].turnaround_time = sys[i].completion_time - sys[i].arrival_time;
        sys[i].waiting_time = sys[i].turnaround_time - sys[i].burst_time;
    }

    // Step 4: Execute User Queue
    for (int i = 0; i < uc; i++)
    {
        if (time < user[i].arrival_time)
            time = user[i].arrival_time;

        time += user[i].burst_time;

        user[i].completion_time = time;
        user[i].turnaround_time = user[i].completion_time - user[i].arrival_time;
        user[i].waiting_time = user[i].turnaround_time - user[i].burst_time;
    }

    double avg_tt = 0, avg_wt = 0;

    printf("\nProcess\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    // Print System Processes
    for (int i = 0; i < sc; i++)
    {
        avg_tt += sys[i].turnaround_time;
        avg_wt += sys[i].waiting_time;

        printf("P%d\t%d\t%d\tSystem\t%d\t%d\t%d\n",
               sys[i].p_id,
               sys[i].arrival_time,
               sys[i].burst_time,
               sys[i].completion_time,
               sys[i].turnaround_time,
               sys[i].waiting_time);
    }

    // Print User Processes
    for (int i = 0; i < uc; i++)
    {
        avg_tt += user[i].turnaround_time;
        avg_wt += user[i].waiting_time;

        printf("P%d\t%d\t%d\tUser\t%d\t%d\t%d\n",
               user[i].p_id,
               user[i].arrival_time,
               user[i].burst_time,
               user[i].completion_time,
               user[i].turnaround_time,
               user[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tt / n);
    printf("Average Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}