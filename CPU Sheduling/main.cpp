#include <iostream>
using namespace std;

void fcfs();
void sjf();
void priority();
void round_robin();
int MAX = 30;

int main()
{
    char ans;

    do
    {
        cout << "\n1. FCFS";
        cout << "\n2. SJF";
        cout << "\n3. Priority";
        cout << "\n4. Round Robin";
        cout << "\n0. Exit";
        cout << "\nEnter choice:-  ";
        int ch;
        cin >> ch;

        switch (ch)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            priority();
            break;
        case 4:
            round_robin();
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "\nInvalid Input ";
            break;
        }
        cout << "\n\nDo You want to continue ?... ";
        cin.ignore();
        cin >> ans;

    } while (ans == 'y');

    return 0;
}

void fcfs()
{
    int n;
    cout << "Enter the Number of Processes ==> ";
    cin >> n;

    int bt[n], at[n + 1], gc[n + 1], ft[n], wt[n], tat[n];

    cout << "\n*****Enter the Burst time of the processes*****\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the burst Time of the porcess p" << i << " ==> ";
        cin >> bt[i];
    }

    cout << "\n*****Enter the Arrival time of the processes*****\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Arrival Time of the porcess p" << i << " ==> ";
        cin >> at[i];
    }

    gc[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        gc[i] = gc[i - 1] + bt[i - 1];
        ft[i - 1] = gc[i];
    }

    for (int i = 0; i < n; i++)
    {
        wt[i] = gc[i] - at[i];
        tat[i] = ft[i] - at[i];
    }

    cout << "\n\n  Gantt Chart";
    cout << "\n+--";
    for (int i = 1; i < n; i++)
        cout << "-+--";
    cout << "-+\n";

    for (int i = 0; i < n; i++)
        cout << "| p" << i;
    cout << "|";

    cout << "\n+--";
    for (int i = 1; i < n; i++)
        cout << "-+--";
    cout << "-+\n";
    for (int i = 0; i <= n; i++)
        cout << gc[i] << "   ";

    cout << "\n\nProcess  BurstTime   WaitingTime     TurnAroundTime";
    for (int i = 0; i < n; i++)
        cout << endl
             << "   p" << i << "       " << bt[i] << "             " << wt[i] << "                " << gc[i + 1];

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += wt[i];
    float average_wt = float(sum) / n;

    sum = 0;
    for (int i = 0; i < n; i++)
        sum += tat[i];
    float average_tat = float(sum) / n;
    

    cout << "\nAverage Waiting Time = " << average_wt;
    cout << "\nAverage TurnAround Time = " << average_tat;
}

void sjf()
{
    int n;
    cout << "Enter the Number of Processes ==> ";
    cin >> n;

    int bt[n], gc[n + 1], ft[n], wt[n], tat[n], p[n];

    cout << "\n*****Enter the Burst time of the processes*****\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the burst Time of the porcess p" << i << " ==> ";
        cin >> bt[i];
        p[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (bt[j + 1] < bt[j])
            {
                swap(bt[j + 1], bt[j]);
                swap(p[j + 1], p[j]);
            }
        }
    }

    gc[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        gc[i] = gc[i - 1] + bt[i - 1];
        ft[i - 1] = gc[i];
    }

    for (int i = 0; i < n; i++)
    {
        wt[i] = gc[i];
        tat[i] = ft[i];
    }

    cout << "\n\n  Gantt Chart";
    cout << "\n+--";
    for (int i = 1; i < n; i++)
        cout << "-+--";
    cout << "-+\n";

    for (int i = 0; i < n; i++)
        cout << "| p" << p[i];
    cout << "|";

    cout << "\n+--";
    for (int i = 1; i < n; i++)
        cout << "-+--";
    cout << "-+\n";
    for (int i = 0; i <= n; i++)
        cout << gc[i] << "   ";

    cout << "\n\nProcess  BurstTime   WaitingTime     TurnAroundTime";
    for (int i = 0; i < n; i++)
        cout << endl
             << "   p" << p[i] << "       " << bt[i] << "             " << wt[i] << "                " << gc[i + 1];

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += wt[i];
    float average_wt = float(sum) / n;

    sum = 0;
    for (int i = 0; i < n; i++)
        sum += tat[i];
    float average_tat = float(sum) / n;

    cout << "\nAverage Waiting Time = " << average_wt;
    cout << "\nAverage TurnAround Time = " << average_tat;
}

void priority()
{
    int n;
    cout << "Enter the Number of Processes ==> ";
    cin >> n;

    int bt[n], pr[n], gc[n + 1], ft[n], wt[n], tat[n], p[n];

    cout << "\n*****Enter the Burst time of the processes*****\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the burst Time of the process p" << i << " ==> ";
        cin >> bt[i];
        p[i] = i;
    }

    cout << "\n*****Enter the Priority of  processes*****\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Priority Time of the process p" << i << " ==> ";
        cin >> pr[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (pr[j + 1] < pr[j])
            {
                swap(pr[j + 1], pr[j]);
                swap(bt[j + 1], bt[j]);
                swap(p[j + 1], p[j]);
            }
        }
    }

    gc[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        gc[i] = gc[i - 1] + bt[i - 1];
        ft[i - 1] = gc[i];
    }

    for (int i = 0; i < n; i++)
    {
        wt[i] = gc[i];
        tat[i] = ft[i];
    }

    cout << "\n\n  Gantt Chart";
    cout << "\n+--";
    for (int i = 1; i < n; i++)
        cout << "-+--";
    cout << "-+\n";

    for (int i = 0; i < n; i++)
        cout << "| p" << p[i];
    cout << "|";

    cout << "\n+--";
    for (int i = 1; i < n; i++)
        cout << "-+--";
    cout << "-+\n";
    for (int i = 0; i <= n; i++)
        cout << gc[i] << "   ";

    cout << "\n\nProcess  BurstTime   WaitingTime     TurnAroundTime";
    for (int i = 0; i < n; i++)
        cout << endl
             << "   p" << i << "       " << bt[i] << "             " << wt[i] << "                " << gc[i + 1];

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += wt[i];
    float average_wt = float(sum) / n;

    sum = 0;
    for (int i = 0; i < n; i++)
        sum += tat[i];
    float average_tat = float(sum) / n;

    cout << "\nAverage Waiting Time = " << average_wt;
    cout << "\nAverage TurnAround Time = " << average_tat;
}

void round_robin()
{
    int n, qt;
    cout << "Enter the Number of Processes ==> ";
    cin >> n;

    cout << "Enter the Quantum Time ==> ";
    cin >> qt;

    int bt[n], gc[MAX], gc_c = 0, ft[n], wt[n], tat[n], p[MAX], p_c = 0, count = 0, Max = 0;
    gc[gc_c] = 0;
    gc_c++;

    cout << "\n*****Enter the Burst time of the processes*****\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the burst Time of the process p" << i << " ==> ";
        cin >> bt[i];
        Max = max(Max, bt[i]);
        count += bt[i] == 0 ? 1 : 0;
        p[i] = i;
    }

    // Finding the values of gc[]  required for gantt chart
    int pass = Max / qt + (Max % qt != 0 ? 1 : 0);
    int t_bt[n];
    copy(bt, bt + n, t_bt); // This Function will copy the elements of bt[] into t_bt[]

    for (int x = 0; x < pass; x++)
    {
        for (int i = 0; i < n; i++)
        {
            if (t_bt[i] != 0)
            {
                gc[gc_c] = gc[gc_c - 1] + min(t_bt[i], qt);
                gc_c++;
                t_bt[i] -= min(t_bt[i], qt);

                p[p_c] = i;
                p_c++;
            }
        }
    }

    // Finding the waiting time and turn around time of each process
    for (int i = 0; i < n; i++)
    {
        int ft = 0;
        for (int j = 1; j <= gc_c; j++)
        {
            if (p[j - 1] == i)
            {
                ft = j;
            }
        }

        wt[i] = gc[ft] - bt[i];
        tat[i] = wt[i] + bt[i];
    }

    cout << "\n\n  Gantt Chart";
    cout << "\n+--";
    for (int i = 1; i < p_c; i++)
        cout << "-+--";
    cout << "-+\n";

    for (int i = 0; i < p_c; i++)
        cout << "| p" << p[i];
    cout << "|";

    cout << "\n+--";
    for (int i = 1; i < p_c; i++)
        cout << "-+--";
    cout << "-+\n";
    for (int i = 0; i < gc_c; i++)
        cout << gc[i] << "   ";

    cout << "\n\nProcess  BurstTime   WaitingTime     TurnAroundTime";
    for (int i = 0; i < n; i++)
        cout << endl
             << "   p" << p[i] << "       " << bt[i] << "             " << wt[i] << "                " << tat[i];

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += wt[i];
    float average_wt = float(sum) / n;

    sum = 0;
    for (int i = 0; i < n; i++)
        sum += tat[i];
    float average_tat = float(sum) / n;

    cout << "\nAverage Waiting Time = " << average_wt;
    cout << "\nAverage TurnAround Time = " << average_tat;
}
