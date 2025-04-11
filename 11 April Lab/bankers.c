#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int P, R;
    int total[MAX_R], available[MAX_R];
    int allocation[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
    int request[MAX_R];
    int safeSeq[MAX_P];

    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    printf("Enter total resources of each type (space-separated):\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &total[i]);

    printf("Enter allocation matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter maximum matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter currently available resources of each type:\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    char choice;
    printf("Do you want to simulate a request from a process? (y/n): ");
    scanf(" %c", &choice);
    int reqP = -1;

    if (choice == 'y' || choice == 'Y') {
        printf("Enter process number (0 to %d): ", P - 1);
        scanf("%d", &reqP);
        printf("Enter request vector of %d values:\n", R);
        for (int i = 0; i < R; i++) {
            scanf("%d", &request[i]);
            if (request[i] > need[reqP][i]) {
                printf("Error: Request exceeds process max need.\n");
                return 1;
            }
            if (request[i] > available[i]) {
                printf("Resources not available. Request can't be granted now.\n");
                return 1;
            }
        }

        for (int i = 0; i < R; i++) {
            available[i] -= request[i];
            allocation[reqP][i] += request[i];
            need[reqP][i] -= request[i];
        }
    }

    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int count = 0;

    for (int i = 0; i < R; i++) work[i] = available[i];

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 1;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
