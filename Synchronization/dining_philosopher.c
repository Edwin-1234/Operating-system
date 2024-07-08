
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define size 5

int chopstick[size]={1,1,1,1,1};

void wait(int *sem)
{
    while((*sem)<=0);
    (*sem)--;
}

void signal(int *sem)
{
    (*sem)++;
}

void *philosopher(void *arg)
{
    int id=*(int *)arg;
    int lfork,rfork,flag=1;
    while(flag == 1)
    {
        wait(&chopstick[id]);
        lfork=id;
        printf("Philosopher %d picked up fork %d\n",id,lfork);
        wait(&chopstick[(id+1)%size]);
        rfork=(id+1)%size;
        printf("Philosopher %d picked up fork %d\n",id,rfork);
        printf("PHILOSOPHER %d STARTED EATING\n",id);
        //eating
        sleep(1);
        signal(&chopstick[id]);
        printf("Philosopher %d released fork %d\n",id,lfork);
        signal(&chopstick[(id+1)%size]);
        printf("Philosopher %d released fork %d\n",id,rfork);
        printf("Philosopher %d is thinking\n", id);
        //thinking
    }
}

void main()
{
    int p[size]={0,1,2,3,4};
    pthread_t p0,p1,p2,p3,p4;
    pthread_create(&p0,NULL,philosopher,&p[0]);
    pthread_create(&p1,NULL,philosopher,&p[1]);
    pthread_create(&p2,NULL,philosopher,&p[2]);
    pthread_create(&p4,NULL,philosopher,&p[3]);
    pthread_create(&p4,NULL,philosopher,&p[4]);
    pthread_join(p0,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
}
