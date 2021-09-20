#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>
#include <memory.h>

#define BUFFER_SIZE 4096

#define N 100

char s[N];

int bConsumerSleeping = 1, bProducerSleeping = 0; //booleans
int position = 0; 

              //Consumer sleeps when buffer is empty. 
              //Producer sleeps when buffer is full.

void *Produce(void *args) {
    while(1) {
        if (bProducerSleeping) {
            continue;
        }

        printf("Producer filling slot %d\n", position);
        s[position] = 'F';
        position++;

        if (position == N) {
            position = 0;
            bProducerSleeping = 1;
            bConsumerSleeping = 0;
        }
    }

    return NULL;
}

void *Consume(void *args) {
    while(1) {
        if (bConsumerSleeping) {
            continue;
        }

        printf("Consumer consuming slot %d\n", position);
        s[position] = 'E';
        position++;

        if (position == N) {
            position = 0;
            bConsumerSleeping = 1;
            bProducerSleeping = 0;
        }
    }
}

int main() {
    pthread_t tProducer, tConsumer;

    pthread_create(&tProducer, NULL, &Produce, NULL);
    pthread_create(&tConsumer, NULL, &Consume, NULL);

    pthread_join(tProducer, NULL);
    pthread_join(tConsumer, NULL);
}