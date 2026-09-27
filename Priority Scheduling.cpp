#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], rem[20], pr[20], ct[20], wt[20], tat[20], pid[20];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter arrival, burst, priority (lower=higher) for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
        rem[i] = bt[i];
    }

    int time = 0, completed = 0;
    int gp[1000], g = 0; 

    while (completed < n) {
        int idx = -1, bestPr = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem[i] > 0 && pr[i] < bestPr) {
                bestPr = pr[i];
                idx = i;
            }
        }

        if (idx == -1) {
            gp[g++] = 0;
            time++;
            continue;
        }

        gp[g++] = pid[idx];
        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    cout << "\nGantt Chart:\n";
    int start = 0;
    for (int i = 1; i <= g; i++) {
        if (i == g || gp[i] != gp[i-1]) {
            if (gp[i-1] == 0)
                cout << "Idle(" << start << "-" << i << ") ";
            else
                cout << "P" << gp[i-1] << "(" << start << "-" << i << ") ";
            start = i;
        }
    }

    float totalWT = 0, totalTAT = 0;
    cout << "\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << "\nAverage Waiting Time = " << totalWT / n << endl;
    cout << "Average Turnaround Time = " << totalTAT / n << endl;
    return 0;
}