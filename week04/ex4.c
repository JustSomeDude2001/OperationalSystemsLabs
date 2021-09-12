#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <string.h>
#include <memory.h>

#include <errno.h>

#define BUFFER_SIZE 4096

void toArgv(char *str, char **targetLocation, char *delimiters) {
    int argCnt = 0;
    char *curArg = strtok(str, delimiters);

    while (curArg != NULL) {
        targetLocation[argCnt] = curArg;

        curArg = strtok(NULL, delimiters);
        
        argCnt++;
    }
}

void cleanUp(char **strs) {
    char *curString = strs;
    while (curString) {
        free(curString);
        curString++;
    }
}

int main() {
    char *nextCommand = malloc(BUFFER_SIZE * sizeof(char));

    while (1) {
        fgets(nextCommand, BUFFER_SIZE, stdin);
        
        char **argv = malloc(BUFFER_SIZE * sizeof(char*));

        toArgv(nextCommand, argv, "\n ");

        pid_t curPID = fork();

        if (curPID == 0) {
            execvp(argv[0], argv);

            cleanUp(argv);
        }
    }
}