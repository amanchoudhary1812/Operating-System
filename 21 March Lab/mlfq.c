#include <stdio.h>

#define MAX 100

typedef struct {
    int id, arrival_time, burst_time, remaining_time, completion_time;
    int waiting_time, turnaround_time;
} Process;

// Function to execute Round Robin
void round_robin(Process processes[], int *n, int tq, int *time, int queue_level, Process next_queue[], int *next_size) {
    printf("\nExecuting Queue %d (Time Quantum = %d):\n", queue_level, tq);
    int remaining = *n;

    while (remaining > 0) {
        int found = 0;
        for (int j = 0; j < *n; j++) {
            if (processes[j].remaining_time > 0 && processes[j].arrival_time <= *time) {
                found = 1;
                if (processes[j].remaining_time > tq) {
                    printf("P%d -> (Remaining Time: %d)\n", processes[j].id, processes[j].remaining_time - tq);
                    processes[j].remaining_time -= tq;
                    *time += tq;
                    next_queue[(*next_size)++] = processes[j];  // Move unfinished process to next queue
                } else {
                    printf("P%d -> (Completed)\n", processes[j].id);
                    *time += processes[j].remaining_time;
                    processes[j].completion_time = *time;
                    processes[j].turnaround_time = processes[j].completion_time - processes[j].arrival_time;
                    processes[j].waiting_time = processes[j].turnaround_time - processes[j].burst_time;
                    processes[j].remaining_time = 0;
                    remaining--;
                }
            }
        }
        if (!found) (*time)++; // Prevent infinite loops if no process is ready
    }
    printf("END\n");
}

// Function to execute FCFS
void fcfs(Process processes[], int *n, int *time) {
    printf("\nExecuting Queue 3 (FCFS):\n");
    if (*n == 0) {
        printf("No processes left for FCFS.\n");
        return;
    }

    for (int i = 0; i < *n; i++) {
        if (processes[i].remaining_time > 0) {
            if (*time < processes[i].arrival_time) {
                *time = processes[i].arrival_time;  // Prevent negative waiting time
            }
            printf("P%d -> (Completed)\n", processes[i].id);
            *time += processes[i].remaining_time;
            processes[i].completion_time = *time;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
            processes[i].remaining_time = 0;
        }
    }
    printf("END\n");
}

// Function to execute MLFQ
void execute_mlfq(Process processes[], int n) {
    int time = 0;
    int initial_n = n;

    // First Queue (RR, TQ = 4)
    Process queue2[MAX];
    int q2_size = 0;
    round_robin(processes, &n, 4, &time, 1, queue2, &q2_size);

    // Second Queue (RR, TQ = 8)
    Process queue3[MAX];
    int q3_size = 0;
    if (q2_size > 0) {
        round_robin(queue2, &q2_size, 8, &time, 2, queue3, &q3_size);
    }

    // Third Queue (FCFS)
    if (q3_size > 0) {
        fcfs(queue3, &q3_size, &time);
    }

    // Calculate AWT and ATAT only for completed processes
    float total_wt = 0, total_tat = 0;
    int completed_processes = 0;

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < initial_n; i++) {
        if (processes[i].completion_time > 0) {  // Process is completed
            total_wt += processes[i].waiting_time;
            total_tat += processes[i].turnaround_time;
            printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
            completed_processes++;
        }
    }

    // Prevent division by zero when calculating averages
    if (completed_processes > 0) {
        printf("\nAverage Waiting Time: %.2f", total_wt / completed_processes);
        printf("\nAverage Turnaround Time: %.2f\n", total_tat / completed_processes);
    } else {
        printf("\nNo processes completed.\n");
    }
}

// Main function
int main() {
    // Sample Data
    Process sample_data[] = {
        {0, 1, 3, 3, 0, 0, 0},
        {1, 3, 6, 6, 0, 0, 0},
        {2, 5, 8, 8, 0, 0, 0},
        {3, 7, 4, 4, 0, 0, 0},
        {4, 8, 5, 5, 0, 0, 0}
    };
    int sample_n = 5;

    printf("=== Sample Data Execution ===\n");
    execute_mlfq(sample_data, sample_n);

    // User Input
    int n;
    printf("\n\nEnter the number of processes: ");
    scanf("%d", &n);

    Process user_p[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        user_p[i].id = i;
        printf("Process %d: ", i);
        scanf("%d %d", &user_p[i].arrival_time, &user_p[i].burst_time);
        user_p[i].remaining_time = user_p[i].burst_time;
    }

    printf("\n=== User Input Execution ===\n");
    execute_mlfq(user_p, n);

    return 0;
}
