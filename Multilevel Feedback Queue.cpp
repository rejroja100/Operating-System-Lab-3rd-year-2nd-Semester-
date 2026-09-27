#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], rem[20], ct[20], wt[20], tat[20], pid[20];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter arrival & burst time for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
        rem[i] = bt[i];
    }

    int q0[100], q1[100], q2[100];
    int f0 = 0, r0 = 0, f1 = 0, r1 = 0, f2 = 0, r2 = 0;
    bool added[20] = {false};

    int tq0 = 4, tq1 = 8;

    int time = 0, completed = 0;
    int gp[1000], gs[1000], ge[1000], g = 0;

   
    int minAt = at[0];
    for (int i = 1; i < n; i++) if (at[i] < minAt) minAt = at[i];
    time = minAt;

    
    auto addNewArrivals = [&](int currentTime) {
        for (int i = 0; i < n; i++) {
            if (!added[i] && at[i] <= currentTime) {
                q0[r0++] = i;
                added[i] = true;
            }
        }
    };

    addNewArrivals(time);

    while (completed < n) {
        addNewArrivals(time);

        if (f0 < r0) { 
            int idx = q0[f0++];
            int run = min(tq0, rem[idx]);
            int start = time;
            time += run;
            rem[idx] -= run;
            gp[g] = pid[idx]; gs[g] = start; ge[g] = time; g++;

            addNewArrivals(time);

            if (rem[idx] == 0) {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed++;
            } else {
                q1[r1++] = idx; 
            }
        }
        else if (f1 < r1) { 
            int idx = q1[f1++];
            int run = min(tq1, rem[idx]);
            int start = time;
            time += run;
            rem[idx] -= run;
            gp[g] = pid[idx]; gs[g] = start; ge[g] = time; g++;

            addNewArrivals(time);

            if (rem[idx] == 0) {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed++;
            } else {
                q2[r2++] = idx;             }
        }
        else if (f2 < r2) { 
            int idx = q2[f2++];
            int start = time;
            time += rem[idx];
            rem[idx] = 0;
            gp[g] = pid[idx]; gs[g] = start; ge[g] = time; g++;

            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
        else {
            time++; 
        }
    }

    cout << "\nGantt Chart:\n";
    for (int i = 0; i < g; i++)
        cout << "P" << gp[i] << "(" << gs[i] << "-" << ge[i] << ") ";

    float totalWT = 0, totalTAT = 0;
    cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << "\nAverage Waiting Time = " << totalWT / n << endl;
    cout << "Average Turnaround Time = " << totalTAT / n << endl;
    return 0;
}