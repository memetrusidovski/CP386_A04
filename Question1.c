#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

sem_t *mutex;
char *name = "file.txt";

void *threadRun(void *t);
int readFile(char *fileName, int ***resources);

int main(int argc, char *argv[])
{
    int ***resources = (int ***) malloc(sizeof(int));
    readFile(name, resources);

    int numberCustomers = 0;
    int availableResources[4] = {0,0,0,0};
    int n, m, i, j, k;
    n = 7;
    m = 2;

    if ((mutex = sem_open("/semaphore", O_CREAT, 0644, 1)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }



}

int readFile(char *fileName, int ***resources) // use this method in a suitable way to read file
{
    FILE *file;
    file = fopen("sample4_in.txt", "r");

    if (!file){
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return -1;}

    char line[256];

    while (fgets(line, sizeof(line), file))
    {
       printf("%s", line);
    }

    fclose(file);

    *resources = (int **)malloc(sizeof(int) * 25);

    int c = 0;

    while(c < 5){
        int *temp = (int *)malloc(sizeof(int)*5);
        
        (*resources)[c] = temp;
        c++;
    }

    int x = 0;
    int y = 0;

    while(x < 5){
        while (y < 5){
            printf("%d ", (*resources)[x][y]);
            y++;
        }
        printf("\n");
        x++;
    }

    return 1;
}