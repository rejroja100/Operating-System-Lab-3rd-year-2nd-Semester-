#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

void avg(process proc[], int n)
{
    int wt = 0, tat = 0;

    for (int i = 0; i < n; i++)
        wt += proc[i].waiting_time;
    for (int i = 0; i < n; i++)
        tat += proc[i].turn_around_time;

    cout << "Turn around time : " << tat << "\t" << "avg turn around time : " << tat / n << endl;
    cout << "waiting time : " << wt << "\t" << "avg wating time : " << wt / n << endl;
}

void printSjf(process proc[], int n)
{
    cout << "-------------Shortest Job First (Non-Preemptive)----------" << endl;
    cout << "process\tArrival_Time\tBurst_Time\tCompletion_time\tTurn_Around_time\twaiting_time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << proc[i].pid << "\t\t" << proc[i].arrival_time << "\t\t" << proc[i].burst_time
             << "\t\t" << proc[i].completion_time << "\t\t" << proc[i].turn_around_time
             << "\t\t" << proc[i].waiting_time << endl;
    }
}

void ganttChartSjf(process proc[], int n)
{
    cout << "\n-------------------- Gantt Chart (SJF) --------------------\n"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << proc[i].pid << "(" << proc[i].completion_time - proc[i].burst_time
             << "-" << proc[i].completion_time << ")";
        if (i != n - 1)
            cout << " -> ";
    }
    cout << endl
         << endl;
}

void sjf(process proc[], int n)
{
    vector<process> input(proc, proc + n);
    vector<process> result;
    vector<bool> done(n, false);

    int time = 0;
    int complete = 0;

    while (complete < n)
    {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && input[i].arrival_time <= time)
            {
                if (input[i].burst_time < minBurst)
                {
                    minBurst = input[i].burst_time;
                    idx = i;
                }
                else if (input[i].burst_time == minBurst && idx != -1 && input[i].arrival_time < input[idx].arrival_time)
                {
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        input[idx].completion_time = time + input[idx].burst_time;
        input[idx].turn_around_time = input[idx].completion_time - input[idx].arrival_time;
        input[idx].waiting_time = input[idx].turn_around_time - input[idx].burst_time;


        time = input[idx].completion_time;
        done[idx] = true;
        complete++;

        result.push_back(input[idx]);
    }

    for(int i = 0; i < n; i++){
        proc[i] = result[i];
    }
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

    sjf(proc, n);
    printSjf(proc, n);
    ganttChartSjf(proc, n);
    avg(proc, n);

    return 0;
}