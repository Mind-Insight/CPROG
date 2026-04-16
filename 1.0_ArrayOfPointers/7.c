#include <stdio.h>

#define N 5
#define buff 100

typedef struct
{
    int **arr;
    int header;
    int headerPtr;
    int tail;
    int tailPtr;
} Queue;

Queue *create()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->arr = (int *)malloc(sizeof(int *) * buff);
    queue->header = 0;
    queue->headerPtr = 0;
    queue->tail = 0;
    queue->tailPtr = 0;
    return queue;
}

void push(Queue *queue, int value)
{
    if (queue->tailPtr == 0)
    {
        int *newArr = (int *)malloc(sizeof(int) * N);
        newArr[queue->tail] = value;
        queue->arr[queue->tail] = newArr;
        if (queue->header == queue->tail)
            queue->headerPtr++;
        queue->tailPtr++;
    }
    else if (queue->tailPtr == N)
    {
        int *newArr = (int *)malloc(sizeof(int) * N);
        queue->tailPtr = 0;
        newArr[queue->tailPtr] = value;
        queue->tailPtr++;
        queue->tail++;
        queue->arr[queue->tail] = newArr;
    }
    else
    {
        queue->arr[queue->tail][queue->tailPtr] = value;
        if (queue->header == queue->tail)
            queue->headerPtr++;
        queue->tailPtr++;
    }
}

void pop(Queue *queue)
{
    if (queue->headerPtr != 0)
    {
        queue->arr[queue->header][queue->headerPtr] = NULL;
        queue->headerPtr--;
        if (queue->headerPtr == 0)
        {
            free(queue->arr[queue->header]);
            if (queue->tail == 0 && queue->header == 0)
            {
                queue->tailPtr--;
                queue->headerPtr = queue->tailPtr;
            }
            else
            {
                queue->header++;
                if (queue->header == queue->tail)
                    queue->headerPtr = queue->tailPtr;
                else
                    queue->headerPtr = N;
            }
        }
    }
}

void print(Queue *queue)
{
    int p = queue->header;
    for (int i = 0; i < queue->headerPtr; i++)
        printf("%d ", queue->arr[p][i]);
    printf("\n");
    while (p != queue->tail)
    {
        p++;
        if (p == queue->tail)
        {
            for (int i = 0; i < queue->tailPtr; i++)
                printf("%d ", queue->arr[p][i]);
        }
        else
            for (int i = 0; i < N; i++)
                printf("%d ", queue->arr[p][i]);
        printf("\n");
    }
}

int main()
{
    Queue *queue = create();
    push(queue, 1);
    push(queue, 2);
    push(queue, 3);
    push(queue, 4);
    push(queue, 5);
    push(queue, 5);
    push(queue, 5);
    pop(queue);
    push(queue, 5);
    push(queue, 5);
    push(queue, 5);
    push(queue, 5);
    push(queue, 5);
    pop(queue);
    print(queue);
}