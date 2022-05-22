//Kevin Siraki
#include <stdio.h>
#include <stdlib.h>

struct node {
    int arrivalTime;
    int serviceTime;
    int initialtime;
    int finishtime;
    int turnarounTime;
    int waitingTime;
    int postion;
}* ptr = NULL;

typedef struct node node1;

int getNumber();
void FIFO(int);
void SJF(int);
void SRT(int);

int main() {
    int numProcesses;
    int choice = 0;
    while (choice != 4) {
        printf("\n1-FIFO\n2-SJF \n3-SRT\n4-Exit\nSelection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                numProcesses = getNumber();
                FIFO(numProcesses);
                break;
            case 2:
                numProcesses = getNumber();
                SJF(numProcesses);
                break;
            case 3:
                numProcesses = getNumber();
                SRT(numProcesses);
                break;
            case 4:
                printf("Goodbye!");
                break;
            default:
                printf("INVALID CHOICE");
                break;
        }
    }
    return 0;
}


int getNumber() {
    int numProcess;
    printf("\nPlease Enter the total number of processes:\n");
    scanf("%d", & numProcess);
    printf("\n");
    for (int i = 0; i < numProcess; i++) ptr = (node1 * ) malloc(numProcess * sizeof(node1));

    for (int i = 0; i < numProcess; i++) {
        printf("Please enter the arrival time of process %d", i + 1);
        printf(":\n");
        scanf("%d", & ptr[i].arrivalTime);
        printf("Please Enter the service time %d", i + 1);
        printf(":\n");
        scanf("%d", & ptr[i].serviceTime);
        ptr[i].waitingTime = 0;
        ptr[i].postion = i;
    }
    return numProcess;
}

void FIFO(int numProcessescess) {
    int total = 0;
    int tmp[numProcessescess];
    int pid[numProcessescess];
    tmp[0] = 0;
    for (int i = 1; i < numProcessescess; i++) {
        pid[i] = ptr[i].postion;
        tmp[i] = tmp[i - 1] + ptr[i - 1].serviceTime;
        ptr[i].waitingTime = tmp[i] - ptr[i].arrivalTime;
        if (ptr[i].waitingTime < 0)
            ptr[i].waitingTime = 0;
    }
    for (int i = 0; i < numProcessescess; i++)
        ptr[i].turnarounTime = ptr[i].serviceTime + ptr[i].waitingTime;

    for (int i = 0; i < numProcessescess; i++)
        total += ptr[i].turnarounTime;

    printf("Average turn-around time: \n");
    printf("%d", total);
    printf("\n");
    printf("Total average: \n");
    printf("%d", total / numProcessescess);
}

void SJF(int n) {
    struct node node1;
    int i;
    int j;
    int min;
    int avgturntime = 0;
    int avgwaiting = 0;
    int p[n];
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (ptr[i].arrivalTime > ptr[j].arrivalTime) {
                node1 = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = node1;
            }
        }
    }
    min = 0;
    j = 1;
    while (j < n && ptr[j].arrivalTime == ptr[0].arrivalTime) {
        if (ptr[j].serviceTime < ptr[min].serviceTime)
            min = j;
        j++;
    }
    node1 = ptr[0];
    ptr[0] = ptr[min];
    ptr[min] = node1;
    for (i = 1; i < n; i++) {
        min = i;
        j = i + 1;
        while (j < n && ptr[j].arrivalTime <= ptr[i - 1].finishtime) {
            if (ptr[j].serviceTime < ptr[min].serviceTime)
                min = j;
            j++;
        }
        node1 = ptr[i];
        ptr[i] = ptr[min];
        ptr[min] = node1;
    }
    for (i = 0; i < n; i++) {
        ptr[i].turnarounTime = ptr[i].finishtime - ptr[i].arrivalTime;
        ptr[i].waitingTime = ptr[i].turnarounTime - ptr[i].serviceTime;
        avgturntime += ptr[i].turnarounTime;
        avgwaiting += ptr[i].waitingTime;
        p[i] = i;
    }
    printf("Average turn-around time: \n");
    printf("%d", abs(avgturntime));
    printf("\n");
    printf("Total average: \n");
    printf("%d", abs(avgturntime / n));
}

void SRT(int numProcessescess) {
    float averageTurnAroundTime;
    int i;
    int j;
    int k = 0;
    int r = 0;
    int minimum;
    int temp;
    int procs[numProcessescess * 20], pid[numProcessescess];
    for (i = 0; i < numProcessescess; i++)
        r += ptr[i].serviceTime;
    for (i = 0; i < numProcessescess; i++) {
        for (j = i + 1; j < numProcessescess; j++) {
            if (ptr[i].arrivalTime > ptr[j].arrivalTime) {
                temp = ptr[i].arrivalTime;
                ptr[i].arrivalTime = ptr[j].arrivalTime;
                ptr[j].arrivalTime = temp;
                temp = ptr[i].serviceTime;
                ptr[i].serviceTime = ptr[j].serviceTime;
                ptr[j].serviceTime = temp;
            }
        }
    }
    for (i = 0; i < r; i++) {
        minimum = 3200;
        for (j = 0; j < numProcessescess; j++) {
            if ((ptr[j].serviceTime != 0) && (ptr[j].arrivalTime <= i) && (ptr[j].serviceTime < minimum)) {
                minimum = ptr[j].serviceTime;
                k = j;
            }
        }
        ptr[k].serviceTime--;
        procs[i] = k;
    }
    k = 0;
    for (i = 0; i < r; i++) {
        for (j = 0; j < numProcessescess; j++) {
            if (procs[i] == j) {
                ptr[j].finishtime = i;
                ptr[j].waitingTime++;
            }
        }
    }
    for (i = 0; i < numProcessescess; i++) {
        averageTurnAroundTime = averageTurnAroundTime + ((ptr[i].finishtime - ptr[i].arrivalTime) + 1);
        pid[i] = i + 1;
    }

    printf("Average turn-around time: \n");
    printf("%f", averageTurnAroundTime);
    printf("\n");
    printf("Total average: \n");
    printf("%f", averageTurnAroundTime / numProcessescess);
}