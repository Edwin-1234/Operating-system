/*
Write a program which creates a child process and the parent process waits for the 
child process to exit after printing the process id of the child and parent process. 
(Using: fork, wait, getpid, getppid, exit System Calls).
*/
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    pid=fork();

    if(pid < 0)
    {
        printf("Child Process Creation FAILED\n");
        return 1;
    }
    else if(pid==0)
    {
        printf("INSIDE CHILD PROCESS\n");
        printf("Child Process ID : %d\n",getpid());
        printf("Parent Process ID : %d\n",getppid());
        exit(0);
    }
    else
    {
        printf("INSIDE PARENT PROCESS\n");
        //printf("Child Process ID : %d\n",pid);
        //printf("Parent Process ID : %d\n",getpid());
        wait(NULL);
        printf("Child Process has exited\n");
    }
    return 0;
}
