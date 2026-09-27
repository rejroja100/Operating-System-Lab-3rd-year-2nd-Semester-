#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

void srtf(process proc[], int n){
    vector<process> input(proc, proc + n);
    vector<bool> done(n, false);

    for(int i = 0; i < n; i++){
        input[i].remaining_time = input[i].burst_time;
    }

    int time = 0;
    int complete = 0;

    vector<pair<int,int>> ganttLog; // {pid, time} -> records when a process starts running at a given time unit
    int lastPid = -1;

    while(complete < n){
        int idx = -1;
        int minRemaining = INT_MAX;

        // find process with smallest remaining time among those that have arrived and aren't finished
        for(int i = 0; i < n; i++){
            if(!done[i] && input[i].arrival_time <= time && input[i].remaining_time > 0){
                if(input[i].remaining_time < minRemaining){
                    minRemaining = input[i].remaining_time;
                    idx = i;
                }
                else if(input[i].remaining_time == minRemaining && idx != -1 &&
                        input[i].arrival_time < input[idx].arrival_time){
                    idx = i;
                }
            }
        }

        if(idx == -1){
            // CPU idle, nobody has arrived yet
            time++;
            continue;
        }

        // log gantt chart entry only when the running process changes
        if(lastPid != input[idx].pid){
            ganttLog.push_back({input[idx].pid, time});
            lastPid = input[idx].pid;
        }

        // run this process for 1 unit of time
        input[idx].remaining_time--;
        time++;

        // if it just finished
        if(input[idx].remaining_time == 0){
            done[idx] = true;
            complete++;

            input[idx].completion_time = time;
            input[idx].turn_around_time = input[idx].completion_time - input[idx].arrival_time;
            input[idx].waiting_time = input[idx].turn_around_time - input[idx].burst_time;
        }
    }

    // mark the very end of the gantt chart
    ganttLog.push_back({-1, time});

    // copy back results in original pid order
    for(int i = 0; i < n; i++){
        proc[i] = input[i];
    }

    // print the gantt chart
    cout << "\n-------------------- Gantt Chart (SRTF) --------------------\n" << endl;
    for(int i = 0; i + 1 < (int)ganttLog.size(); i++){
        cout << "P" << ganttLog[i].first << "(" << ganttLog[i].second << "-" << ganttLog[i+1].second << ")";
        if(i + 2 < (int)ganttLog.size()) cout << " -> ";
    }
    cout << endl << endl;
}

void printSrtf(process proc[], int n){
    cout << "-------------Shortest Remaining Time First (Preemptive)----------" << endl;
    cout << "process\tArrival_Time\tBurst_Time\tCompletion_time\tTurn_Around_time\twaiting_time" << endl;
    for(int i = 0; i < n; i++){
        cout << "P" << proc[i].pid << "\t\t" << proc[i].arrival_time << "\t\t" << proc[i].burst_time
             << "\t\t" << proc[i].completion_time << "\t\t" << proc[i].turn_around_time
             << "\t\t" << proc[i].waiting_time << endl;
    }
}

void avg(process proc[], int n){
    int wt = 0, tat = 0;

    for(int i = 0; i < n; i++) wt += proc[i].waiting_time;
    for(int i = 0; i < n; i++) tat += proc[i].turn_around_time;

    cout << "Turn around time : " << tat << "\t" << "avg turn around time : " << (float)tat / n << endl;
    cout << "waiting time : " << wt << "\t" << "avg waiting time : " << (float)wt / n << endl;
}

int main(){
    int n;
    cout << "Enter the number of processes : "; cin >> n;

    process proc[n];

    for(int i = 0; i < n; i++){
        proc[i].pid = i+1;
        cout << "Enter the arrival time of P" << i+1 << ": ";
        cin >> proc[i].arrival_time;
        cout << "Enter the burst time of P" << i+1 << ": ";
        cin >> proc[i].burst_time;
    }

    srtf(proc, n);
    printSrtf(proc, n);
    avg(proc, n);

    return 0;
}