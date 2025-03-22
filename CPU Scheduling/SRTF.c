#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct Process {
    int id, arrival, burst, remaining, waiting, turnaround;
};

void calculateSRTF(struct Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;
    
    while (completed < n) {
        minIndex = -1;
        int minRemaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minRemaining) {
                minRemaining = p[i].remaining;
                minIndex = i;
            }
        }
        if (minIndex == -1) {
            time++;
            continue;
        }
        p[minIndex].remaining--;
        time++;
        if (p[minIndex].remaining == 0) {
            completed++;
            p[minIndex].turnaround = time - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        }
    }
}

void printResults(struct Process p[], int n) {
    float avgWait = 0, avgTurnaround = 0;
    printf("\nProcess | Arrival | Burst | Waiting | Turnaround\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t  %d\t  %d\t   %d\t   %d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
        avgWait += p[i].waiting;
        avgTurnaround += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", avgWait / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaround / n);
}

int main() {
    int n = 5;
    struct Process p[] = {
        {0, 0, 4, 4, 0, 0},
        {1, 1, 3, 3, 0, 0},
        {2, 2, 1, 1, 0, 0},
        {3, 3, 5, 5, 0, 0},
        {4, 4, 2, 2, 0, 0}
    };
    
    calculateSRTF(p, n);
    printResults(p, n);
    
    return 0;
}
