#include<stdio.h>

// Function to find the waiting time, turnaround time, and completion time for all processes using SJF (Preemptive)
void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[])
{
    int remaining[n]; // Array to store remaining burst time of processes
    int currentTime = 0; // Current time
    int completed = 0; // Counter for completed processes

    // Initialize remaining array with burst times
    for (int i = 0; i < n; i++)
        remaining[i] = bt[i];

    while (completed < n)
    {
        int shortest = -1; // Index of shortest remaining time process

        // Find process with shortest remaining burst time
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currentTime && remaining[i] > 0)
            {
                if (shortest == -1 || remaining[i] <= remaining[shortest])
                    shortest = i;
            }
        }

        // If no process found, move to next time
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        // Reduce remaining time of the process
        remaining[shortest]--;

        // If the process is completed
        if (remaining[shortest] == 0)
        {
            completed++;
            // Set completion time for the process
            ct[shortest] = currentTime + 1;
            // Calculate waiting time and turnaround time for the process
            wt[shortest] = ct[shortest] - bt[shortest] - at[shortest];
            tat[shortest] = ct[shortest] - at[shortest];
        }

        // Move to the next time
        currentTime++;
    }

    // Print the table
     printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i],ct[i]);
    }
}

void main()
{
    // Number of processes
    int n;
    float atat,awt;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Process id's
    int processes[n];
    // Burst time of all processes
    int burst_time[n];
    // Arrival time of all processes
    int arrival_time[n];

    printf("Enter Process Number:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processes[i]);
    }
    printf("Enter Arrival Time:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arrival_time[i]);
    }
    printf("Enter Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &burst_time[i]);
    }

    // Arrays to store waiting time, turnaround time, and completion time
    int wt[n], tat[n], ct[n];

    printf("\nSJF (Preemptive) Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct);
    for(int i=0;i<n;i++){
        atat=atat+tat[i];
        awt=awt+wt[i];
    }
    printf("Average Turn Around Time = %f",atat/n);
    printf("Average Waiting Time = %f",awt/n);
}