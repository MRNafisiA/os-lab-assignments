#include<stdio.h>

void fcfs(int *bt, int *p, int i, int j, int n, int pos, int temp);

void sjf(int *bt, int *p, int i, int j, int n, int pos, int temp);

void priorityScheduling(int *bt, int *p, int *pr, int n);

void roundRobinScheduling(int *bt);

void shortestRemainingTime(int *bt, int n);

int main() {
    int bt[20], p[20], pr[20], i, n;
    printf("Enter number of process:");
    scanf("%d", &n);

    printf("\nEnter Burst Time and priority:\n");
    for (i = 0; i < n; i++) {
        printf("p%d:", i + 1);
        scanf("%d", &bt[i]);
        printf("p priority%d:", i + 1);
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }
//    sjf(bt, p, i, j, n, pos, temp);

}

void fcfs(int *bt, int *p, int i, int j, int n, int pos, int temp) {
    // do nothing
}

void sjf(int *bt, int *p, int i, int j, int n, int pos, int temp) {
    //sorting of burst times
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
                pos = j;
        }

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
}

void priorityScheduling(int *bt, int *p, int *pr, int n) {
    int pos, temp;
    for (int i = 0; i < n; i++) {
        pos = i;
        for (int j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos])
                pos = j;
        }

        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
}

void roundRobinScheduling(int *bt) {
    int limit;
    scanf("%d", &limit);
    int x = limit;
    int time_quantum;
    scanf("%d", &time_quantum);
    int counter = 0;
    for (int total = 0, i = 0; x != 0;) {
        if (bt[i] <= time_quantum && bt[i] > 0) {
            total = total + bt[i];
            bt[i] = 0;
            counter = 1;
        } else if (bt[i] > 0) {
            bt[i] = bt[i] -
                    time_quantum;
            total = total + time_quantum;
        }
        if (bt[i] == 0 && counter == 1) {
            x--;
            counter = 0;
        }
        if (i == limit - 1) {
            i = 0;
        } else {
            i = 0;
        }
    }
}

void shortestRemainingTime(int *bt, int n) {
    int x[20], count = 0, smallest, end;
    for (int i = 0; i < n; i++) {
        x[i] = bt[i];
    }

    bt[19] = 9999;
    for (int time = 0; count != n; time++) {
        smallest = 9;
        for (int i = 0; i < n; i++) {
            if (bt[i] <= time && bt[i] < bt[smallest] && bt[i] > 0)
                smallest = i;
        }
        bt[smallest]--;

        if (bt[smallest] == 0) {
            count++;
            end = time + 1;
        }
    }
}