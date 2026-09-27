#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int burst_time;
    int remain_time;
    int arival_time;
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

    cout << "Turn around time : " << tat << "\t" << "avg turn around time : " << (float)tat / n << endl;
    cout << "waiting time : " << wt << "\t" << "avg waiting time : " << (float)wt / n << endl;
}

void printRR(process proc[], int n)
{
    cout << "-------------Round Robin----------" << endl;
    cout << "process\tArrival_Time\tBurst_Time\tCompletion_time\tTurn_Around_time\twaiting_time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << proc[i].pid << "\t\t" << proc[i].burst_time
             << "\t\t" << "\t\t" << proc[i].turn_around_time
             << "\t\t" << proc[i].waiting_time << endl;
    }
}

void roundRobin(process proc[], int n, int quantam)
{
    vector<process> input(proc, proc + n);

    for (int i = 0; i < n; i++)
    {
        input[i].remain_time = input[i].burst_time;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i);

    vector<pair<int, int>> ganttLog;

    int time = 0;
    int complete = 0;

    while (complete < n)
    {
        int idx = q.front();
        q.pop();

        ganttLog.push_back({input[idx].pid, time});

        int currenttime = min(quantam, input[idx].remain_time);
        input[idx].remain_time -= currenttime;
        time += currenttime;

        if (input[idx].remain_time > 0)
        {
            q.push(idx);
        }
        else
        {
            complete++;
            input[idx].completion_time = time;
            input[idx].turn_around_time = input[idx].completion_time - input[idx].arival_time;
            input[idx].waiting_time = input[idx].turn_around_time - input[idx].burst_time;
        }

        ganttLog.push_back({-1, time});

        for (int i = 0; i < n; i++)
        {
            proc[i] = input[i];
        }
    }

    // print gantt chart
    cout << "\n-------------------- Gantt Chart (Round Robin) --------------------\n"
         << endl;
    for (int i = 0; i + 1 < (int)ganttLog.size(); i++)
    {
        cout << "P" << ganttLog[i].first << "(" << ganttLog[i].second << "-" << ganttLog[i + 1].second << ")";
        if (i + 2 < (int)ganttLog.size())
            cout << " -> ";
    }
    cout << endl
         << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes : ";
    cin >> n;

    process proc[n];

    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        proc[i].arival_time = i; // auto-assigned: 0,1,2,3...
        cout << "Enter the burst time of P" << i + 1 << ": ";
        cin >> proc[i].burst_time;
    }

    int quantum;
    cout << "Enter the time quantum : ";
    cin >> quantum;

    roundRobin(proc, n, quantum);
    printRR(proc, n);
    avg(proc, n);

    return 0;
}