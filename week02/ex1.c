#include <stdio.h>
#include <limits.h>
#include <float.h>

void typesDemonstration() {
    int integerMaxVal = INT_MAX;
    float floatMaxVal = FLT_MAX;
    double doubleMaxVal = DBL_MAX;

    printf("INT_MAX = %d\n", integerMaxVal);
    printf("FLT_MAX = %f\n", floatMaxVal);
    printf("DBL_MAX = %f\n", doubleMaxVal);

    printf("\n");

    printf("size of INT_MAX = %d\n", sizeof(integerMaxVal));
    printf("size of FLT_MAX = %d\n", sizeof(floatMaxVal));
    printf("size of DBL_MAX = %d\n", sizeof(doubleMaxVal));
}

int main() {
    typesDemonstration();
}