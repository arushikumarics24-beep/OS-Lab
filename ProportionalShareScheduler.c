#include <stdio.h>

#define MAX 20
#define TIME_QUANTUM 10   // You can adjust this

struct Process {
    int id;
    int arrival;
    float execution;
    float remaining;
    float weight;
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

        printf("Execution Time: ");
        scanf("%f", &p[i].execution);

        printf("Weight: ");
        scanf("%f", &p[i].weight);

        p[i].remaining = p[i].execution;
        p[i].completed = 0;
    }

    // Step 1: Compute total weight
    float total_weight = 0;
    for (int i = 0; i < n; i++) {
        total_weight += p[i].weight;
    }

    int completed_count = 0;
    int t = 0;

    printf("\nExecution Timeline:\n");

    // Step 2: Scheduling loop
    while (completed_count < n) {

        int any_ready = 0;

        for (int i = 0; i < n; i++) {

            // Check if process is ready
            if (p[i].arrival <= t && p[i].remaining > 0) {

                any_ready = 1;

                // Step 3: Calculate proportional time slice
                float time_slice = (p[i].weight / total_weight) * TIME_QUANTUM;

                if (time_slice < 1)
                    time_slice = 1; // minimum execution unit

                printf("Time %.2d -> Running P%d for %.2f units\n", t, p[i].id, time_slice);

                // Execute
                if (p[i].remaining <= time_slice) {
                    t += (int)p[i].remaining;
                    p[i].remaining = 0;
                } else {
                    p[i].remaining -= time_slice;
                    t += (int)time_slice;
                }

                // Completion check
                if (p[i].remaining <= 0 && p[i].completed == 0) {
                    p[i].completed = 1;
                    completed_count++;
                    total_weight -= p[i].weight;

                    printf("P%d completed at time %d\n", p[i].id, t);
                }
            }
        }

        // If no process is ready, CPU idle
        if (!any_ready) {
            printf("Time %d -> Idle\n", t);
            t++;
        }
    }

    printf("\nAll processes completed.\n");
    return 0;
}
