#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>     
#include <memory.h>

#define BUFFER_SIZE 4096

struct pFrame {
    int page;
    int counter;
};

int findPage(int targetPage, struct pFrame* begin, struct pFrame *end) {
    for (int i = 0; begin + i != end; i++) {
        if ((begin + i) -> page == targetPage) {
            return i;
        }
    }

    return -1;
}

int findOldestPage(struct pFrame* begin, struct pFrame *end) {
    int result = -1;
    int resultPage = -1;
    int oldest = __INT32_MAX__;
    
    for (int i = 0; begin + i != end; i++) {
        if ((begin + i) -> page == -1) {
            return i;
        }

        int curBits = countBits((begin + i) -> counter);

        if (curBits < oldest) {
            oldest = curBits;
            result = i;
            resultPage = (begin + i) -> page;
        }
    }

    return result;
}

void agePages(struct pFrame* begin, struct pFrame *end) {
    for (int i = 0; begin + i != end; i++) {
        (begin + i) -> counter >>= 1;
    }
}

void loadPage(int newPage, struct pFrame* target) {
    target -> counter = 0;
    target -> page = newPage;
}

int countBits(int target) {
    int result = 0;
    while(target > 0) {
        result += target % 2;
        target /= 2;
    }

    return result;
}

int main() {

    int n;
    printf("Input number of pages: ");
    scanf("%d", &n);

    struct pFrame frames[n];

    //initializing memory
    for (int i = 0; i < n; i++) {
        frames[i].page = -1;
        frames[i].counter = 0;
    }

    int lastTime = 0;

    float hit = 0.;
    float miss = 0.;

    char* fileName = malloc(sizeof(char) * 1000);
    char* outputFileName = malloc(sizeof(char) * 1000);
    
    printf("Input file name: ");
    scanf("%s", fileName);
    printf("Output file name:");
    scanf("%s", outputFileName);

    FILE* file = fopen(fileName, "r");
    FILE* output = fopen(outputFileName, "w");

    int t = 0;

    while(!feof(file)) {
        int p;
        fscanf(file, "%d", &p);

        if (p < 0) {
            break;
        }

        while (lastTime != t) {
            agePages(frames, frames + n);
            lastTime++;
        }

        int pageFound = findPage(p, frames, frames + n);

        if (pageFound == -1) {
            int oldestPageIndex = findOldestPage(frames, frames + n); 
            if ((frames + oldestPageIndex) -> page == -1) {
                fprintf(output, "\nPutting the page %d in the frame %d, where was no page\n", 
                       p, oldestPageIndex);    
            } else {
                fprintf(output, "\nPutting the page %d in the frame %d, where was page %d\n", 
                       p, oldestPageIndex, (frames + oldestPageIndex) -> page);
            }
            loadPage(p, frames + findOldestPage(frames, frames + n));
            miss += 1.0;
        } else {
            frames[pageFound].counter |= (1 << 8);
            fprintf(output, "\nPage %d hit on frame %d\n", p, pageFound);
            hit += 1.0;
        }
        t++;
    }

    fprintf(output, "Hit/Miss rate: %f", hit / miss);

    fclose(file);
    fclose(output);
}