#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max_need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int n_processes, n_resources;

void initialize() {
    // Initialize allocation and max_need matrices
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n_processes);

    printf("Enter number of resources: ");
    scanf("%d", &n_resources);

    printf("Enter allocation matrix (%d x %d):\n", n_processes, n_resources);
    for (i = 0; i < n_processes; i++) {

        for (j = 0; j < n_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter maximum need matrix (%d x %d):\n", n_processes, n_resources);
    for (i = 0; i < n_processes; i++) {
        for (j = 0; j < n_resources; j++) {
            scanf("%d", &max_need[i][j]);
        }
    }

    printf("Enter available resources vector (%d elements):\n", n_resources);
    for (j = 0; j < n_resources; j++) {
        scanf("%d", &available[j]);
    }
}

void detect_deadlock() {
    int i, j, k;
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int safe_sequence[MAX_PROCESSES];
    int safe_sequence_count = 0;

    // Initialize work vector and finish array
    for (j = 0; j < n_resources; j++) {
        work[j] = available[j];
    }

    for (i = 0; i < n_processes; i++) {
        finish[i] = 0;
    }

    // Find a process which can be allocated resources
    int found;
    do {
        found = 0;
        for (i = 0; i < n_processes; i++) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (j = 0; j < n_resources; j++) {
                    if (max_need[i][j] - allocation[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    // Process can be allocated resources
                    for (j = 0; j < n_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    safe_sequence[safe_sequence_count++] = i;
                    found = 1;
                }
            }
        }
    } while (found);

    // Check if all processes are finished
    for (i = 0; i < n_processes; i++) {
        if (!finish[i]) {
            printf("Deadlock detected!\n");
            return;
        }
    }

    // No deadlock detected, print safe sequence
    printf("No deadlock detected.\nSafe sequence: ");
    for (i = 0; i < n_processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
}

int main() {
    initialize();
    detect_deadlock();
    return 0;
}