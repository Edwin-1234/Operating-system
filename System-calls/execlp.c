#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid=fork();        
    if(pid < 0)
    {
        printf("Process creation failed\n");
        return 1;
    }
    else if(pid == 0)           
    {
        if(execlp("./add","add",NULL) == -1)
        {
            printf("Process loading failed\n");
        };
        exit(0);
    }
    else                        
    {
        wait(NULL);
        printf("Child Process has terminated\n");
    }
    return 0;
}
