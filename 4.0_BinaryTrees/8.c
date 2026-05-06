#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define BUFF 100
#define TREE_N 2

typedef struct Node
{
    char *row;
    struct Node **children;
    int max;
    int count;
} Node;

Node *root = NULL;

typedef struct
{
    Node ***arr;
    int header;
    int headerPtr;
    int tail;
    int tailPtr;
} Queue;

Queue *create()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->arr = (Node ***)malloc(sizeof(Node **) * BUFF);
    for (int i = 0; i < BUFF; i++)
        queue->arr[i] = NULL;
    queue->header = 0;
    queue->headerPtr = 0;
    queue->tail = 0;
    queue->tailPtr = 0;
    return queue;
}

void push(Queue *queue, Node *value)
{
    if (queue->arr[queue->tail] == NULL)
    {
        queue->arr[queue->tail] = (Node **)malloc(sizeof(Node *) * N);
        queue->tailPtr = 0;
    }
    queue->arr[queue->tail][queue->tailPtr] = value;
    queue->tailPtr++;
    if (queue->tailPtr == N)
    {
        queue->tail++;
        queue->tailPtr = 0;
    }
}

Node *pop(Queue *queue)
{
    if (queue->header == queue->tail && queue->headerPtr >= queue->tailPtr)
        return NULL;

    Node *value = queue->arr[queue->header][queue->headerPtr];
    queue->headerPtr++;
    if (queue->headerPtr == N)
    {
        free(queue->arr[queue->header]);
        queue->arr[queue->header] = NULL;
        queue->header++;
        queue->headerPtr = 0;
    }
    return value;
}

int is_empty(Queue *queue)
{
    return (queue->header == queue->tail && queue->headerPtr >= queue->tailPtr);
}

Node *peek(Queue *queue)
{
    if (is_empty(queue))
        return NULL;
    return queue->arr[queue->header][queue->headerPtr];
}

Node *create_node(const char *s, int max_children)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->row = strdup(s);
    node->max = max_children;
    node->count = 0;
    node->children = (Node **)malloc(max_children * sizeof(Node *));
    return node;
}

void insert(const char *s, Queue *q)
{
    if (root == NULL)
    {
        root = create_node(s, TREE_N);
        push(q, root);
        return;
    }
    Node *parent = peek(q);
    if (parent == NULL)
        return;

    int child_max = parent->max * 2;
    Node *child = create_node(s, child_max);
    parent->children[parent->count] = child;
    parent->count++;
    push(q, child);
    if (parent->count == parent->max)
        pop(q);
}

void print(Node *node, int depth)
{
    if (node == NULL)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("%s\n", node->row);
    for (int i = 0; i < node->count; i++)
        print(node->children[i], depth + 1);
}

int main()
{
    Queue *q = create();

    insert("lvl_1", q);
    insert("lvl_2", q);
    insert("lvl_2", q);
    insert("lvl_3", q);
    insert("lvl_3", q);
    insert("lvl_3", q);
    insert("lvl_3", q);
    insert("lvl_3", q);
    insert("lvl_3", q);
    print(root, 0);
}