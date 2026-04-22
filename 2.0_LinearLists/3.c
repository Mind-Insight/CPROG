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

void sub(list** orig, list* new) {
    list* head1 = *orig;
    list* prev = NULL;
    while (head1 != NULL) {
        list* head2 = new;
        int flag = 0;
        while (head2 != NULL) {
            if (head1->value == head2->value) {
                flag = 1;
                if (prev == NULL) {
                    list* head = head1->next;
                    free(head1);
                    head1 = head;
                }
                else {
                    prev->next = head1->next;
                    free(head1);
                    head1 = prev->next;
                }
                break;
            }
            head2 = head2->next;
        }
        if (!flag) {
            prev = head1;
            head1 = head1->next;    
        }
    }
}


int main() {
    list* orig = fill(1, 10);
    list* new = fill(5, 10);
    sub(&orig, new);
    print(orig);
}