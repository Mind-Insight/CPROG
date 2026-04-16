#include <stdio.h>

#define N 5
#define buff 100

typedef struct
{
    int **arr;
    int header;
    int arrPtr;
} Stack;

Stack *create()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->arr = (int *)malloc(sizeof(int *) * buff);
    stack->header = 0;
    stack->arrPtr = 0;
    return stack;
}

void push(Stack *stack, int value)
{
    if (stack->arrPtr == 0)
    {
        int *newArr = (int *)malloc(sizeof(int) * N);
        newArr[stack->arrPtr] = value;
        stack->arr[stack->header] = newArr;
        stack->arrPtr++;
    }
    else if (stack->arrPtr % N == 0)
    {
        stack->arrPtr = 0;
        int *newArr = (int *)malloc(sizeof(int) * N);
        stack->header++;
        newArr[stack->arrPtr] = value;
        stack->arr[stack->header] = newArr;
        stack->arrPtr++;
    }
    else
    {
        stack->arr[stack->header][stack->arrPtr] = value;
        stack->arrPtr++;
    }
}

void pop(Stack *stack)
{
    if (stack->arrPtr != 0)
    {
        stack->arr[stack->header][stack->arrPtr] = NULL;
        stack->arrPtr--;
        if (stack->arrPtr == 0)
        {
            free(stack->arr[stack->header]);
            stack->header--;
            stack->arrPtr = N;
        }
    }
    else
        printf("Stack is empty\n");
}

void print(Stack *stack)
{
    int p = stack->header;
    for (int i = 0; i < stack->arrPtr; i++)
        printf("%d ", stack->arr[stack->header][i]);
    printf("\n");
    p--;
    while (p != -1)
    {
        for (int i = 0; i < N; i++)
            printf("%d ", stack->arr[p][i]);
        p--;
        printf("\n");
    }
}

int main()
{
    Stack *stack = create();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    push(stack, 6);
    pop(stack);
    push(stack, 6);
    print(stack);
    free(stack);
}