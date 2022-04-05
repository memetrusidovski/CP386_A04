#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>

sem_t *mutex;
char *name = "file.txt";

int maximum[5][4] = {{6, 4, 7, 3}, {4, 2, 3, 2}, {2, 5, 3, 3}, {6, 3, 3, 2}, {5, 5, 7, 5}};
int allocated[5][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int need[5][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int resources[4] = {10, 5, 7, 8};
int safeSeq[5] = {0,0,0,0,0};
int count = 0;

void * threadRun(void *t);
int readFile(char *fileName, int ***resources);
int needMatrix();
int requestR(int customerNum, char *input);
void printStatus();
void runT();

int main(int argc, char *argv[])
{
    if(argc > 2){
        resources[0] = atoi(argv[1]);
        resources[1] = atoi(argv[2]);
        resources[2] = atoi(argv[3]);
        resources[3] = atoi(argv[4]);
    }
    // if we were to scan file for a 2d array without hardcoding
    /*int ***resources = (int ***) malloc(sizeof(int));
    readFile(name, resources);*/

    bool done = true;

    int n = 5;
    int m = 4;

    if ((mutex = sem_open("/semaphore", O_CREAT, 0644, 1)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    while (done)
    {
        char input[20];
        printf("Enter Command: ");
        scanf(" %20[^\n]", input);

        if (strcmp(input, "exit") == 0)
        {
            done = false;
        }
        else if (input[0] == 'R' && input[1] == 'Q')
        {
            int custNum = (int)input[3] - 48;
            if (requestR(custNum, input) == 1)
                printf("State is safe, request is satisfied\n");
            else
                printf("State is not safe, Rejected\n");
        }
        else if (strcmp(input, "status") == 0){
            printStatus();
        }
        else if (strcmp(input, "run") == 0)
        {
            runT();
        }

        sleep(1);
    }

    
}

int readFile(char *fileName, int ***resources) // use this method in a suitable way to read file
{
    FILE *file;
    file = fopen("sample4_in.txt", "r");

    if (!file)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return -1;
    }

    char line[256];

    // Build a 2d array to store values
    int **tempresources = (int **)malloc(sizeof(int) * 25);

    int c = 0;

    while (c < 5)
    {
        int *temp = (int *)malloc(sizeof(int) * 5);

        tempresources[c] = temp;
        c++;
    }

    int x = 0;
    int y = 0;

    *resources = tempresources;

    //(*resources)[1][1] = 4;
    // printf("%d ", (*resources)[4][4]);

    // Load data
    while (fgets(line, sizeof(line), file))
    {
        char *token = NULL;
        int j = 0;
        token = strtok(line, " ");
        while (token != NULL)
        {
            printf("%c ", token[0]);
            token = strtok(NULL, " ");
        }
    }

    fclose(file);
    return 1;
}

int needMatrix()
{
    // int **needed = (int**) malloc(sizeof(int)*4*5);

    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 4; y++)
            need[x][y] = maximum[x][y] - allocated[x][y];

    
    return 1;
}

void printStatus(){

    printf("Available Resources: \n");
    for(int x = 0; x < 4; x++){
        printf("%d ", resources[x]);
    }

    printf("\nMaximum Resources: \n");
    //Print Max
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 4; y++)
            printf("%d ", maximum[x][y]);
        printf("\n");
    }

    printf("\nAllocated Resources: \n");
    //Allocated
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 4; y++)
            printf("%d ", allocated[x][y]);
        printf("\n");
    }

    printf("\nNeeded Resources: \n");
    //Print need matrix
    needMatrix();
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 4; y++)
            printf("%d ", need[x][y]);
        printf("\n");
    }


}

int requestR(int customerNum, char *input)
{
    int r = 1;
    printf("Request: %d\n", customerNum);

    int temp[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        allocated[customerNum][i] = (int)input[5 + (2 * i)] - 48;
        if (allocated[customerNum][i] > maximum[customerNum][i])
        {
            r = 0;
            // Reset to 0, rejected
            for (int i = 0; i < 4; i++)
                allocated[customerNum][i] = 0;
        }
    }

    if(r == 1){
        for(int i = 0; i < 4; i++)
            resources[i] -= (int)input[5 + (2 * i)] - 48;

        safeSeq[count] = customerNum;
        count++;
    }

    return r;
}

void runT(){
    printf("\nSafe Sequence is: ");

    for(int i = 0; i < count; i++){
        printf("%d ", safeSeq[i]);
    }
    printf("\n");

    for (int i = 0; i < count; i++){
        pthread_t t1;
        int *t = malloc(sizeof(int));
        *t = safeSeq[i];
        pthread_create(&t1, NULL, threadRun, t);
    }

}

void *threadRun(void *t){
    sem_wait(mutex);
    int custT = *((int*) t);
    printf("--> Customer/Thread %d", custT);

    printf("\nAllocated resources: ");
    for(int i = 0; i < 4; i++){
        printf("%d ", allocated[custT][i]);
    }

    printf("\nNeeded: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", need[custT][i]);
    }

    printf("\nAvailable: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", resources[i]);
        resources[i] += allocated[custT][i];
    }

    printf("\nThread has started");
    printf("\nThread has finished");
    printf("\nThread is releasing resources");

    printf("\nNew Available: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", resources[i]);
    }

    printf("\n");
    
    sem_post(mutex);

    return NULL;
}