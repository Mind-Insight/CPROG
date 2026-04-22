#include <stdio.h>
#include <stdlib.h>


typedef struct dlist {
    int value;
    struct dlist* next;
    struct dlist* prev;
} dlist;

dlist* fill(int start, int end) {
    dlist* head = NULL;
    dlist* tail = NULL;
    for (int i = start; i <= end; i++) {
        dlist* ph = (dlist*)malloc(sizeof(dlist));
        ph->value = i;
        ph->next = NULL;
        if (head == NULL) {
            ph->prev = NULL;
            head = ph;
            tail = ph;
        }
        else {
            ph->prev = tail;
            tail->next = ph;
            tail = ph;
        }
    }
    return head;
}

void print(dlist* orig) {
    dlist* head = orig;
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
}

void intersectionDlist(dlist** orig, dlist* new) {
    /*
    1 2 3 4
    3 4
    */
    dlist* head1 = *orig;
    while (head1 != NULL) {
        dlist* temp = new;
        int flag = 0;
        while (temp != NULL) {
            if (temp->value == head1->value) {
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if (!flag) {
            if (head1->prev == NULL) {
                dlist* head = head1;
                free(head1);
                head1 = head->next;
            }
            else {
                dlist* head = head1->next;
                head1->prev = head1->next;
                free(head1);
                head1 = head;
            }
        }
        head1 = head1->next;
    }

}


int main() {
    dlist* orig = fill(1, 10);
    dlist* new = fill(5, 15);
    intersectionDlist(&orig, new);
    print(orig);
}