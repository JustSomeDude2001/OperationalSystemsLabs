#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <memory.h>

#define BUFFER_SIZE 4096

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}

enum ERROR_CODE {
    NULL_POSITION = 132,
    EINVAL = 22
};

void error(int code) {
    switch (code)
    {
    case NULL_POSITION:
        printf("ERROR: Adding node to non-existent position\n");
        exit(NULL_POSITION);
        break;
    case EINVAL:
        printf("ERROR: One or more arguments inputted are in bad format. Please follow instructions carefully.");
        exit(EINVAL);
        break;
    default:
        break;
    }
}

struct DataPackage {
    int a;
};

struct DataPackage newData(int a) {
    struct DataPackage result;
    result.a = a;
    return result;
}

struct Node {
    struct DataPackage data;
    struct Node *nextNode;
};

struct LinkedList {
    struct Node *head;
};

struct Node *newNode(struct DataPackage newData) {
    struct Node *nodePointer;
    
    nodePointer = malloc(sizeof(struct Node));

    nodePointer -> data = newData;

    nodePointer -> nextNode = NULL;

    return nodePointer;
} 

struct Node *dummyNode() {
    return newNode(newData(0));
}

struct LinkedList *newLinkedList() {
    struct LinkedList *result = malloc(sizeof(struct LinkedList));
    result -> head = dummyNode();
}

void addNode(struct LinkedList *targetList, struct DataPackage newData, int position) {

    if (position < 0) {
        error(NULL_POSITION);
    }

    struct Node *currentNode = targetList -> head;
    
    for (int curPos = 0; curPos < position; curPos++) {
        if (currentNode -> nextNode == NULL) {
            error(NULL_POSITION);
        }

        currentNode = currentNode -> nextNode;
    }

    struct Node *insertedNode = newNode(newData);

    insertedNode -> nextNode = currentNode -> nextNode; 

    currentNode -> nextNode = insertedNode;
}

void removeNode(struct LinkedList *targetList, int position) {
    
    if (position <= 0) {
        error(NULL_POSITION);
    }

    struct Node *currentNode = targetList -> head;

    for (int curPos = 0; curPos < position; curPos++) {
        if (currentNode -> nextNode == NULL) {
            error(NULL_POSITION);
        }

        if (curPos + 1 == position) {
            struct Node *temp = currentNode -> nextNode;
            currentNode -> nextNode = currentNode -> nextNode -> nextNode;
            free(temp);
            break;
        }

        currentNode = currentNode -> nextNode;
    }
}

void printLinkedList(struct LinkedList *targetList) {
    
    struct Node *currentNode = targetList -> head;

    do {
        currentNode = currentNode -> nextNode;
        if (currentNode != NULL) {
            printf("%d ", currentNode -> data.a);
        }
    } while(currentNode != NULL);
}

void nodeRecursiveDestructor(struct Node *targetNode) {
    if (targetNode -> nextNode != NULL) {
        nodeRecursiveDestructor(targetNode -> nextNode);
    }

    free(targetNode);
}

void linkedListDestructor(struct LinkedList *targetList) {
    if(targetList -> head != NULL) {
        nodeRecursiveDestructor(targetList -> head);
    }

    free(targetList);
}

void solution() {

    struct LinkedList *currentList = newLinkedList();

    while (1) {
        int currentTask;
        printf("Please choose next action:\n");
        printf("1. Add value to linked list.\n");
        printf("2. Remove item from linked list.\n");
        printf("3. Display linked list.\n");
        printf("4. End execution.\n");
        scanf("%d", &currentTask);

        switch (currentTask)
        {
        case 1:
            printf("Please input any integer and a valid position.\n");
            int value, pos;
            scanf("%d%d", &value, &pos);

            addNode(currentList, newData(value), pos);

            break;
        
        case 2:
            printf("Please input any valid position.\n");
            int position;
            scanf("%d", &position);

            removeNode(currentList, position);

            break;

        case 3:
            printLinkedList(currentList);
            printf("\n");
            
            break;
        
        case 4:
            linkedListDestructor(currentList);

            exit(0);
        default:
            printf("Invalid task number. Try again.\n");
            break;
        }
    }
}

int main() {
    solution();
}