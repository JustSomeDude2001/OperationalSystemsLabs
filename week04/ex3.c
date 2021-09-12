#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <string.h>
#include <memory.h>

#define BUFFER_SIZE 4096

int main() {
    char *nextCommand = malloc(BUFFER_SIZE * sizeof(char));
    while (1) {
        scanf("%4096s", nextCommand);
        system(nextCommand);
    }
}