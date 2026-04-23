#include <stdio.h>
#include <stdlib.h>

typedef struct loopList
{
    int value;
    struct loopList *next;
} loopList;

loopList *fill(int start, int end)
{
    if (start >= end)
        return NULL;
    loopList *head = NULL;
    loopList *tail = NULL;
    for (int i = start; i <= end; i++)
    {
        loopList *ph = (loopList *)malloc(sizeof(loopList));
        ph->value = i;
        ph->next = NULL;
        if (head == NULL)
        {
            head = ph;
            tail = ph;
        }
        else
        {
            tail->next = ph;
            tail = ph;
        }
    }
    tail->next = head;
    return head;
}

void print(loopList *orig)
{
    if (orig == NULL)
        return;
    loopList *head = orig;
    while (head->next != orig)
    {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("%d", head->value);
}

void intersectionLoopLists(loopList **orig, loopList *new)
{
    if (!*orig || !new)
        return;

    loopList *cur = *orig;
    loopList *prev = NULL;
    loopList *tail = *orig;
    while (tail->next != *orig)
        tail = tail->next;

    loopList *stop = *orig;
    do
    {
        loopList *tmp = new;
        int found = 0;
        do
        {
            if (tmp->value == cur->value)
            {
                found = 1;
                break;
            }
            tmp = tmp->next;
        } while (tmp != new);

        loopList *next = cur->next;

        if (!found)
        {
            if (!prev)
            {
                if (cur->next == cur)
                {
                    free(cur);
                    *orig = NULL;
                    return;
                }
                tail->next = next;
                *orig = next;
                free(cur);
                cur = *orig;
                stop = *orig;
            }
            else
            {
                prev->next = next;
                free(cur);
                cur = next;
            }
        }
        else
        {
            prev = cur;
            cur = next;
        }
    } while (cur != stop);
}

int main()
{
    loopList *orig = fill(1, 10);
    loopList *new = fill(5, 15);
    intersectionLoopLists(&orig, new);
    print(orig);
}