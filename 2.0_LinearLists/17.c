#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 256


typedef struct StringNode {
    char* str;
    struct StringNode* next;
} StringNode;

typedef struct TopNode {
    StringNode* head;
    struct TopNode* next;
} TopNode;


void pushString(StringNode** head, const char* str) {
    StringNode* newNode = (StringNode*)malloc(sizeof(StringNode));
    newNode->str = (char*)malloc(strlen(str) + 1);
    strcpy(newNode->str, str);
    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        StringNode* tail = *head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newNode;
    }
}


TopNode* readFromFile(const char* filename, int bottomLength) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    TopNode* head = NULL;
    TopNode* tail = NULL;
    char buff[BUFF_SIZE];
    int count = 0;
    
    while (fgets(buff, sizeof(buff), file)) {
        buff[strcspn(buff, "\n")] = '\0';
        if (head == NULL || count == bottomLength) {
            TopNode* newNode = (TopNode*)malloc(sizeof(TopNode));
            newNode->head = NULL;
            newNode->next = NULL;
            
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            count = 0;
        }
        pushString(&(tail->head), buff);
        count++;
    }
    fclose(file);
    return head;
}

void printList(TopNode* head) {
    int topNum = 1;
    while (head != NULL) {
        printf("Верхний узел %d:\n", topNum++);
        StringNode* cur = head->head;
        int strNum = 1;
        while (cur != NULL) {
            printf("  %d. %s\n", strNum++, cur->str);
            cur = cur->next;
        }
        head = head->next;
        printf("\n");
    }
}


int main() {
    FILE* f = fopen("text.txt", "w");
    int bottomLength = 3;
    TopNode* list = readFromFile("text.txt", bottomLength);
    printList(list);
}