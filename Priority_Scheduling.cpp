#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), pr(n), ct(n), tat(n), wt(n), pid(n);
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter arrival, burst, priority (lower = higher priority) for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
    }

    int completed = 0, time = 0;
    vector<pair<int,pair<int,int>>> gantt;

    while (completed < n) {
        int idx = -1, bestPr = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!done[i] && at[i] <= time && pr[i] < bestPr) { bestPr = pr[i]; idx = i; }

        if (idx == -1) { time++; continue; }

        int start = time;
        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        done[idx] = true;
        completed++;
        gantt.push_back({pid[idx], {start, time}});
    }

    cout << "\nGantt Chart:\n";
    for (auto &g : gantt) cout << "P" << g.first << "(" << g.second.first << "-" << g.second.second << ") ";
    cout << "\n\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        totalWT += wt[i]; totalTAT += tat[i];
    }
    cout << "Avg WT: " << totalWT/n << "\nAvg TAT: " << totalTAT/n << endl;
}