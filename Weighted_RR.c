#include <stdio.h>

struct process
{
    int id, burst, remaining, weight;
} p[100];

int main()
{
    int n, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Burst Time and Weight for P%d: ", i);
        scanf("%d%d", &p[i].burst, &p[i].weight);

        p[i].id = i;
        p[i].remaining = p[i].burst;
    }

    printf("\nTime\tProcess\n");

    while (1)
    {
        int done = 1;

        for (int i = 0; i < n; i++)
        {
            int slice = p[i].weight;

            while (slice-- && p[i].remaining > 0)
            {
                printf("%d\tP%d\n", time++, i);
                p[i].remaining--;
                done = 0;
            }
        }

        if (done)
            break;
    }

    return 0;
}