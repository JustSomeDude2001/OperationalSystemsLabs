/**
 * Simple Pyramid Drawer.
 */
#include <stdio.h>

#define BUFFER_SIZE 4096

void layerPrinter(int offset,
                  int bodySize) {
    
    for (int i = 0; i < offset; i++) {
        putc(' ', stdout);
    }

    for (int i = 0; i < bodySize; i++) {
        putc('*', stdout);
    }

    putc('\n', stdout);
}

void figurePrinter(int height,
                   int initialOffset,
                   int offsetChange,
                   int initialWidth,
                   int widthChange) {

    int curWidth = initialWidth;
    int curOffset = initialOffset;

    for (int i = 0; i < height; i++) {
        layerPrinter(curOffset, curWidth);
        
        curOffset += offsetChange;
        curWidth += widthChange;
    }
}

void userInteractor(int argc, char *args[]) {
    int n = -1;
    
    if (argc < 2) {
        fputs("Bad Input. Please input at least 1 positive integer.\n", stdout);
        return;
    }

    sscanf(args[1], "%d", &n);

    if (n <= 0) {
        fputs("Bad Input. Please only input positive integers.\n", stdout);
        return;
    }

    figurePrinter(n, n, -1, 1, +2);
}

int main(int argc, char *args[]) {
    userInteractor(argc, args);
}