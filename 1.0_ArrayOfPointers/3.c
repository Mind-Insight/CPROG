#include <stdio.h>

#define buff 100

char *cutString(char *str, int newSize, int left, int right)
{
    char *newStr = (char *)malloc(sizeof(char) * newSize);
    for (int i = 0; i < left; i++)
        newStr[i] = str[i];
    for (int i = left, j = right + 1; i < newSize; i++, j++)
        newStr[i] = str[j];
    return newStr;
}

int bracketCounter(char *row, int size)
{
    int counter = 0;
    for (int i = 0; i < size; i++)
        if (row[i] == '(')
            counter++;
    return counter;
}

char **arr(char *row, int size)
{
    int strSize = bracketCounter(row, size) + 1;
    char **cutstr = (char *)malloc(sizeof(char *) * (strSize + 1));
    int arrInd = 0;
    cutstr[strSize] = NULL;

    int start = 0, end = 0, prev = 0;
    if (!bracketCounter(row, size))
        cutstr[arrInd] = row;
    while (bracketCounter(row, size))
    {
        if (row[start] == '(')
        {
            end = prev = start;
            while (row[end] != ')')
            {
                end += 1;
                if (row[end] == '(')
                {
                    prev = start;
                    start = end;
                }
            }
            int tempSize = end - start - 1;
            char *str = (char *)malloc(sizeof(char) * tempSize);
            for (int i = start + 1, j = 0; i < end, j < tempSize; i++, j++)
                str[j] = row[i];
            cutstr[arrInd] = str;
            arrInd++;
            size -= (end - start + 1);
            // printf("%d %d %d\n", prev, start, end);
            row = cutString(row, size, start, end);
            start = prev;
            if (!bracketCounter(row, size))
                cutstr[arrInd] = row;
        }
        else
            start++;
    }
    return cutstr;
}

int main()
{
    char str[buff];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    char **a = arr(str, strlen(str));
    for (int i = 0; a[i] != NULL; i++)
    {
        printf("%s ", a[i]);
    }
    // char* a = cutString(str, strlen(str) - (5 - 3 + 1), 3, 5);
    // for (int i = 0; i < 6; i++) {
    //     printf("%c", a[i]);
    // }
    // printf("\n");
    // a = cutString(a, 6 - (4 - 1 + 1), 1, 4);
    // for (int i = 0; i < strlen(a); i++) {
    //     printf("%c", a[i]);
    // }

    return 0;
}