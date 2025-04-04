#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20  // Max nodes (processes + resources)

int graph[MAX][MAX];
int numProcesses, numResources;

int visited[MAX], recStack[MAX];

int totalNodes;

int getResourceNode(int r) {
    return r;  // Resources: R0 to R(numResources-1)
}

int getProcessNode(int p) {
    return numResources + p;  // Processes: P0 to P(numProcesses-1)
}

bool isCyclicUtil(int node) {
    visited[node] = 1;
    recStack[node] = 1;

    for (int i = 0; i < totalNodes; i++) {
        if (graph[node][i]) {
            if (!visited[i] && isCyclicUtil(i))
                return true;
            else if (recStack[i])
                return true;
        }
    }
    recStack[node] = 0;
    return false;
}

bool isDeadlock() {
    for (int i = 0; i < totalNodes; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    for (int i = 0; i < totalNodes; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i))
                return true;
        }
    }
    return false;
}

void printGraph() {
    printf("\n📊 Allocation Graph (Adjacency List):\n");
    for (int i = 0; i < totalNodes; i++) {
        if (i < numResources)
            printf("R%d -> ", i);
        else
            printf("P%d -> ", i - numResources);

        for (int j = 0; j < totalNodes; j++) {
            if (graph[i][j]) {
                if (j < numResources)
                    printf("R%d ", j);
                else
                    printf("P%d ", j - numResources);
            }
        }
        printf("\n");
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter number of resources: ");
    scanf("%d", &numResources);

    totalNodes = numProcesses + numResources;

    int edges;
    printf("\nEnter number of edges (allocations + requests): ");
    scanf("%d", &edges);

    printf("Enter each edge (Type From To):\n");
    printf("  Type 0: Request edge (P -> R)\n");
    printf("  Type 1: Allocation edge (R -> P)\n");
    printf("Examples:\n  0 0 1  => P0 requests R1\n  1 2 1 => R2 allocated to P1\n\n");

    for (int i = 0; i < edges; i++) {
        int type, from, to;
        scanf("%d %d %d", &type, &from, &to);

        if (type == 0) {
            // Request: Process -> Resource
            graph[getProcessNode(from)][getResourceNode(to)] = 1;
        } else if (type == 1) {
            // Allocation: Resource -> Process
            graph[getResourceNode(from)][getProcessNode(to)] = 1;
        } else {
            printf("Invalid edge type.\n");
        }
    }

    printGraph();

    if (isDeadlock())
        printf("\n🔴 Deadlock Detected!\n");
    else
        printf("\n🟢 No Deadlock Detected.\n");

    return 0;
}
