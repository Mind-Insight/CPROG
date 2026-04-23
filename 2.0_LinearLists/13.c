#include <stdio.h>
#include <stdlib.h>


typedef struct loopList {
    int value;
    struct loopList* next;
} loopList;


void push(loopList** orig, int value) {
    loopList* newnode = (loopList*)malloc(sizeof(loopList));
    newnode->value = value;
    if (*orig == NULL) {
        *orig = newnode;
        (*orig)->next = *orig;
    }
    else {
        loopList* last = *orig;
        while (last->next != *orig) {
            last = last->next;
        }
        newnode->next = *orig;
        last->next = newnode;
    }
}


void print(loopList* orig) {
    if (orig == NULL) return;
    loopList* head = orig;
    while (head->next != orig) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("%d", head->value);
}


void insertSort(loopList** orig) {
    loopList* head = *orig;
    do {
        loopList* temp = head;
        do {
            if (temp->value < head->value) {
                int tmp = temp->value;
                temp->value = head->value;
                head->value = tmp;
            }
            temp = temp->next;
        } while (temp != *orig);
        head = head->next;
    } while(head != *orig);
}


int main() {
    loopList* orig = NULL;
    int n;
    
    printf("Введите кол-во элементов в списке: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int a;
        printf("\nВведите элемент %d: ", i + 1);
        scanf("%d", &a);
        push(&orig, a);
    }
    printf("\n\nИзначальный спискок: ");
    print(orig);

    insertSort(&orig);
    printf("\nОтсортированный последовательность: ");
    print(orig);
}