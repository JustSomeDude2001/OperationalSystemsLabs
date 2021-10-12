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

    int* ptr;
    int sz = 100 * 1024 * 1024;

    for (int i = 0; i < 10; i++) {
        ptr = malloc(sz);
        memset(ptr, 0, sz);
        sleep(1);
        //free(ptr);
    }

    printf("Done\n");
}

/**
 * EX2
 * Unfortunately, my system was unable to track the changes in the swap sizes.
 * 
 * However, significant changes in the amount of free memory were noted when 
 * memory is not freed.
 * 
 * EX3
 * When memory was not freed, ex2's memory usage grown every 10 seconds.
 * When freed, the memory usage was stable.
 */
