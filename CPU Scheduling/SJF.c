#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, arrival, burst, waiting, turnaround;
};

void sortByBurst(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].burst > p[j].burst) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateSJF(struct Process p[], int n) {
    int completion[n], completed = 0, time = 0;
    bool done[n];
    for (int i = 0; i < n; i++) done[i] = false;
    
    while (completed < n) {
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (minIndex == -1 || p[i].burst < p[minIndex].burst)
                    minIndex = i;
            }
        }
        if (minIndex == -1) {
            time++;
            continue;
        }
        time += p[minIndex].burst;
        completion[minIndex] = time;
        p[minIndex].turnaround = completion[minIndex] - p[minIndex].arrival;
        p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        done[minIndex] = true;
        completed++;
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
        {0, 0, 4, 0, 0},
        {1, 1, 3, 0, 0},
        {2, 2, 1, 0, 0},
        {3, 3, 5, 0, 0},
        {4, 4, 2, 0, 0}
    };
    
    calculateSJF(p, n);
    printResults(p, n);
    
    return 0;
}
