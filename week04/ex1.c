#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <string.h>
#include <memory.h>

#define BUFFER_SIZE 4096

int main() {

    pid_t rootPID = -1;
    pid_t selfPID;

    int var = 10;

    selfPID = getpid();

    if (rootPID == -1) {
        rootPID = selfPID;
    }

    if (selfPID == rootPID) {
        printf("I am root! My PID is %d. var is %d\n", selfPID, var);
        
        wait(NULL);

        fork();
    } 
    
    selfPID = getpid();

    if (selfPID != rootPID) {
        printf("I am child! My PID is %d. var is %d\n", selfPID, var);
    }
}