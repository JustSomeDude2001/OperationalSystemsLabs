#include <stdio.h>

#include <string.h>
#include <memory.h>


#define BUFFER_SIZE 4096

void swapChars(char *a, char *b) {
    *a = *a^*b;
    *b = *a^*b;
    *a = *b^*a;
}

void reverseString(char *str) {
    int sz = strlen(str);
    for (int i = 0; i < sz / 2; i++) {
        swapChars(&str[i], &str[sz - i - 1]);
    }
}

void solution() {
    fputs("Please input a string.\n", stdout);

    char *str;
    str = malloc(BUFFER_SIZE);
    fscanf(stdin, "%[^\n]s", str);

    reverseString(str);

    printf("%s", str);
    free(str);
}

int main() {
    solution();
}