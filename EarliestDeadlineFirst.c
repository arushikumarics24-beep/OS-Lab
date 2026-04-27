#include <stdio.h>

#define MAX 20

struct Process {
    int id;
    int arrival;
    int execution;
    int deadline;
    int remaining;
    int completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);
        printf("Execution Time (Ci): ");
        scanf("%d", &p[i].execution);
        printf("Deadline (Di): ");
        scanf("%d", &p[i].deadline);

        p[i].remaining = p[i].execution;
        p[i].completed = 0;
    }

    // Step 1: CPU Utilization
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)p[i].execution / p[i].deadline;
    }

    printf("\nCPU Utilization (U) = %.2f\n", U);

    // Step 2: Feasibility Check
    if (U > 1.0) {
        printf("Scheduling not feasible (deadlines may be missed)\n");
    } else {
        printf("Scheduling feasible\n");
    }

    // Step 3–4: EDF Scheduling Simulation
    int t = 0, completed_count = 0;

    printf("\nExecution Order (time -> process):\n");

    while (completed_count < n) {
        int idx = -1;
        int earliest_deadline = 999999;

        // Find process with earliest deadline among ready processes
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= t && p[i].remaining > 0) {
                if (p[i].deadline < earliest_deadline) {
                    earliest_deadline = p[i].deadline;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process ready
            printf("Time %d -> Idle\n", t);
            t++;
            continue;
        }

        // Execute selected process
        printf("Time %d -> P%d\n", t, p[idx].id);
        p[idx].remaining--;

        // If completed
        if (p[idx].remaining == 0) {
            p[idx].completed = 1;
            completed_count++;
        }

        t++;
    }

    printf("\nAll processes completed.\n");

    return 0;
}
