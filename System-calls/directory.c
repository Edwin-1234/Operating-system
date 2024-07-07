#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main() 
{
    DIR *d;
    int value;
    struct stat f;
    struct dirent *dir;

    d = opendir(".");
    if (d == NULL) 
    {
        printf("could not open current directory");
        exit(EXIT_FAILURE);
    } 
    else
    {
        for (dir = readdir(d); dir != NULL; dir = readdir(d))
        {
            value = stat(dir->d_name, &f);
            if (value < 0) 
            {
                perror("Error getting file status");
                continue;
            }
            printf("File: %s\n", dir->d_name);
            printf("Size: %ld bytes\n", f.st_size);
            printf("---------------------------------\n");
        }
    }
    closedir(d);
}
