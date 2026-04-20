#include <stdio.h>
#include <stdlib.h>


typedef struct list {
    int value;
    struct list* next;
} list;

list* fill(int start, int end) {
    list* head = NULL;
    list* tail = NULL;
    for (int i = start; i <= end; i++) {
        list* ph = (list*)malloc(sizeof(list));
        ph->value = i;
        ph->next = NULL;
        if (head == NULL) {
            head = ph;
            tail = ph;
        }
        else {
            tail->next = ph;
            tail = ph;
        }
    }
    return head;
}

void print(list* orig) {
    list* head = orig;
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
}

void intersection(list** orig, list** new) {
    list* head1 = *orig;
    list* head2 = *new;
    while (head2 != NULL) {
        
    }
}


int main() {
    list* orig = fill(1, 10);
    
}