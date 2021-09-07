#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <memory.h>

#define BUFFER_SIZE 4096

enum ERROR_CODE {
    NULL_POSITION = 132,
    EINVAL = 22
};

void error(int code) {
    switch (code)
    {
    case NULL_POSITION:
        printf("ERROR: Adding node to non-existent position\n");
        exit(NULL_POSITION);
        break;
    case EINVAL:
        printf("ERROR: One or more arguments inputted are in wrong format. Please follow instructions carefully.");
        exit(EINVAL);
        break;
    default:
        break;
    }
}

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}

int defaultComparator(int *a, int *b) {
    return (*a > *b);
}

void sort(int *start, int *end, int (*comparator)(int *a, int *b)) {
    for (int *cur = start; cur != end; cur++) {
        for (int *candidate = cur; candidate != end; candidate++) {
            if (comparator(cur, candidate)) {
                swap(cur, candidate);
            }
        }
    }
}

void solution() {
    int n;
    int *a;

    printf("Input a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        error(EINVAL);
    }

    a = malloc(sizeof(int) * n);

    printf("Input %d integers: ", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    sort (a, a + n, &defaultComparator);

    printf("Sorted array: \n");

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    free(a);
}

int main() {
    solution();
}