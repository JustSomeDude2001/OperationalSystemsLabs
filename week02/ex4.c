#include <stdio.h>

#define BUFFER_SIZE 4096

void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}

void userInteractor() {
    int a, b;
    fputs("Please input 2 integers separated by space.\n", stdout);

    scanf("%d%d", &a, &b);

    swap(&a, &b);

    fputs("Integers swapped. \n", stdout);

    printf("%d %d", a, b);
}

int main() {
    userInteractor();
}