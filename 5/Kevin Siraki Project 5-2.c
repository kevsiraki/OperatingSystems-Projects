//Kevin Siraki 
//Project 5
//COMP 322

#include<stdio.h>

void bestFit() {
    int fragment[20], b[20], p[20], i, j, nb, np, tem, low = 9999;
    static int barray[20], parray[20];
    printf("Best Fit\n");
    printf("Enter the number of processes:");
    scanf("%d", & np);
    printf("\nEnter the number of blocks:");
    scanf("%d", & nb);
    printf("\nEnter the size of the blocks:-\n");
    for (i = 1; i <= nb; i++) {
        printf("Block no.%d:", i);
        scanf("%d", & b[i]);
    }
    printf("\nEnter the size of the processes :-\n");
    for (i = 1; i <= np; i++) {

        printf("Process no.%d:", i);

        scanf("%d", & p[i]);
    }
    for (i = 1; i <= np; i++) {
        for (j = 1; j <= nb; j++) {

            if (barray[j] != 1) {
                tem = b[j] - p[i];
                if (tem >= 0)
                    if (low > tem) {
                        parray[i] = j;
                        low = tem;
                    }
            }
        }
        fragment[i] = low;
        barray[parray[i]] = 1;
        low = 10000;
    }
    printf("\nProcess_number \tProcess_size\tBlock_number \tBlock_size\tFragment");
    for (i = 1; i <= np && parray[i] != 0; i++)

        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, p[i], parray[i], b[parray[i]], fragment[i]);
    printf("\n");
}

void firstFit() {
    printf("First Fit\n");
    int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j;
    for (i = 0; i < 10; i++) {
        flags[i] = 0;
        allocation[i] = -1;
    }
    printf("Enter no. of blocks: ");
    scanf("%d", & bno);
    printf("\nEnter size of each block: ");
    for (i = 0; i < bno; i++)
        scanf("%d", & bsize[i]);

    printf("\nEnter no. of processes: ");
    scanf("%d", & pno);
    printf("\nEnter size of each process: ");
    for (i = 0; i < pno; i++)
        scanf("%d", & psize[i]);
    for (i = 0; i < pno; i++) //allocation as per first fit
        for (j = 0; j < bno; j++)
            if (flags[j] == 0 && bsize[j] >= psize[i]) {
                allocation[j] = i;
                flags[j] = 1;
                break;
            }
    printf("\nBlock no.\tsize\t\tprocess no.\t\tsize");
    for (i = 0; i < bno; i++) {
        printf("\n%d\t\t%d\t\t", i + 1, bsize[i]);
        if (flags[i] == 1)
            printf("%d\t\t\t%d", allocation[i] + 1, psize[allocation[i]]);
        else
            printf("Not allocated");
    }
    printf("\n");
}

void nextFit() {
    printf("Next Fit\n");
    int memory_size[10][2], process_size[10][3];
    int i, j=0, total_processes = 0, total_memory = 0;
    printf("\nEnter the Total Number of Processes: ");
    scanf("%d", & total_processes);
    printf("\nEnter the Size of Each Process\n");
    for (int i = 0; i < total_processes; i++) {
        printf("Enter Size of Process %d: ", i + 1);
        scanf("%d", & process_size[i][0]);
        process_size[i][1] = 0;
        process_size[i][2] = i;
    }
    printf("\nEnter no. of memory partitions: ");
    scanf("%d", & total_memory);
    printf("\nEnter the size of each partition:\n");
    for (i = 0; i < total_processes; i++) {
        printf("Enter size of partition %d: ", i + 1);
        scanf("%d", & memory_size[i][0]);
        memory_size[i][1] = 0;
    }
    for (i = 0; i < total_processes; i++) {
        while (j < total_memory) {
            if (memory_size[j][1] == 0 && process_size[i][0] <= memory_size[j][0]) {
                process_size[i][1] = 1;
                memory_size[j][1] = 1;
                printf(" Process [%d] Allocated to Memory Block: %d\n", i + 1, j + 1);
                break;
            }
            j++;
        }
    }
    for (i = 0; i < total_memory; i++) {
        if (process_size[i][1] == 0) {
            printf(" Process [%d] Unallocated\n", i + 1);
        }
    }
    printf("\n");
}

void worstFit() {
    printf("Worst Fit\n");
    int fragments[10], blocks[10], Processs[10];
    int m, n, number_of_blocks, number_of_Processs, temp, top = 0;
    static int block_arr[10], Process_arr[10];
    printf("\nEnter the Total Number of Blocks:\t");
    scanf("%d", & number_of_blocks);
    printf("Enter the Total Number of Processs:\t");
    scanf("%d", & number_of_Processs);
    printf("\nEnter the Size of the Blocks:\n");
    for (m = 0; m < number_of_blocks; m++) {
        printf("Block No.[%d]:\t", m + 1);
        scanf("%d", & blocks[m]);
    }
    printf("Enter the Size of the Processs:\n");
    for (m = 0; m < number_of_Processs; m++) {
        printf("Process No.[%d]:\t", m + 1);
        scanf("%d", & Processs[m]);
    }
    for (m = 0; m < number_of_Processs; m++) {
        for (n = 0; n < number_of_blocks; n++) {
            if (block_arr[n] != 1) {
                temp = blocks[n] - Processs[m];
                if (temp >= 0) {
                    if (top < temp) {
                        Process_arr[m] = n;
                        top = temp;
                    }
                }
            }
            fragments[m] = top;
            block_arr[Process_arr[m]] = 1;
            top = 0;
        }
    }
    printf("\nProcess Number\tProcess Size\tBlock Number\tBlock Size\tFragment");
    for (m = 0; m < number_of_Processs; m++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", m, Processs[m], Process_arr[m], blocks[Process_arr[m]], fragments[m]);
    }
    printf("\n");
}

int main() {
    int choice;
    do {
        printf("Select an algorithm.\n1. Best Fit\n2. First Fit\n3. Next Fit\n4. Worst Fit\n5. Exit\nChoice: ");
        scanf("%d", & choice);
        switch (choice) {
        case 1:
            bestFit();
            break;
        case 2:
            firstFit();
            break;
        case 3:
            nextFit();
            break;
        case 4:
            worstFit();
            break;
        case 5:
            printf("Goodbye.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }

    } while (choice != 5);
    return 0;
}
