//Kevin Siraki
//Bankers Algorithm Simulation
#include <stdio.h>
#include <stdlib.h>
int *resource = NULL;
int *available = NULL;
int *max_claims = NULL;
int *allocation = NULL;
int *need = NULL;
int num_processes;
int num_resources;

void resources() {
	int i;
	printf("\nResources: \n");
	for (i = 0; i < num_resources; i++) printf("\tr%d", i);
	printf("\n");
	for (i = 0; i < num_resources; i++) printf("\t%d", resource[i]);
	printf("\n");
	return;
}

void availability() {
	int i;
	printf("\nAvailable:\n");
	for (i = 0; i < num_resources; i++) printf("\tr%d", i);
	printf("\n");
	for (i = 0; i < num_resources; i++) printf("\t%d", available[i]);
	printf("\n");
	printf("\nAllocated resources:\n");
	for (i = 0; i < num_resources; i++) printf("\tr%d", i);
	printf("\n");
	for (i = 0; i < num_resources; i++) printf("\t%d", resource[i] - available[i]);
	printf("\n");
	return;
}

void claimMax() {
	int i, j;
	printf("\nMax claims: \n");
	for (i = 0; i < num_resources; i++) printf("\tr%d", i);
	printf("\n");
	for (i = 0; i < num_processes; i++)
	{
		printf("p%d\t", i);
		for (j = 0; j < num_resources; j++) printf("%d\t", max_claims[i * num_resources + j]);
		printf("\n");
	}
	return;
}

void allocationFunc() {
	int i, j;
	printf("\nAllocation: \n");
	for (i = 0; i < num_resources; i++) printf("\tr%d", i);
	printf("\n");
	for (i = 0; i < num_processes; i++)
	{
		printf("p%d\t", i);
		for (j = 0; j < num_resources; j++) printf("%d\t", allocation[i * num_resources + j]);
		printf("\n");
	}
	return;
}

void needCalc() {
	int i, j;
	printf("\nNeed: \n");
	for (i = 0; i < num_resources; i++) printf("\tr%d", i);
	printf("\n");
	for (i = 0; i < num_processes; i++)
	{
		printf("p%d\t", i);
		for (j = 0; j < num_resources; j++) printf("%d\t", need[i * num_resources + j]);
		printf("\n");
	}
	return;
}

void inputParams() {
	int i, j, units;
	printf("Enter number of processes: ");
	scanf("%d", &num_processes);
	printf("Enter number of resources: ");
	scanf("%d", &num_resources);
	resource = (int *)malloc(num_resources * sizeof(int));
	available = (int *)malloc(num_resources * sizeof(int));
	max_claims = (int *)malloc(num_processes * num_resources * sizeof(int));
	allocation = (int *)malloc(num_processes * num_resources * sizeof(int));
	need = (int *)malloc(num_processes * num_resources * sizeof(int));
	printf("Enter number of units for resources: (r0 to r%d): ", num_resources - 1);
	for (i = 0; i < num_resources; i++) {
		scanf("%d", &units);
		resource[i] = units;
		available[i] = units;
	}
	for (i = 0; i < num_processes; i++) {
		printf("Enter maximum number of units process p%d will request from each resource: (r0 to r%d): ", i, num_resources - 1);
		for (j = 0; j < num_resources; j++) {
			scanf("%d", &units);
			max_claims[i * num_resources + j] = units;
			need[i * num_resources + j] = units;
		}
	}
	for (i = 0; i < num_processes; i++) {
		printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d: ", num_resources - 1, i);
		for (j = 0; j < num_resources; j++) {
			scanf("%d", &units);
			allocation[i * num_resources + j] = units;
			available[j] -= units;
			need[i * num_resources + j] -= units;
		}
	}
	resources();
	availability();
	claimMax();
	allocationFunc();
	needCalc();
	return;
}

void checkSafety()
{
	int i, j;
	int less_than;
	int num_sequenced = 0;
	int *safe = (int *)calloc(num_processes, sizeof(int));
	while (num_sequenced < num_processes) {
		for (i = 0; i < num_processes; i++) {
			less_than = 1;
			if (safe[i] == 0) {
				for (j = 0; j < num_resources; j++) less_than &= (need[i * num_resources + j] <= available[j]);
				printf("\nChecking: < ");
				for (j = 0; j < num_resources; j++) printf("%d ", need[i * num_resources + j]);
				printf("> <= < ");
				for (j = 0; j < num_resources; j++) printf("%d ", available[j]);
				printf("> ");
				if (less_than == 1) {
					for (j = 0; j < num_resources; j++) {
						available[j] += allocation[i * num_resources + j];
						allocation[i * num_resources + j] = 0;
					} 
					printf(":p[%d] safely sequenced", i);
					num_sequenced++;
					safe[i] = 1;
				} 
			}	  
		}		  
	}			  
	return;
}

void deallocate() {
	if (resource != NULL) free(resource);
	if (available != NULL) free(available);
	if (max_claims != NULL) free(max_claims);
	if (allocation != NULL) free(allocation);
	if (need != NULL) free(need);
	return;
}

int main()
{
	int input = 0;
	while (input < 3)
	{
		printf("\nBanker's Algorithm");
		printf("\n___________________\n");
		printf("1) Enter parameters\n");
		printf("2) Determine safe sequence\n");
		printf("3) Quit program\n");
		printf("\nEnter Selection: ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			inputParams();
			break;
		case 2:
			checkSafety();
			break;
		default:
			deallocate();
			break;
		} 
	}
	return 1;
}
