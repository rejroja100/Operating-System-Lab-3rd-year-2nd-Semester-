#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid;
    int burst_time;
    int remaining_time;
    int turn_around_time;
    int waiting_time;
    int completion_time;
    int arival_time;

};

void avg(process proc[], int n)
{
    int wt = 0, tt = 0;

    for (int i = 0; i < n; i++)
    {
        wt += proc[i].waiting_time;
        tt += proc[i].turn_around_time;
    }

    cout << "The everage waiting and everege turn around time is " << wt / n << " and " << tt / n << endl;
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

void Round_Robin(process proc[], int n, int quantam)
{
    vector<process> input(proc, proc + n);

    for (int i = 0; i < n; i++)
    {
        input[i].remaining_time = input[i].burst_time;
    }

    queue<int> q;
    for(int i = 0; i < n; i++) q.push(i);


    vector<pair<int, int>> ganttlog;

    int time = 0, complete = 0;

    while (complete < n)
    {
        int idx = q.front();
        q.pop();

        ganttlog.push_back({input[idx].pid, time});

        int currenttime = min(quantam, input[idx].remaining_time);
        input[idx].remaining_time -= currenttime;
        time += currenttime;
        
        if(input[idx].remaining_time > 0){
            q.push(idx);
        }
        else{
            complete++;
            input[idx].completion_time = time;
            input[idx].turn_around_time = input[idx].completion_time - input[idx].arival_time;
            input[idx].waiting_time = input[idx].turn_around_time - input[idx].burst_time;
        }

        ganttlog.push_back({-1, time});

        for(int i = 0; i < n; i++){
            proc[i] = input[i];
        }
    }
    
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

    Round_Robin(proc, n, quantum);
    printRR(proc, n);
    avg(proc, n);

    return 0;
}