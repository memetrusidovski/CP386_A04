#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>

// Memet Rusidovski 130951550
// https://github.com/memetrusidovski/CP386_A04
sem_t *mutex;
int block = 1000000; //Default block size
int allocated = 0;

typedef struct Node
{
    int data;
    int processNum;
    struct Node *_next;
} Node;

typedef struct List
{
    int size;
    Node *_head;
    Node *_tail;
} List;

// All Linked List code is mine from my github repo
// https://github.com/memetrusidovski/Data-Structures/tree/main/C
List *create();
Node* append(List *list, int data, int num);
void prepend(List *list, int data, int num);
void removeNode(Node *node);
Node *search(List *list, int find);
bool contains(List *list, int find);
int req(Node *node);
void status(List* lst);

int main(int argc, char *argv[])
{
    if(argc >= 2){
        block = atoi(argv[1]);
        printf("Allocated %d bytes of memory\n", block);
    }
    bool done = true;
    List *lst = create();
    char *token = NULL;

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
            token = strtok(input, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");

            Node *node = append(lst,atoi(token),  atoi(&input[4]));
            
            req(node);
        }
        else if (input[0] == 'R' && input[1] == 'L')
        {
            removeNode(search(lst, atoi(&input[4])));
        }
        else if (strcmp(input, "status") == 0)
        {
            status(lst);
        }
        else if (strcmp(input, "run") == 0)
        {
            
        }

        sleep(1);
    }
}

int req(Node *node){


    return 1;
}

void status(List *lst){
    Node *current = (Node *)malloc(sizeof(Node));
    current = lst->_head;

    while (current != NULL)
    {
        printf("p%d: %d <<<<<<\n", current->processNum, current->data);
        current = current->_next;
    }
}

List *create()
{
    List *list = (List *)malloc(sizeof(List));
    list->size = 0;

    return list;
}

// Adds a value to the end of a list
Node* append(List *list, int data, int num)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->processNum = num;

    if (list->size == 0)
    {
        list->_head = newNode;
        list->_tail = newNode;
    }
    else
    {
        list->_tail->_next = newNode;
        list->_tail = newNode;
    }

    list->size++;

    return newNode;
}

// Add a value to the front of a list
void prepend(List *list, int data, int num)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->processNum = num;

    if (list->size == 0)
    {
        list->_head = newNode;
        list->_tail = newNode;
    }
    else
    {
        newNode->_next = list->_head;
        list->_head = newNode;
    }

    list->size++;
}

// Takes a node and removes it from the list in Constant Time
void removeNode(Node *node)
{
    node->data = node->_next->data;
    node->_next = node->_next->_next;
}

// A linear search function
Node *search(List *list, int find)
{
    Node *current = (Node *)malloc(sizeof(Node));
    current = list->_head;

    while (current != NULL)
    {
        if (current->processNum == find)
        {
            return current;
        }
        else
            current = current->_next;
    }

    return current;
}

// Checks if a value is contained in the list
bool contains(List *list, int find)
{
    if (search(list, find) != NULL)
        return true;

    return false;
}