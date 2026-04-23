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


void selectionSort(loopList** orig) {
    if (*orig == NULL || (*orig)->next == *orig) return;
    
    loopList* start = *orig;
    do {
        loopList* min_node = start;
        loopList* cur = start->next;
        while (cur != *orig) {
            if (cur->value < min_node->value) min_node = cur;
            cur = cur->next;
        }
        if (min_node != start) {
            int temp = start->value;
            start->value = min_node->value;
            min_node->value = temp;
        }
        start = start->next;
    } while (start != *orig);
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

    selectionSort(&orig);
    printf("\nОтсортированный последовательность: ");
    print(orig);
}