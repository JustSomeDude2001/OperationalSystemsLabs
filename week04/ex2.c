#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <string.h>
#include <memory.h>

#define BUFFER_SIZE 4096

int main() {
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            printf("rootPID is %d", fork());
        } else {
            fork();
        }
        sleep(5);
    }
}