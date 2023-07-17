#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int pid,A_T,B_T,S_T,C_T,TAT,W_T,R_T;
    int priority;
};

float Ret_avg, Ret_tat;

bool ArrivalCompare(Process p1,Process p2)
{
    return p1.A_T<p2.A_T;
}

bool IDCompare(Process p1,Process p2)
{
    return p1.pid<p2.pid;
}


void FirstComeFirstSearch(Process p[], int n, bool flag)
{
    int i;
    int total_TAT = 0;
    int total_W_T = 0;
    int current_time = 0;
    int idle_time = 0;

    sort(p,p+n,ArrivalCompare);

    if(flag == 0)
    cout <<"Gantt Chart"<<endl;
    for(i=0;i<n;i++)
    {
        if(i==0)
            p[i].S_T = p[i].A_T;
        else
            p[i].S_T = max(p[i].A_T , p[i-1].C_T);

        if(p[i].S_T > current_time)
        {
            if(flag == 0)
            cout << current_time << " idle " ;
            idle_time += (p[i].S_T - current_time);
        }

        p[i].C_T = p[i].S_T + p[i].B_T;

        p[i].TAT = p[i].C_T - p[i].A_T;

        p[i].W_T = p[i].TAT - p[i].B_T;

        p[i].R_T = p[i].S_T - p[i].A_T;

        total_TAT += p[i].TAT;

        total_W_T += p[i].W_T;
        if(flag == 0)
        cout<<p[i].S_T<<" P"<<p[i].pid<<" ";
        current_time = p[i].C_T;
    }
    if(flag == 0)
    cout << p[i-1].C_T << endl;
    double avg_TAT = (double)total_TAT/n;
    double avg_W_T = (double)total_W_T/n;
    if(flag == 0)
    cout<<endl<<endl;
    if(flag == 0){
    for(i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;

}

void ShortestJobFirst(Process p[], int n, bool flag)
{

    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int chk = 0;
    int idle_time = 0;
    int is_completed[n+2];
    float avg_TAT;
    float avg_W_T;
    int total_TAT = 0;
    int total_idle_time = 0;
    int total_W_T = 0;
    memset(is_completed,0,sizeof(is_completed));
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
        int idx = -1;
        int past = current_time;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].A_T <= current_time && is_completed[i] == 0) {
                if(p[i].B_T < mn) {
                    mn = p[i].B_T;
                    idx = i;
                }
                if(p[i].B_T == mn) {
                    if(p[i].A_T < p[idx].A_T) {
                        mn = p[i].B_T;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].S_T = current_time;
            p[idx].C_T = p[idx].S_T + p[idx].B_T;
            p[idx].TAT = p[idx].C_T - p[idx].A_T;
            p[idx].W_T = p[idx].TAT - p[idx].B_T;
            p[idx].R_T = p[idx].S_T - p[idx].A_T;

            total_TAT += p[idx].TAT;
            total_W_T += p[idx].W_T;
            total_idle_time += p[idx].S_T - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].C_T;
            prev = current_time;
        }
        else {
            current_time++;
        }
        if(chk == -1 && idx == -1)continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;

        chk = idx;

    }
    if(flag == 0)
    cout << current_time << endl;

    int min_A_T = 10000000;
    int max_C_T = -1;
    for(int i = 0; i < n; i++) {
        min_A_T = min(min_A_T,p[i].A_T);
        max_C_T = max(max_C_T,p[i].C_T);
    }

    avg_TAT = (float) total_TAT / n;
    avg_W_T = (float) total_W_T / n;
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;

}


void ShortestRemainingTimeFirst(Process p[], int n, bool flag)
{


    int total_TAT = 0;
    int total_W_T = 0;
    int total_idle_time = 0;
    int idle_time=0;
    int burst_remain[n+5];
    int is_completed[n+5];

    memset(is_completed,0,sizeof(is_completed));

    float avg_TAT;
    float avg_W_T;
    float avg_R_T;
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int chk = -2;
    for(int i = 0; i < n; i++)
    {
        burst_remain[i] = p[i].B_T;
    }
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
        int past = current_time;
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].A_T <= current_time && is_completed[i] == 0) {
                if(burst_remain[i] < mn) {
                    mn = burst_remain[i];
                    idx = i;
                }
                if(burst_remain[i] == mn) {
                    if(p[i].A_T < p[idx].A_T) {
                        mn = burst_remain[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remain[idx] == p[idx].B_T) {
                p[idx].S_T = current_time;
                total_idle_time += p[idx].S_T - prev;
            }
            burst_remain[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_remain[idx] == 0) {
                p[idx].C_T = current_time;
                p[idx].TAT = p[idx].C_T - p[idx].A_T;
                p[idx].W_T = p[idx].TAT - p[idx].B_T;
                p[idx].R_T = p[idx].S_T - p[idx].A_T;

                total_TAT += p[idx].TAT;
                total_W_T += p[idx].W_T;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;
    if(flag == 0)
    cout << endl;
    int min_A_T = 10000000;
    int max_C_T = -1;
    for(int i = 0; i < n; i++) {
        min_A_T = min(min_A_T,p[i].A_T);
        max_C_T = max(max_C_T,p[i].C_T);
    }

    avg_TAT = (float) total_TAT / n;
    avg_W_T = (float) total_W_T / n;

    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;


}


void NonPreemtivePriority(Process p[],int n, bool flag)
{
    float avg_TAT;
    float avg_W_T;
    float avg_R_T;
    int total_TAT = 0;
    int total_W_T = 0;
    int total_R_T = 0;
    int total_idle_time = 0;
    int priority;
    int is_completed[n+5];
    memset(is_completed,0,sizeof(is_completed));

    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int chk = -2;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
         int past = current_time;
        int idx = -1;
        int mx = 100000000;
        for(int i = 0; i < n; i++) {
            if(p[i].A_T <= current_time && is_completed[i] == 0) {
                if(p[i].priority < mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].A_T < p[idx].A_T) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].S_T = current_time;
            p[idx].C_T = p[idx].S_T + p[idx].B_T;
            p[idx].TAT = p[idx].C_T - p[idx].A_T;
            p[idx].W_T = p[idx].TAT - p[idx].B_T;
            p[idx].R_T = p[idx].S_T - p[idx].A_T;

            total_TAT += p[idx].TAT;
            total_W_T += p[idx].W_T;
            total_R_T += p[idx].R_T;
            total_idle_time += p[idx].S_T - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].C_T;
            prev = current_time;
        }
        else {
            current_time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;
        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;
    if(flag == 0)
    cout << endl;
    int min_A_T = 10000000;
    int max_C_T = -1;
    for(int i = 0; i < n; i++) {
        min_A_T = min(min_A_T,p[i].A_T);
        max_C_T = max(max_C_T,p[i].C_T);
    }

    avg_TAT = (float) total_TAT / n;
    avg_W_T = (float) total_W_T / n;
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;
}

void PreemtivePriority(Process p[], int n, bool flag)
{
    float avg_TAT;
    float avg_W_T;
    int total_TAT = 0;
    int total_W_T = 0;
    int total_idle_time = 0;
    int burst_remain[n];
    int is_completed[n];
    memset(is_completed,0,sizeof(is_completed));
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    for(int i = 0; i < n; i++)
    {
        burst_remain[i] = p[i].B_T;
    }
     int chk = -2;
     if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n) {
         int past = current_time;
        int idx = -1;
        int mx = 100000000;
        for(int i = 0; i < n; i++) {
            if(p[i].A_T <= current_time && is_completed[i] == 0) {
                if(p[i].priority < mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].A_T < p[idx].A_T) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remain[idx] == p[idx].B_T) {
                p[idx].S_T = current_time;
                total_idle_time += p[idx].S_T - prev;
            }
            burst_remain[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_remain[idx] == 0) {
                p[idx].C_T = current_time;
                p[idx].TAT = p[idx].C_T - p[idx].A_T;
                p[idx].W_T = p[idx].TAT - p[idx].B_T;
                p[idx].R_T = p[idx].S_T - p[idx].A_T;

                total_TAT += p[idx].TAT;
                total_W_T += p[idx].W_T;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
        if(chk == idx) continue;
        if(flag == 0)
        cout << past << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;
    if(flag == 0)
    cout << endl;
    int min_A_T = 10000000;
    int max_C_T = -1;
    for(int i = 0; i < n; i++) {
        min_A_T = min(min_A_T,p[i].A_T);
        max_C_T = max(max_C_T,p[i].C_T);
    }

    avg_TAT = (float) total_TAT / n;
    avg_W_T = (float) total_W_T / n;
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;
}

void RoundRobin(Process p[],int n,int t, bool flag)
{
    float avg_TAT;
    float avg_W_T;
    float avg_R_T;
    int total_TAT = 0;
    int total_W_T = 0;
    int total_R_T = 0;
    int total_idle_time = 0;
    int burst_remain[n];
    int idx;


    sort(p, p+n, ArrivalCompare);
    for(int i = 0; i < n; i++)
    {
        p[i].S_T = -1;
        burst_remain[i] = p[i].B_T;
    }

    queue<int> q;
    int current_time = 0;
    int completed = 0;
    int mark[n];
    memset(mark,0,sizeof(mark));
    for(int i = 0; i < n; i++)
    {
        if(p[i].A_T <= current_time && mark[i] == 0)
        {
            q.push(i);
            mark[i] = 1;
        }
    }
    int chk = 0;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    while(completed != n)
    {
        int prev = current_time;
        idx = -1;
        if(!q.empty()){
            idx = q.front();
            q.pop();
            if(p[idx].S_T == -1)
                p[idx].S_T = current_time;
            if(burst_remain[idx]-t>0)
            {
                burst_remain[idx] -= t;
                current_time += t;
            }
            else
            {
                current_time += burst_remain[idx];
                burst_remain[idx] = 0;
                completed++;
                p[idx].C_T = current_time;
                p[idx].TAT = p[idx].C_T - p[idx].A_T;
                p[idx].W_T = p[idx].TAT - p[idx].B_T;
                p[idx].R_T = p[idx].S_T - p[idx].A_T;

                total_TAT += p[idx].TAT;
                total_W_T += p[idx].W_T;
            }
            for(int i = 0; i < n; i++)
            {
                if(p[i].A_T <= current_time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if(burst_remain[idx]>0)
            {
                q.push(idx);
            }

        }
        else
        {
            current_time++;
             for(int i = 0; i < n; i++) {
                if(p[i].A_T <= current_time && mark[i] == 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
        if(idx == -1)total_idle_time++;
        if(chk == -1 && idx == -1){continue;}
        if(flag == 0)
        cout << prev << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;

    avg_TAT = (float) total_TAT / n;
    avg_W_T = (float) total_W_T / n;

    sort(p,p+n,IDCompare);
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;
}

int srch(Process p[], int n, queue<int> q, int rem[])
{
    int pq = 100000000, idx = -1;
    while(!q.empty())
    {
        int pos = q.front();
       // cout << pos << " " <<p[pos].priority << endl;
        if(p[pos].priority < pq)
        {
            pq = p[pos].priority;
            idx = pos;
        }
        else if(p[pos].priority == pq)
        {
            if(p[pos].pid < p[idx].pid)
                idx = pos;
        }
        q.pop();
    }
    return idx;
}

void OurProposeAlgorithm(Process p[], int n, int t, bool flag)
{
    float avg_TAT;
    float avg_W_T;
    float avg_R_T;
    int total_TAT = 0;
    int total_W_T = 0;
    int total_R_T = 0;
    int total_idle_time = 0;
    int burst_remain[n];
    int idx;


    sort(p, p+n, ArrivalCompare);
    for(int i = 0; i < n; i++)
    {
        p[i].S_T = -1;
        burst_remain[i] = p[i].B_T;
    }

    queue<int> q;
    int current_time = 0;
    int completed = 0;
    int mark[n];
    memset(mark,0,sizeof(mark));
    for(int i = 0; i < n; i++)
    {
        if(p[i].A_T <= current_time && mark[i] == 0)
        {
            q.push(i);
            mark[i] = 1;
        }
    }
    int chk = 0;
    if(flag == 0)
    cout << "Gantt Chart" << endl;
    int freq[n+2] = {0};
    int inc = 0;
    for(int i = 0; i < n; i++)inc = max(inc,p[i].priority);
    //cout << inc << endl;
    while(completed != n)
    {
        int prev = current_time;
        idx = -1;
        if(!q.empty()){
            idx = srch(p,n,q,burst_remain);
            //cout << idx <<""<<p[idx].pid<<endl;
            queue<int> temp;
            while(!q.empty())
            {
                if(idx != q.front())temp.push(q.front());
                q.pop();
            }
            q = temp;
            if(idx != chk)freq[idx] = 1;
            else
                freq[idx]++;
            if(freq[idx] == 3)p[idx].priority = inc, inc++;
            //cout << idx <<" "<<p[idx].priority<<endl;

            if(p[idx].S_T == -1)
                p[idx].S_T = current_time;
            if(burst_remain[idx]-t>0)
            {
                burst_remain[idx] -= t;
                current_time += t;
            }
            else
            {
                current_time += burst_remain[idx];
                burst_remain[idx] = 0;
                completed++;
                p[idx].C_T = current_time;
                p[idx].TAT = p[idx].C_T - p[idx].A_T;
                p[idx].W_T = p[idx].TAT - p[idx].B_T;
                p[idx].R_T = p[idx].S_T - p[idx].A_T;

                total_TAT += p[idx].TAT;
                total_W_T += p[idx].W_T;
            }
            for(int i = 0; i < n; i++)
            {
                if(p[i].A_T <= current_time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if(burst_remain[idx]>0)
            {
                q.push(idx);
            }

        }
        else
        {
            current_time++;
             for(int i = 0; i < n; i++) {
                if(p[i].A_T <= current_time && mark[i] == 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
        if(idx == -1)total_idle_time++;
        if(chk == -1 && idx == -1){continue;}
        if(flag == 0)
        cout << prev << " " << (idx == -1?"idle":"P"+to_string(p[idx].pid)) << " " ;

        chk = idx;
    }
    if(flag == 0)
    cout << current_time << endl;

    avg_TAT = (float) total_TAT / n;
    avg_W_T = (float) total_W_T / n;

    sort(p,p+n,IDCompare);
    if(flag == 0){
    for(int i=0;i<n;i++)
    {
        cout<<"Process: P";
        cout<<p[i].pid<<"\t";

        cout<<"Finish time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].C_T<<"\t";

        cout<<"Response time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].R_T<<"\t";

        cout<<"Waiting time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].W_T<<"\t";

        cout<<"Turnaround time: ";
        cout << setw(2) << setfill(' ');
        cout<<p[i].TAT<<endl;
    }

    cout<<"Average waiting time: ";
    cout<<avg_W_T<<endl;

    cout<<"Average turnaround time: ";
    cout<<avg_TAT<<endl;

    cout <<"Idle time: " << total_idle_time << endl;
    cout << "Press any key for the home page" << endl;
    }
    Ret_avg = avg_W_T;
    Ret_tat = avg_TAT;
}

void CompareAll(Process p[], int n, int t)
{
    FirstComeFirstSearch(p,n,1);
    cout << "Algorithm: 1 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    cout << setw(2) << setfill(' ');
    ShortestJobFirst(p,n,1);
    cout << "Algorithm: 2 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    ShortestRemainingTimeFirst(p,n,1);
    cout << "Algorithm: 3 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    NonPreemtivePriority(p,n,1);
    cout << "Algorithm: 4 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    PreemtivePriority(p,n,1);
    cout << "Algorithm: 5 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    RoundRobin(p,n,t,1);
    cout << "Algorithm: 6 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    OurProposeAlgorithm(p,n,t,1);
    cout << "Algorithm: 7 Average Waiting Time: "<< Ret_avg <<" Average Turnaround Time: " << Ret_tat << endl;
    cout << "Press any key for the home page" << endl;
}

int main()
{
    int check;
    while(1)
    {
        cout << "1:FCFS" << endl;
        cout << "2:Non-Preemptive-SJF" << endl;
        cout << "3:Preemptive-SJF" << endl;
        cout << "4:Non-Preemptive-Priority" << endl;
        cout << "5:Preemptive-Priority" << endl;
        cout << "6:Round-Robin" << endl;
        cout << "7:Our-Proposed-Algorithm" << endl;
        cout << "8:Compare-All" << endl;
        cout << "9:Exit" << endl;
        cout << "Input your choice: ";
        cin >> check;
        if(check == 9)
        {
            break;
        }
        cout << endl;

        int n, i ,j, t;
        cout<<"Number of process,n: ";
        cin>>n;
        cout<<endl;

        struct Process p[n];

        if(check == 1 || check == 2 || check == 3 || check == 6)
        {
            if(check == 6)
            {
                cout<<"Enter time quantum: ";
                cin>>t;
            }
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].A_T;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].B_T;
                cout<<endl;

                p[i].pid=i+1;
            }
        }
        else if(check == 4 || check == 5)
        {
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].A_T;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].B_T;

                cout<<"Enter the priority of P"<<i+1<<": ";
                cin>>p[i].priority;
                cout<<endl;

                p[i].pid=i+1;
            }
        }
        else
        {

            cout<<"Enter time quantum: ";
            cin>>t;
            for(i=0;i<n;i++)
            {
                cout<<"Enter the arrival time of P"<<i+1<<": ";
                cin>>p[i].A_T;

                cout<<"Enter the burst time of P"<<i+1<<": ";
                cin>>p[i].B_T;

                cout<<"Enter the priority of P"<<i+1<<": ";
                cin>>p[i].priority;
                cout<<endl;

                p[i].pid=i+1;
            }
        }


        if(check == 1)
        {
            FirstComeFirstSearch(p,n,0);
        }
        else if(check == 2)
        {
            ShortestJobFirst(p,n,0);
        }
        else if(check == 3)
        {
            ShortestRemainingTimeFirst(p,n,0);
        }
        else if(check == 4)
        {
            NonPreemtivePriority(p,n,0);
        }
        else if(check == 5)
        {
            PreemtivePriority(p,n,0);
        }
        else if(check == 6)
        {
           RoundRobin(p,n,t,0);
        }
        else if(check == 7)
        {
            OurProposeAlgorithm(p,n,t,0);
        }
        else if(check == 8)
        {
            CompareAll(p,n,t);
        }
        getchar();
        getchar();
    }
    return 0;
}

