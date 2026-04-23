#include <stdio.h>
#include <stdlib.h>


typedef struct loopList {
    int value;
    struct loopList* next;
} loopList;

loopList* fill(int start, int end) {
    if (start >= end) return NULL;
    loopList* head = NULL;
    loopList* tail = NULL;
    for (int i = start; i <= end; i++) {
        loopList* ph = (loopList*)malloc(sizeof(loopList));
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
    tail->next = head;
    return head;
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


void subLoopLists(loopList** orig, loopList* new) {
    if (new == NULL || *orig == NULL) return;
    loopList* head = *orig;
    loopList* prev = NULL;

    loopList* tail = *orig;
    while (tail->next != *orig) tail = tail->next;
    
    int count = 0;
    loopList* tmp = *orig;
    do {
        count++;
        tmp = tmp->next;
    } while (tmp != *orig);
    
    for (int i = 0; i < count; i++) {
        loopList* temp = new;
        int flag = 0;
        do {
            if (head->value == temp->value) {
                flag = 1;
                break;
            }
            temp = temp->next;
        } while (temp != new);
        
        loopList* nextnode = head->next;
        
        if (flag) {
            if (prev == NULL) {
                if (head->next == head) {
                    free(head);
                    *orig = NULL;
                    return;
                }
                *orig = nextnode;
                tail->next = nextnode;
                free(head);
                head = nextnode;
            } else {
                prev->next = nextnode;
                if (head == tail) {
                    tail = prev;
                }
                free(head);
                head = nextnode;
            }
        } else {
            prev = head;
            head = nextnode;
        }
    }
}



int main() {
    loopList* orig = fill(1, 10);
    loopList* new = fill(2, 4);
    subLoopLists(&orig, new);
    print(orig);
}