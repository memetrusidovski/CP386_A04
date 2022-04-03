#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

sem_t *mutex;

void *threadRun(void *t);
int readFile(char *fileName );

int main(int argc, char *argv[])
{
    int testInteger;
    while(1 == 1){
    printf("Enter an integer: ");
    scanf("%d", &testInteger);
    printf("Number = %d \n", testInteger);
    sleep(1);
    }

}