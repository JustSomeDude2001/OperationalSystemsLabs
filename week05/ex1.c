#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>
#include <memory.h>


#define BUFFER_SIZE 4096

void *threadedFunction(void *args) {
    printf("Hello from thread %d\n", *((int*)args));
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pthread_t thread_id;
        
        printf("Creating thread...\n");

        pthread_create(&thread_id, NULL, threadedFunction, &i);

        pthread_join(thread_id, NULL);
    }
}