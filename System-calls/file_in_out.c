#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void write_file(char* filename,char* data)
{
    int fd;
    fd=open(filename,O_WRONLY | O_CREAT | O_TRUNC,06404);
    if(fd == -1)
    {
        perror("Open");
        exit(EXIT_FAILURE);
    }
    if(write(fd,data,strlen(data)) == -1)
    {
        perror("Write");
        exit(EXIT_FAILURE);
    }
    printf("Written Successfully\n");
    if(close(fd) == -1)
    {
        perror("Close");
        exit(EXIT_FAILURE);
    }
}

void read_file(char* filename)
{
    int fd;
    ssize_t bytesread;
    char buffer[1024+1];
    fd=open(filename,O_RDONLY);
    if(fd == -1)
    {
        perror("Open");
        exit(EXIT_FAILURE);
    }
    bytesread=read(fd,buffer,1024);
    if(bytesread == -1)
    {
        perror("Read");
        exit(EXIT_FAILURE);
    }
    buffer[bytesread]='\0';
    printf("\nFile Contents\n");
    printf("%s\n",buffer);
    if(close(fd) == -1)
    {
        perror("Close");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    char filename[25];
    char str[25];
    printf("Enter the name of the file : ");
    scanf("%[^\n]",filename);
    printf("Enter the contents : ");
    scanf(" %[^\n]",str);
    write_file(filename,str);
    read_file(filename);
    return 0;
}
