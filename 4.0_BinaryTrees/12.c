#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 256

typedef struct Node
{
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

Node *newnode(char ch, int freq, Node *left, Node *right)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void buildCodes(Node *root, char *path, int depth, char codes[256][256])
{
    if (!root->left && !root->right)
    {
        path[depth] = '\0';
        strcpy(codes[(unsigned char)root->ch], path);
        return;
    }
    if (root->left)
    {
        path[depth] = '0';
        buildCodes(root->left, path, depth + 1, codes);
    }
    if (root->right)
    {
        path[depth] = '1';
        buildCodes(root->right, path, depth + 1, codes);
    }
}

void huffman(const char *str)
{
    int freq[BUFF] = {0};
    for (const char *p = str; *p; p++)
        freq[(unsigned char)*p]++;
    Node *nodes[BUFF];
    int cnt = 0;
    for (int i = 0; i < BUFF; i++)
        if (freq[i] > 0)
            nodes[cnt++] = newnode((char)i, freq[i], NULL, NULL);

    while (cnt > 1)
    {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq)
        {
            int t = min1;
            min1 = min2;
            min2 = t;
        }
        for (int i = 2; i < cnt; i++)
        {
            if (nodes[i]->freq < nodes[min1]->freq)
            {
                min2 = min1;
                min1 = i;
            }
            else if (nodes[i]->freq < nodes[min2]->freq)
                min2 = i;
        }
        Node *joint = newnode(0, nodes[min1]->freq + nodes[min2]->freq, nodes[min1], nodes[min2]);
        nodes[min1] = joint;
        nodes[min2] = nodes[cnt - 1];
        cnt--;
    }
    Node *root = nodes[0];

    char codes[256][256] = {{0}};
    char path[256];
    buildCodes(root, path, 0, codes);
    printf("Символ   Частота   Код\n");
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            printf("  '%c'      %d     %s\n", (char)i, freq[i], codes[i]);
}

int main()
{
    huffman("abracadabra");
}