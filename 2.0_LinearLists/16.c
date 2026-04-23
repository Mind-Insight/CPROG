#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
#define BUFF_SIZE 256

typedef struct Node {
    char* strings[SIZE + 1];
    struct Node* next;
} Node;


Node* readFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    Node* head = NULL;
    Node* tail = NULL;
    char buff[BUFF_SIZE];
    int index = 0;
    
    while (fgets(buff, sizeof(buff), file)) {
        buff[strcspn(buff, "\n")] = '\0';
        
        if (head == NULL || index == SIZE) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->next = NULL;
            
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            index = 0;
        }
        tail->strings[index] = (char*)malloc(strlen(buff) + 1);
        strcpy(tail->strings[index], buff);
        index++;
    }
    
    fclose(file);
    if (tail != NULL) {
        tail->strings[index] = NULL;
        tail->next = head;
    }
    return head;
}


void printList(Node* head) {
    if (head == NULL) return;
    
    Node* cur = head;
    int nodeNum = 1;
    
    do {
        printf("Узел %d:\n", nodeNum++);
        for (int i = 0; cur->strings[i] != NULL; i++) {
            printf("  %s\n", cur->strings[i]);
        }
        cur = cur->next;
    } while (cur != head);
}


int main() {
    FILE* f = fopen("txt.txt", "w");
    Node* list = readFromFile("txt.txt");
    printList(list);
}