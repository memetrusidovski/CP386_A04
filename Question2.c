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
int block = 1000000; //Default block size

typedef struct Node
{
    int data;
    int processNum;
    Node *_next;
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
void append(List *list, int data);
void prepend(List *list, int data);
void removeNode(Node *node);
Node *search(List *list, int find);
bool contains(List *list, int find);


int main(int argc, char *argv[])
{
    if(argc >= 2){
        block = atoi(argv[1]);
        printf("Allocated %d bytes of memory", block);
    }
    bool done = true;
    List *lst = create();
    


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
            
        }
        else if (input[0] == 'R' && input[1] == 'L')
        {
                
        }
        else if (strcmp(input, "status") == 0)
        {
            
        }
        else if (strcmp(input, "run") == 0)
        {
            
        }

        sleep(1);
    }
}

List *create()
{
    List *list = (List *)malloc(sizeof(List));
    list->size = 0;

    return list;
}

// Adds a value to the end of a list
void append(List *list, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

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
}

// Add a value to the front of a list
void prepend(List *list, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

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
        if (current->data == find)
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