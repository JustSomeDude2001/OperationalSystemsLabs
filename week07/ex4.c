#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>             
#include <memory.h>

#define BUFFER_SIZE 4096

int* myRealloc(int* ptr, size_t oldsize, size_t newsize) {
    int* newptr = malloc(newsize);
    
    if (oldsize > newsize)
        memcpy(newptr, ptr, newsize);
    else
        memcpy(newptr, ptr, oldsize);

    free(ptr);
    return newptr;
}

int main() {
    int n;
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = 1;
    }

    int nnew;
    scanf("%d", &nnew);

    a = myRealloc(a, n * sizeof(int), nnew * sizeof(int));


    for (int i = 0; i < nnew; i++) {
        a[i] = 2;
        printf("%d ", a[i]);
    }
}