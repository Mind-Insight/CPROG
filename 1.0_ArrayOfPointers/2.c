#include <stdio.h>
#include <string.h>

#define N 1000

int getWordsCount(char *row)
{
    int counter = 0;
    int i = 0;
    int start = 0;
    while (row[i] != "\0" && i < strlen(row))
    {
        start = -1;
        while (isalpha(row[i]))
        {
            if (start == -1)
                start = i;
            i += 1;
        }
        if (start != -1)
        {
            counter += 1;
        }
        i += 1;
    }
    return counter;
}

char **getWords(char *row)
{
    int counter = 0;
    int i = 0;
    int flag = 0;
    int start = 0, end = 0;
    char **pp = (int *)malloc(sizeof(int *) * (getWordsCount(row) + 1));
    int ipp = 0;
    while (row[i] != "\0" && i < strlen(row))
    {
        start = -1;
        end = 0;
        while (isalpha(row[i]))
        {
            if (start == -1)
                start = i;
            i += 1;
        }
        if (start != -1)
        {
            end = i - 1;
            int wordLen = end - start + 1;
            char *word = (char *)malloc(sizeof(char) * wordLen);
            int wordInd = 0;
            for (int x = start; x < end + 1; x++, wordInd++)
                word[wordInd] = row[x];
            pp[ipp] = word;
            ipp++;
        }
        i += 1;
    }
    pp[++ipp] = NULL;
    return pp;
}

int main()
{
    char row[N];
    fgets(row, N, stdin);
    row[strcspn(row, "\n")] = '\0';

    char **words = getWords(row);
    for (int i = 0; words[i] != NULL; i++)
    {
        printf("%s\n", words[i]);
    }
    return 0;
}