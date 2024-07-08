#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;
int S = 1; 
int E = BUFFER_SIZE; 
int F = 0; 

void wait(int *sem) {
    while (*sem <= 0) {}
    (*sem)--;
}

void signal(int *sem) {
    (*sem)++;
}

void *producer(void *arg) {
    int item = 1; /
    while (1) {
        wait(&E); 
        wait(&S); 

        
        sleep(1);
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        signal(&S); 
        signal(&F); 

        item=(item+1)%BUFFER_SIZE;
    }
}

void *consumer(void *arg) {
    while (1) {
        wait(&F);
        wait(&S); 

       
        sleep(1);
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        signal(&S); 
        signal(&E); 
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
