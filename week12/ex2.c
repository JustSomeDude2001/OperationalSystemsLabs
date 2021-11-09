#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>     
#include <memory.h>

#include <dirent.h>
#include "/usr/include/linux/input.h" 

#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define BUFFER_SIZE 4096

int main() {
    int input = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    FILE *output =  fopen("ex2.txt", "w");

    if (input == -1) {
        printf("Failed to open");
        return 0;
    }

    //no read block.
    fcntl(input, F_SETFL, 0);

    struct input_event ie;

    while (1) {
        int sizeofRed;
        if (read(input, (void*) &ie, sizeof(struct input_event)) < sizeof(struct input_event)) {
            continue;
        }
        if (ie.value == EV_KEY) {
            fprintf(output, "PRESSED - %x (%d)\n", ie.code, ie.code);
            fflush(output);
        }
    }
}