#include <stdio.h>

typedef struct {
    int id, arrival_time, burst_time, waiting_time, turnaround_time, completed;
} Process;

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

void hrrn_scheduling(Process p[], int n) {
    int completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0;

    // Sort by arrival time
    sort_by_arrival(p, n);

    printf("\nExecution Order:\n");

    while (completed < n) {
        int selected = -1;
        float max_response_ratio = -1.0;

        for (int i = 0; i < n; i++) {
            if (p[i].completed == 0 && p[i].arrival_time <= current_time) {
                int waiting_time = current_time - p[i].arrival_time;
                float response_ratio = (waiting_time + p[i].burst_time) / (float)p[i].burst_time;

                if (response_ratio > max_response_ratio) {
                    max_response_ratio = response_ratio;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            p[selected].waiting_time = current_time - p[selected].arrival_time;
            p[selected].turnaround_time = p[selected].waiting_time + p[selected].burst_time;
            total_wt += p[selected].waiting_time;
            total_tat += p[selected].turnaround_time;

            current_time += p[selected].burst_time;
            p[selected].completed = 1;
            completed++;

            printf("P%d -> ", p[selected].id - 1);
        }
    }

    printf("END\n");

    // Display process details
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id - 1, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    // Sample Data
    Process sample_data[] = {
        {1, 1, 3, 0, 0, 0},
        {2, 3, 6, 0, 0, 0},
        {3, 5, 8, 0, 0, 0},
        {4, 7, 4, 0, 0, 0},
        {5, 8, 5, 0, 0, 0}
    };
    int sample_n = 5;

    printf("=== Sample Data Execution ===\n");
    hrrn_scheduling(sample_data, sample_n);

    // User Input
    int n;
    printf("\n\nEnter the number of processes: ");
    scanf("%d", &n);

    Process user_p[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        user_p[i].id = i + 1;
        printf("Process %d: ", i);
        scanf("%d %d", &user_p[i].arrival_time, &user_p[i].burst_time);
        user_p[i].completed = 0;
    }

    printf("\n=== User Input Execution ===\n");
    hrrn_scheduling(user_p, n);

    return 0;
}
