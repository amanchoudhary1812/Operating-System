#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 5

int available[MAX_RESOURCES];                 // Available instances of each resource
int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Current allocations
int max[MAX_PROCESSES][MAX_RESOURCES];        // Maximum need per process

int numProcesses, numResources;

// Function to print current state
void printState() {
    printf("\nCurrent Allocation State:\n");
    printf("Process\tAllocated Resources\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < numResources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < numResources; j++) {
        printf("R%d: %d\t", j, available[j]);
    }
    printf("\n");
}

// Function to check if request follows increasing order
bool isIncreasingOrder(int request[]) {
    for (int i = 1; i < numResources; i++) {
        if (request[i] > 0 && request[i - 1] == 0)
            return false;
    }
    return true;
}

// Function to check if request is for all resources (prevents Hold and Wait)
bool isAllResourcesRequested(int processID, int request[]) {
    for (int i = 0; i < numResources; i++) {
        if (request[i] < max[processID][i])
            return false;
    }
    return true;
}

// Request resources with prevention checks
bool requestResources(int processID, int request[]) {
    if (!isIncreasingOrder(request)) {
        printf("\nRequest denied: Must request resources in increasing order (prevent Circular Wait).\n");
        return false;
    }

    if (!isAllResourcesRequested(processID, request)) {
        printf("\nRequest denied: Must request all needed resources at once (prevent Hold and Wait).\n");
        return false;
    }

    for (int i = 0; i < numResources; i++) {
        if (request[i] > available[i]) {
            printf("\nRequest denied: Not enough resources available.\n");
            return false;
        }
    }

    // Allocation
    for (int i = 0; i < numResources; i++) {
        available[i] -= request[i];
        allocation[processID][i] += request[i];
    }

    printf("\nRequest granted: Resources allocated to P%d.\n", processID);
    return true;
}

int main() {
    printf("Enter number of processes (min 2): ");
    scanf("%d", &numProcesses);
    printf("Enter number of resources (min 3): ");
    scanf("%d", &numResources);

    // Input available instances
    printf("\nEnter available instances of each resource:\n");
    for (int i = 0; i < numResources; i++) {
        printf("R%d: ", i);
        scanf("%d", &available[i]);
    }

    // Input max need for each process
    printf("\nEnter maximum resource needs per process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d:\n", i);
        for (int j = 0; j < numResources; j++) {
            printf("Max R%d: ", j);
            scanf("%d", &max[i][j]);
        }
    }

    printState();

    // Simulate resource requests
    for (int p = 0; p < numProcesses; p++) {
        int request[MAX_RESOURCES];
        printf("\nEnter request for P%d:\n", p);
        for (int j = 0; j < numResources; j++) {
            printf("Request R%d: ", j);
            scanf("%d", &request[j]);
        }

        requestResources(p, request);
        printState();
    }

    printf("\nDeadlock Prevention Simulation Complete.\n");
    return 0;
}
