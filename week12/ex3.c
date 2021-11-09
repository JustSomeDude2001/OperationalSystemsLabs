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
    FILE *output =  fopen("ex3.txt", "w");

    if (input == -1) {
        printf("Failed to open");
        return 0;
    }

    //no read block.
    fcntl(input, F_SETFL, 0);

    struct input_event ie;

    int pressed[256];

    for (int i = 0; i < 256; i++) {
        pressed[i] = 0;
    }

    while (1) {
        int sizeofRed;
        if (read(input, (void*) &ie, sizeof(struct input_event)) < sizeof(struct input_event)) {
            continue;
        }

        if (ie.value == EV_KEY) {
            pressed[ie.code] = 1;
        }

        if (ie.value == EV_REL) {
            pressed[ie.code] = 0;
        }

        if (pressed[KEY_P] && pressed[KEY_E]) {
            fprintf(output, "I passed Exam!\n");
        }

        if (pressed[KEY_C] && pressed[KEY_A] && pressed[KEY_P]) {
            fprintf(output, "Get some cappuccino!\n");
        }

        if (pressed[KEY_Y] && pressed[KEY_O] && pressed[KEY_U]) {
            fprintf(output, "'YOU' custom shortcut\n");
        }

        fflush(output);

    }
}