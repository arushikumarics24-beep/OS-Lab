#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to calculate waiting and turnaround time using FCFS
void calculateFCFS(struct Process p[], int n) {
    p[0].waiting_time = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

// Function to display process details
void display(struct Process p[], int n, char queue_name[]) {
    printf("\n%s Queue:\n", queue_name);
    printf("PID\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);
    }
}

int main() {
    int n_sys, n_user;

    // Input system processes
    printf("Enter number of system processes: ");
    scanf("%d", &n_sys);

    struct Process sys[n_sys];

    for (int i = 0; i < n_sys; i++) {
        printf("Enter burst time for System Process %d: ", i + 1);
        sys[i].pid = i + 1;
        scanf("%d", &sys[i].burst_time);
    }

    // Input user processes
    printf("\nEnter number of user processes: ");
    scanf("%d", &n_user);

    struct Process user[n_user];

    for (int i = 0; i < n_user; i++) {
        printf("Enter burst time for User Process %d: ", i + 1);
        user[i].pid = i + 1;
        scanf("%d", &user[i].burst_time);
    }

    // Calculate for system queue
    calculateFCFS(sys, n_sys);

    // Calculate for user queue
    calculateFCFS(user, n_user);

    // Adjust user waiting time (since system queue runs first)
    int total_sys_time = 0;
    for (int i = 0; i < n_sys; i++) {
        total_sys_time += sys[i].burst_time;
    }

    for (int i = 0; i < n_user; i++) {
        user[i].waiting_time += total_sys_time;
        user[i].turnaround_time = user[i].waiting_time + user[i].burst_time;
    }

    // Display results
    display(sys, n_sys, "System");
    display(user, n_user, "User");

    return 0;
}
