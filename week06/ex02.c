#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>             
#include <memory.h>

#define BUFFER_SIZE 4096

struct Process {
    int pID;
    
    int arrivalTime;
    int burstTime;

    int completionTime;
    int turnaroundTime;
    int waitingTime;
    float averageTurnoaroundTime;
    float averageWaitingTime;
};

// Process printing method
void printProcess(struct Process *target) {
    printf("pID: %d     aT: %d      bT:%d       cT:%d       tT:%d       wT:%d       avTT:%f         avWT:%f\n", 
           target -> pID, target -> arrivalTime, target -> burstTime, target -> completionTime, target -> turnaroundTime,
           target -> waitingTime, target -> averageTurnoaroundTime, target -> averageWaitingTime);
}

// Process scanning method
void scanProcess(struct Process *target) {
    static int globalPID = 0;
    printf("Scanning PID %d\n:", globalPID);

    target -> pID = globalPID;
    globalPID++;

    printf("Please, input arrival time and burst time (all integers in clock cycles):\n");
    scanf("%d%d", &(target -> arrivalTime), &(target -> burstTime));
}

// Comparator for qsort
int arrivalTimeComp(const struct Process *A, const struct Process *B) {
    if ((A) -> arrivalTime !=
        (B) -> arrivalTime)
        return (A) -> arrivalTime - 
               (B) -> arrivalTime;
    else 
        return (A) -> burstTime - 
               (B) -> burstTime;
}

// Shortest job first implementation.
void sjf(struct Process *processes, int n) {

    qsort (processes, n, sizeof(struct Process), &arrivalTimeComp);

    int currentTime = 0;

    // Neighborhood borders describe processes coming at the same time.
    int neighborhoodBorderLeft = 0;
    int neighborhoodBorderRight = 1;

    float neighborhoodSum = 0.0;

    int neighborhoodValue = -1;

    int neighborhoodGlobalWT = 0;

    float neighborhoodSize = neighborhoodBorderRight - neighborhoodBorderLeft;

    for (int i = 0; i < n; i++) {
        struct Process *current = processes + i;

        // If process comes at a busy time - add to its waiting time
        if (currentTime >= current -> arrivalTime) {
            current -> waitingTime = currentTime - current -> arrivalTime;
        } else {
            currentTime = current -> arrivalTime;
            current -> waitingTime = 0;
        }

        // If we start checking a process coming at a new time, update neighborhood.
        if (current -> arrivalTime != neighborhoodValue) {
            while((processes + neighborhoodBorderLeft) -> arrivalTime != current -> arrivalTime) {
                neighborhoodGlobalWT += processes -> burstTime;
                neighborhoodBorderLeft++;
            }
            
            neighborhoodBorderRight = neighborhoodBorderLeft + 1;

            while(neighborhoodBorderRight < n && (processes + neighborhoodBorderRight) -> arrivalTime == current -> arrivalTime) {
                neighborhoodBorderRight++;
            }

            neighborhoodSum = 0.0;

            for (int j = neighborhoodBorderLeft; j < neighborhoodBorderRight; j++) {
                neighborhoodSum += (processes + j) -> burstTime;
            }

            neighborhoodValue = current -> arrivalTime;
            neighborhoodSize = neighborhoodBorderRight - neighborhoodBorderLeft;
        }
        
        // Calculate average waiting time based on the total burst time of the neighborhood.
        current -> averageWaitingTime = (float)(neighborhoodSum - (current -> burstTime)) / 
                                        (neighborhoodSize) + neighborhoodGlobalWT;

        // Calculate average turnaround time on average waiting time
        current -> averageTurnoaroundTime = current -> averageWaitingTime + current -> burstTime;

        // Update current time
        currentTime += current -> burstTime;

        //Handle trivial cases of current time and turnaround time
        current -> completionTime = currentTime;

        current -> turnaroundTime = currentTime - current -> arrivalTime;
    }
}

int main() {
    printf("Input amount of processes");
    int n;
    scanf("%d", &n);
    
    struct Process *procs = malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        scanProcess(procs + i);
    }   

    sjf(procs, n);

    for (int i = 0; i < n; i++) {
        printProcess(procs + i);
    }

}