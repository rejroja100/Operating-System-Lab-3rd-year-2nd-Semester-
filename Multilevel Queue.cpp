#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), q_level(n), ct(n), tat(n), wt(n), pid(n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter arrival, burst, queue(0=system/high priority, 1=user/low priority) for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i] >> q_level[i];
    }

    vector<int> order; 
    for (int lvl = 0; lvl <= 1; lvl++) {
        vector<int> temp;
        for (int i = 0; i < n; i++) if (q_level[i] == lvl) temp.push_back(i);
        sort(temp.begin(), temp.end(), [&](int a, int b){ return at[a] < at[b]; });
        for (int x : temp) order.push_back(x);
    }

    int time = 0;
    vector<pair<int,pair<int,int>>> gantt;

    for (int idx : order) {
        if (time < at[idx]) time = at[idx];
        int start = time;
        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        gantt.push_back({pid[idx], {start, time}});
    }

    cout << "\nGantt Chart:\n";
    for (auto &g : gantt) cout << "P" << g.first << "(" << g.second.first << "-" << g.second.second << ") ";
    cout << "\n\nP\tAT\tBT\tQ\tCT\tTAT\tWT\n";
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << q_level[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        totalWT += wt[i]; totalTAT += tat[i];
    }
    cout << "Avg WT: " << totalWT/n << "\nAvg TAT: " << totalTAT/n << endl;
}