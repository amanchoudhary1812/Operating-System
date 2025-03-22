#include <stdio.h>

struct Process {
    int id, arrival, burst, priority, waiting, turnaround;
};

void sortByPriority(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculatePriorityScheduling(struct Process p[], int n) {
    int completion[n];
    p[0].waiting = 0;
    completion[0] = p[0].arrival + p[0].burst;
    p[0].turnaround = p[0].burst;
    
    for (int i = 1; i < n; i++) {
        completion[i] = (completion[i - 1] > p[i].arrival ? completion[i - 1] : p[i].arrival) + p[i].burst;
        p[i].turnaround = completion[i] - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void printResults(struct Process p[], int n) {
    float avgWait = 0, avgTurnaround = 0;
    printf("\nProcess | Arrival | Burst | Priority | Waiting | Turnaround\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t  %d\t  %d\t  %d\t   %d\t   %d\n", p[i].id, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turnaround);
        avgWait += p[i].waiting;
        avgTurnaround += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", avgWait / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaround / n);
}

int main() {
    int n = 5;
    struct Process p[] = {
        {0, 0, 4, 2, 0, 0},
        {1, 1, 3, 3, 0, 0},
        {2, 2, 1, 4, 0, 0},
        {3, 3, 5, 5, 0, 0},
        {4, 4, 2, 1, 0, 0}
    };
    
    sortByPriority(p, n);
    calculatePriorityScheduling(p, n);
    printResults(p, n);
    
    return 0;
}