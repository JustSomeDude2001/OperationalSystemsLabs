#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>             
#include <memory.h>

#define BUFFER_SIZE 4096

int main() {
    int n;

    printf("Please input a positive integer.");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(n));

    for (int i = 0; i < n; i++) {
        *(a + i) = i;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", *(a + i));
    }

    free(a);
}