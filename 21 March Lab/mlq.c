
#include <stdio.h>

#define MAX 100

typedef struct {
    int id, arrival_time, burst_time, completion_time;
    int waiting_time, turnaround_time;
} Process;

// Function to sort processes by arrival time (FCFS)
void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to execute processes in FCFS order
void execute_fcfs(Process queue[], int n, int *current_time) {
    for (int i = 0; i < n; i++) {
        if (*current_time < queue[i].arrival_time) {
            *current_time = queue[i].arrival_time;
        }
        queue[i].waiting_time = *current_time - queue[i].arrival_time;
        queue[i].completion_time = *current_time + queue[i].burst_time;
        queue[i].turnaround_time = queue[i].completion_time - queue[i].arrival_time;
        *current_time += queue[i].burst_time;

        printf("P%d -> ", queue[i].id);
    }
}

// Function to update the main process array after execution
void update_processes(Process processes[], int n, Process queue[], int queue_size) {
    for (int i = 0; i < queue_size; i++) {
        for (int j = 0; j < n; j++) {
            if (processes[j].id == queue[i].id) {
                processes[j] = queue[i]; // Update main process array
                break;
            }
        }
    }
}

void execute_mlq(Process processes[], int n) {
    Process queue1[MAX], queue2[MAX];
    int q1_size = 0, q2_size = 0;
    int current_time = 0;

    // Allocate processes to predefined queues
    for (int i = 0; i < n; i++) {
        if (processes[i].id == 0 || processes[i].id == 1 || processes[i].id == 4) {
            queue1[q1_size++] = processes[i];
        } else {
            queue2[q2_size++] = processes[i];
        }
    }

    // Sort both queues by arrival time
    sort_by_arrival(queue1, q1_size);
    sort_by_arrival(queue2, q2_size);

    // Execute Queue 1 (Higher Priority)
    printf("\nExecuting Queue 1 (Higher Priority, FCFS):\n");
    execute_fcfs(queue1, q1_size, &current_time);
    printf("END\n");

    // Update main process array after Queue 1 execution
    update_processes(processes, n, queue1, q1_size);

    // Execute Queue 2 (Lower Priority)
    printf("\nExecuting Queue 2 (Lower Priority, FCFS):\n");
    execute_fcfs(queue2, q2_size, &current_time);
    printf("END\n");

    // Update main process array after Queue 2 execution
    update_processes(processes, n, queue2, q2_size);

    // Calculate AWT and ATAT
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {

    // Sample Data
    Process sample_data[] = {
        {0, 1, 3, 0, 0, 0},
        {1, 3, 6, 0, 0, 0},
        {2, 5, 8, 0, 0, 0},
        {3, 7, 4, 0, 0, 0},
        {4, 8, 5, 0, 0, 0}
    };
    
    int sample_n = 5;

    printf("=== Sample Data Execution ===\n");
    execute_mlq(sample_data, sample_n);

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
        user_p[i].completion_time = 0;
        user_p[i].waiting_time = 0;
        user_p[i].turnaround_time = 0;
    }

    printf("\n=== User Input Execution ===\n");
    execute_mlq(user_p, n);

    return 0;
}
