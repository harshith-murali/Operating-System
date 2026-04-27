#include <stdio.h>

struct process
{
    int id, period, burst, remaining;
} p[100];

int main()
{
    int n, time, hyper = 20;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Burst Time and Period for P%d: ", i);
        scanf("%d%d", &p[i].burst, &p[i].period);

        p[i].id = i;
        p[i].remaining = p[i].burst;
    }

    printf("\nTime\tProcess\n");

    for (time = 0; time < hyper; time++)
    {
        int idx = -1, min_period = 9999;

        for (int i = 0; i < n; i++)
        {
            if (time % p[i].period == 0)
                p[i].remaining = p[i].burst;

            if (p[i].remaining > 0 && p[i].period < min_period)
            {
                min_period = p[i].period;
                idx = i;
            }
        }

        if (idx != -1)
        {
            printf("%d\tP%d\n", time, idx);
            p[idx].remaining--;
        }
        else
            printf("%d\tIdle\n", time);
    }

    return 0;
}