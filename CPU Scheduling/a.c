#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Structure to hold process details
struct Process {
    int id, arrival, burst, priority, waiting, turnaround, remaining;
};

// Function to calculate First Come First Serve (FCFS) scheduling
void calculateFCFS(struct Process p[], int n) {
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

// Function to calculate Shortest Job First (SJF) scheduling (Non-Preemptive)
void calculateSJF(struct Process p[], int n) {
    bool done[n];
    int completed = 0, time = 0;
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
        p[minIndex].turnaround = time - p[minIndex].arrival;
        p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
        done[minIndex] = true;
        completed++;
    }
}

// Function to calculate Shortest Remaining Time First (SRTF) scheduling (Preemptive SJF)
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

// Function to calculate Priority Scheduling (Non-Preemptive)
void calculatePriority(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    calculateFCFS(p, n); // Treat as FCFS after sorting by priority
}

// Function to print the results (Waiting Time and Turnaround Time)
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
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("P%d: ", i);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
    }
    
    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF\n3. SRTF\n4. Priority\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            calculateFCFS(p, n);
            break;
        case 2:
            calculateSJF(p, n);
            break;
        case 3:
            calculateSRTF(p, n);
            break;
        case 4:
            calculatePriority(p, n);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    printResults(p, n);
    return 0;
}
