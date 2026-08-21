#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], waiting[n], turnaround[n];

     for (int i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    waiting[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting[i] = waiting[i - 1] + burst[i - 1];
    }

    for (int i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst[i], waiting[i], turnaround[i]);
        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}