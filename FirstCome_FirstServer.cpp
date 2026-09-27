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

void completionTime(process proc[], int n){
    proc[0].completion_time = proc[0].burst_time;

    for(int i = 1; i < n; i++){
        proc[i].completion_time = proc[i-1].completion_time + proc[i].burst_time;
    }
}

void turnAroundTime(process proc[], int n){
    for(int i = 0; i < n; i++){
        proc[i].turn_around_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void WaitingTime(process proc[], int n){
    proc[0].waiting_time = 0;

    for(int i = 1; i < n; i++){
        proc[i].waiting_time = proc[i].turn_around_time - proc[i].burst_time;
    }
}

void ganttChart(process proc[], int n){
    cout << "\n-------------------- Gantt Chart --------------------\n" << endl;

    int time = proc[0].arrival_time;

    for(int i = 0; i < n; i++){
        int start = time;
        int end = start + proc[i].burst_time;

        cout << "P" << proc[i].pid << "(" << start << "-" << end << ")";
        if(i != n - 1) cout << " -> ";

        time = end;
    }

    cout << endl << endl;
}

void fcfs(process proc[], int n){
    completionTime(proc, n);
    turnAroundTime(proc, n);
    WaitingTime(proc, n);
}

void printFcfs(process proc[], int n){
    cout<< "\n-------------First Come First Serve Algorithm----------\n" << endl;

    cout << "process\tArrival_Time\tBurst_Time\tCompletion_time\tTurn_Around_time\twaiting_time" <<endl;
    for(int i = 0; i < n; i++){
        cout << "P" << proc[i].pid << "\t\t" << proc[i].arrival_time << "\t\t" << proc[i].burst_time << "\t\t" << proc[i].completion_time << "\t\t" << proc[i].turn_around_time << "\t\t" << proc[i].waiting_time << endl;
    }
}

void avg(process proc[], int n){
    float p[2] = {0};

    for(int i = 0; i < n; i++) p[0] += proc[i].waiting_time;
    for(int i = 0; i < n; i++) p[1] += proc[i].turn_around_time;

    cout << "Total waiitng time : " << p[0] << endl;
    cout << "avg waiting time : " << p[0]/n << endl << endl;

    cout << "Total turn around time time : " << p[1] << endl;
    cout << "avg turn around time : " << p[1]/n << endl << endl;
}




int main(){
    int n;
    cout << "Enter the number of processes : "; cin >> n;

    process proc[n];

    for(int i = 0; i < n; i++){
        proc[i].pid = i+1;
        proc[i].arrival_time = i;
        cout << "Enter the burst time of P" << i+1 << ": ";
        cin >> proc[i].burst_time;
    }

    fcfs(proc, n);
    printFcfs(proc, n);
    ganttChart(proc, n);

    avg(proc, n);
}