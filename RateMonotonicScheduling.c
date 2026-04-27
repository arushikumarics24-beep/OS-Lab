#include <stdio.h>
#include <math.h>

struct Task {
    int id;
    float Ci;  // Execution time
    float Ti;  // Period
};

// Function to sort tasks by period (ascending)
void sortByPeriod(struct Task tasks[], int n) {
    struct Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].Ti > tasks[j].Ti) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];

    // Input tasks
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d:\n", i + 1);
        printf("Execution Time (Ci): ");
        scanf("%f", &tasks[i].Ci);
        printf("Period (Ti): ");
        scanf("%f", &tasks[i].Ti);
    }

    // Step 1: Calculate CPU Utilization
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (tasks[i].Ci / tasks[i].Ti);
    }

    // Step 2: Calculate RMS Bound
    float bound = n * (pow(2, 1.0/n) - 1);

    // Display results
    printf("\nCPU Utilization (U) = %.4f\n", U);
    printf("RMS Bound = %.4f\n", bound);

    // Step 3: Check Schedulability
    if (U <= bound) {
        printf("Schedulable using RMS\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n");
    }

    // Step 4: Assign Priorities
    sortByPeriod(tasks, n);

    printf("\nTask Priorities (Lower period = Higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Priority %d -> Task %d (Ti = %.2f)\n",
               i + 1, tasks[i].id, tasks[i].Ti);
    }

    // Step 5: (Simulation note)
    printf("\nScheduling simulation is conceptual.\n");
    printf("At runtime: Highest priority READY task executes.\n");

    return 0;
}
