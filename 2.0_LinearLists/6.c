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

void subDlist(dlist** orig, dlist* new) {
    /*
        1 2 3 4
        1 3 4
        2
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
        if (flag) {
            dlist* nextnode = head1->next;
            if (head1->prev == NULL) {
                *orig = head1->next;
                if (head1->next != NULL)
                    head1->prev = NULL;
            }
            else {
                head1->prev->next = head1->next;
                if (head1->next != NULL)
                    head1->next->prev = head1->prev;
            }

            free(head1);
            head1 = nextnode;
        }
        else
            head1 = head1->next;
    }
}


int main() {
    dlist* orig = fill(1, 16);
    dlist* new = fill(5, 15);
    subDlist(&orig, new);
    print(orig);
}