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


void unionloopLists(loopList** orig, loopList* new) {
    if (new == NULL) return;
    if (*orig == NULL) {
        loopList* cur = new;
        do {
            loopList* node = (loopList*)malloc(sizeof(loopList));
            node->value = cur->value;
            node->next = (*orig == NULL) ? node : (*orig);
            if (*orig == NULL) {
                *orig = node;
            } else {
                loopList* tail = *orig;
                while (tail->next != *orig) tail = tail->next;
                tail->next = node;
            }
            cur = cur->next;
        } while (cur != new);
        return;
    }
    
    loopList* tail = *orig;
    while (tail->next != *orig) tail = tail->next;
    loopList* cur_new = new;
    do {
        loopList* cur_orig = *orig;
        int found = 0;
        do {
            if (cur_orig->value == cur_new->value) {
                found = 1;
                break;
            }
            cur_orig = cur_orig->next;
        } while (cur_orig != *orig);

        if (!found) {
            loopList* node = (loopList*)malloc(sizeof(loopList));
            node->value = cur_new->value;
            node->next = *orig;
            tail->next = node;
            tail = node;
        }
        
        cur_new = cur_new->next;
    } while (cur_new != new);
}



int main() {
    loopList* orig = fill(1, 10);
    loopList* new = fill(5, 15);
    unionloopLists(&orig, new);
    print(orig);
}