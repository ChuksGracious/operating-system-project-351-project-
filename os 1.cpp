#include <iostream>

using namespace std;

// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
                     int bt[], int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;

    // calculating waiting time
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

//Function to calculate average time
void findavgTime(int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    //Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt);

    //Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    //Display processes along with all details
    cout << "Processes  "
         << " Burst time  "
         << " Waiting time  "
         << " Turn around time\n";

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << "   " << i + 1 << "\t\t" << bt[i] << "\t    "
             << wt[i] << "\t\t  " << tat[i] << endl;
    }

    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}
int mat[10][6];

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrangeArrival(int num, int mat[][6])
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (mat[j][1] > mat[j + 1][1])
            {
                for (int k = 0; k < 5; k++)
                {
                    swap(mat[j][k], mat[j + 1][k]);
                }
            }
        }
    }
}

void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for (int i = 1; i < num; i++)
    {
        temp = mat[i - 1][3];
        int low = mat[i][2];
        for (int j = i; j < num; j++)
        {
            if (temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for (int k = 0; k < 6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}
void findWaitingTime(int processes[], int n,
                     int bt[], int wt[], int quantum)
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0; // Current time

    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        bool done = true;

        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++)
        {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process

                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;

                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                }

                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t = t + rem_bt[i];

                    // Waiting time is current time minus time
                    // used by this process
                    wt[i] = t - bt[i];

                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }
        }

        // If all processes are done
        if (done == true)
            break;
    }
}

// Function to calculate turn around time
void findTurnAroundTimeRR(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],
                 int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, quantum);

    // Function to find turn around time for all processes
    findTurnAroundTimeRR(processes, n, bt, wt, tat);

    // Display processes along with all details
    cout << "Processes "
         << " Burst time "
         << " Waiting time "
         << " Turn around time\n";

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i + 1 << "\t\t" << bt[i] << "\t "
             << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}

int main()
{

    cout << "Please enter the options below: " << endl;
    cout << "1. Scheduling Method" << endl;
    cout << "2. Premtive mode (NONE)" << endl;
    cout << "3. Show result" << endl;
    cout << "4. Exit" << endl;

    int option;
    cin >> option;

    if (option == 1)
    {

        cout << "Please enter the scheduling method: " << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF" << endl;
        cout << "3. PS" << endl;
        cout << "4. RR" << endl;

        int method;
        cin >> method;

        if (method == 1)
        {
            //process id's
            int processes[] = {1, 2, 3};
            int n = sizeof processes / sizeof processes[0];

            //Burst time of all processes
            int burst_time[] = {10, 5, 8};

            findavgTime(processes, n, burst_time);
        }
        else if (method == 2)
        {
            int num, temp;

            cout << "Enter number of Process: ";
            cin >> num;

            cout << "...Enter the process ID...\n";
            for (int i = 0; i < num; i++)
            {
                cout << "...Process " << i + 1 << "...\n";
                cout << "Enter Process Id: ";
                cin >> mat[i][0];
                cout << "Enter Arrival Time: ";
                cin >> mat[i][1];
                cout << "Enter Burst Time: ";
                cin >> mat[i][2];
            }

            cout << "Before Arrange...\n";
            cout << "Process ID\tArrival Time\tBurst Time\n";
            for (int i = 0; i < num; i++)
            {
                cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t"
                     << mat[i][2] << "\n";
            }

            arrangeArrival(num, mat);
            completionTime(num, mat);
            cout << "Final Result...\n";
            cout << "Process ID\tArrival Time\tBurst Time\tWaiting "
                    "Time\tTurnaround Time\n";
            for (int i = 0; i < num; i++)
            {
                cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t"
                     << mat[i][2] << "\t\t" << mat[i][4] << "\t\t"
                     << mat[i][5] << "\n";
            }
        }
        else if (method == 3)
        {
            int a[10], b[10], x[10], pr[10] = {0};
            int waiting[10], turnaround[10], completion[10];
            int i, j, smallest, count = 0, time, n;
            double avg = 0, tt = 0, end;
            cout << "\nEnter the number of Processes: ";
            cin >> n;
            for (i = 0; i < n; i++)
            {
                cout << "\nEnter arrival time of process: ";
                cin >> a[i];
            }
            for (i = 0; i < n; i++)
            {
                cout << "\nEnter burst time of process: ";
                cin >> b[i];
            }
            for (i = 0; i < n; i++)
            {
                cout << "\nEnter priority of process: ";
                cin >> pr[i];
            }
            for (i = 0; i < n; i++)
                x[i] = b[i];

            pr[9] = -1;
            for (time = 0; count != n; time++)
            {
                smallest = 9;
                for (i = 0; i < n; i++)
                {
                    if (a[i] <= time && pr[i] > pr[smallest] && b[i] > 0)
                        smallest = i;
                }
                time += b[smallest] - 1;
                b[smallest] = -1;
                count++;
                end = time + 1;
                completion[smallest] = end;
                waiting[smallest] = end - a[smallest] - x[smallest];
                turnaround[smallest] = end - a[smallest];
            }
            cout << "Process"
                 << "\t"
                 << "burst-time"
                 << "\t"
                 << "arrival-time"
                 << "\t"
                 << "waiting-time"
                 << "\t"
                 << "turnaround-time"
                 << "\t"
                 << "completion-time"
                 << "\t"
                 << "Priority" << endl;
            for (i = 0; i < n; i++)
            {
                cout << "p" << i + 1 << "\t\t" << x[i] << "\t\t" << a[i] << "\t\t" << waiting[i] << "\t\t" << turnaround[i] << "\t\t" << completion[i] << "\t\t" << pr[i] << endl;
                avg = avg + waiting[i];
                tt = tt + turnaround[i];
            }
            cout << "\n\nAverage waiting time =" << avg / n;
            cout << "  Average Turnaround time =" << tt / n << endl;
        }
        else if (method == 4)
        {
            cout<<"Please enter the time quantum value"<<endl;
            int tq;

            cin>>tq;

            int processes[] = {1, 2, 3};
            int n = sizeof processes / sizeof processes[0];

            // Burst time of all processes
            int burst_time[] = {10, 5, 8};

            // Time quantum
            int quantum = tq;
            findavgTime(processes, n, burst_time, quantum);
        }
    }
    else if (option == 2)
    {
        cout << "Premtive Mode" << endl;
    }
    else if (option == 3)
    {
        cout << "Show result" << endl;
    }
    else if (option == 4)
    {
        return 0;
    }

    return 0;
}
