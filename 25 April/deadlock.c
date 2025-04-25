#include <stdio.h>

int main() {
    int i, j, k, n, m, count = 0;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0)
            break;
    }

    int deadlock = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            deadlock = 1;
            break;
        }
    }

    if (deadlock) {
        printf("\nDeadlock detected. \n");
        for (i = 0; i < n; i++)
            if (finish[i] == 0)
                printf("P%d ", i);
        printf("\n");
    } else {
        printf("\nNo deadlock detected. \n");
    }

    return 0;
}
