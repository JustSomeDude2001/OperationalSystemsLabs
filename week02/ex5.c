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
    int n;
    int figureType = 0;

    if (argc < 2) {
        fputs("Bad Input. Please input at least 1 positive integer.\n", stdout);
        return;
    }

    if (argc < 3) {
        fputs("Figure type not specified. Defaulting to pyramid.\n", stdout);
    }

    sscanf(args[1], "%d", &n);

    if (argc > 2) {
        sscanf(args[2], "%d", &figureType);
        if (figureType < 0 || figureType > 3) {
            fputs("Figure type is limited in [0, 3]. As bad type was specified, defaulting to pyramid.\n", stdout);
            figureType = 0;
        }
    }

    if (n <= 0) {
        fputs("Bad Input. Please only input positive integers.\n", stdout);
        return;
    }

    switch (figureType)
    {
    case 0: //pyramid
        figurePrinter(n, n, -1, 1, +2);
        break;
    case 1: //right triangle
        figurePrinter(n, 0, 0, 1, 1);
        break;
    case 2: //right-hand arrow
        figurePrinter(n / 2, 0, 0, 1, +1);
        figurePrinter(n / 2 + (n % 2), 0, 0, n / 2 + (n % 2), -1);
        break;
    case 3: //block
        figurePrinter(n, 0, 0, n, 0);
        break;
    default:
        //impossible case. Handled before switch.
        break;
    }

}

int main(int argc, char *args[]) {
    userInteractor(argc, args);
}