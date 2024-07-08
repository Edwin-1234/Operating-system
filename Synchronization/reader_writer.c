#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int read_count = 0;
int rw_mutex = 1;
int mutex = 1;
int shared_counter = 0; // Shared resource

void wait(int *sem) {
    while (*sem <= 0);
    (*sem)--;
}

void signal(int *sem) {
    (*sem)++;
}

void *writer(void *arg) {
    while (1) {
        wait(&rw_mutex);
        
        shared_counter++;
        printf("Writer incremented counter to %d\n", shared_counter);
        sleep(1);
        signal(&rw_mutex);
    }
    pthread_exit(0);
}

void *reader(void *arg) {
    while (1) {
        wait(&mutex);
        read_count++;
        if (read_count == 1) {
            wait(&rw_mutex);
        }
        signal(&mutex);

      
        printf("Reader read counter value as %d\n", shared_counter);
        sleep(1); 

        wait(&mutex);
        read_count--;
        if (read_count == 0) {
            signal(&rw_mutex);
        }
        signal(&mutex);
    }
    pthread_exit(0);
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&w2, NULL, writer, NULL);
    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&r2, NULL, reader, NULL);
    pthread_create(&r3, NULL, reader, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    return 0;
}
