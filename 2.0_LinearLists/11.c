#include <stdio.h>
#include <stdlib.h>

typedef struct dlist {
    int value;
    struct dlist* next;
    struct dlist* prev;
} dlist;

void push(dlist** orig, int value) {
    dlist* newnode = (dlist*)malloc(sizeof(dlist));
    newnode->value = value;
    newnode->next = NULL;

    if (*orig == NULL) {
        newnode->prev = NULL;
        *orig = newnode;
    } else {
        dlist* tail = *orig;
        while (tail->next != NULL) tail = tail->next;
        newnode->prev = tail;
        tail->next = newnode;
    }
}

void print(dlist* orig) {
    dlist* head = orig;
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}


dlist* findMin(dlist* orig) {
    if (orig == NULL) return NULL;
    dlist* head1 = orig;
    dlist* minLocal = orig;
    while (head1 != NULL) {
        if (head1->value < minLocal->value) minLocal = head1;
        head1 = head1->next;
    }
    return minLocal;
}


void insertSort(dlist** orig) {
    dlist* head = *orig;
    while (head != NULL) {
        dlist* temp = head;
        while (temp->prev != NULL) {
            if (temp->value < temp->prev->value) {
                int tmp = temp->value;
                temp->value = temp->prev->value;
                temp->prev->value = tmp;
            }
            temp = temp->prev;
        }
        head = head->next;
    }
}

int main() {
    dlist* orig = NULL;
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