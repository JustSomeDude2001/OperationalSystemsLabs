#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>     
#include <memory.h>

#define BUFFER_SIZE 4096

int canRelease(int **alloc_matrix, int **reqst_matrix, 
               int *ex_resources, int *av_resources, int *released, 
               int n, int m, int target) {
    
    //catch out of bounds case.
    if (target >= n) {
        return 0;
    }

    if (released[target]) {
        return 0;
    }

    int hasToRelease = 0;

    for (int i = 0; i < m; i++) {
        int req = reqst_matrix[target][i] - alloc_matrix[target][i];
        
        if (req > av_resources[i]) {
            return 0;
        }
    }

    return 1;
}

void release(int **alloc_matrix, int **reqst_matrix, 
             int *ex_resources, int *av_resources, int *released,
             int n, int m, int target) {

    //catch out of bounds case.
    if (target >= n) {
        return;
    }

    for (int i = 0; i < m; i++) {
        av_resources[i] += alloc_matrix[target][i];
        alloc_matrix[target][i] = 0;
        reqst_matrix[target][i] = 0;
    }

    released[target] = 1;
}

void solution(int **alloc_matrix, int **reqst_matrix, 
              int *ex_resources, int *av_resources, int *released,
              int n, int m) {

    int releasedLastIter = 1;
    while(releasedLastIter) {
        releasedLastIter = 0;
        for (int i = 0; i < n; i++) {
            if (canRelease(alloc_matrix, reqst_matrix,
                           ex_resources, av_resources, released, n, m, i)) {
                
                release(alloc_matrix, reqst_matrix, ex_resources, av_resources, released, n, m, i);
                releasedLastIter = 1;
            }
        }
    }
}

int main() {
    FILE *input = fopen("input.txt", "rw");

    int n, m;
    fscanf(input, "%d%d", &n, &m);

    int *ex_resources = calloc(m, sizeof(int));
    int *av_resources = calloc(m, sizeof(int));

    int **alloc_matrix = calloc(n, sizeof(int*));
    int **reqst_matrix = calloc(n, sizeof(int*));

    int *released = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        alloc_matrix[i] = calloc(m, sizeof(int));
        reqst_matrix[i] = calloc(m, sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        fscanf(input, "%d", &ex_resources[i]);
    }

    for (int i = 0; i < m; i++) {
        fscanf(input, "%d", &av_resources[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(input, "%d", &alloc_matrix[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(input, "%d", &reqst_matrix[i][j]);
        }
    }

    solution(alloc_matrix, reqst_matrix, ex_resources, av_resources, released, n, m);

    int unreleased = 0;

    for (int i = 0; i < n; i++) {
        if (!released[i]) {
            unreleased++;
        }
    }

    if (unreleased == 0) {
        printf("All processes finished and released resources.");
        return 0;
    }

    printf("Some processes unreleased.\n");

    for (int i = 0; i < n; i++) {
        if (released[i] == 0) {
            printf("Process number %d is deadlocked.\n", i);
        }
    }
}