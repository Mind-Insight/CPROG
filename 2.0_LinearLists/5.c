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
    dlist* head1 = *orig;
    while (head1 != NULL) {
        int found = 0;
        dlist* temp = new;
        while (temp != NULL) {
            if (temp->value == head1->value) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        
        if (!found) {
            dlist* next_node = head1->next;
            if (head1->prev == NULL) {
                *orig = next_node;
                if (next_node != NULL)
                    next_node->prev = NULL;
            } else {
                head1->prev->next = next_node;
                if (next_node != NULL) {
                    next_node->prev = head1->prev;
                }
            }
            
            free(head1);
            head1 = next_node;
        } else
            head1 = head1->next;
    }
}


int main() {
    dlist* orig = fill(1, 10);
    dlist* new = fill(5, 15);
    intersectionDlist(&orig, new);
    print(orig);
}