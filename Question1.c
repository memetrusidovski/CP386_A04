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

int available[5][4] = {{6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 5, 7, 5}};

void *threadRun(void *t);
int readFile(char *fileName, int ***resources);

int main(int argc, char *argv[])
{
    int ***resources = (int ***) malloc(sizeof(int));
    readFile(name, resources);
    int done = 0;
    char input[20];

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

    while (done == 0)
    {
        printf("Enter Command: ");
        scanf("%s", input);
        printf(" \n");


        if(strcmp(input, "exit") == 0) done = 1;
        sleep(1);
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


    //Build a 2d array to store values
    int **tempresources = (int **)malloc(sizeof(int) * 25);

    int c = 0;

    while(c < 5){
        int *temp = (int *)malloc(sizeof(int)*5);
        
        tempresources[c] = temp;
        c++;
    }

    int x = 0;
    int y = 0;

    *resources = tempresources;

    //(*resources)[1][1] = 4;
    //printf("%d ", (*resources)[4][4]);


    //Load data
    while (fgets(line, sizeof(line), file))
    {
        char *token = NULL;
        int j = 0;
        token = strtok(line, " ");
        while(token != NULL){
            printf("%c ", token[0]);
            token = strtok(NULL, " ");
        }

    }

    fclose(file);
    return 1;
}