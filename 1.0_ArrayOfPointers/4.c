#include <stdio.h>
#include <string.h>

#define buff 100

char **DMU(char *string, int size)
{
    char **arr = (char *)malloc(sizeof(char *) * buff);
    int iArr = 0;
    int center = 3;
    int start = 0;
    int shift = 3;
    while (center + shift < size)
    {
        int flag = 1;
        for (int i = start, j = center + shift; i < shift, j >= shift; i++, j--)
            if (string[i] != string[j])
                flag = 0;
        if (flag)
        {
            int subseqSize = (center + shift - start + 1);
            char *resSubseq = (char *)malloc(sizeof(char) * subseqSize);
            for (int i = start, j = 0; i <= center + shift, j < subseqSize; i++, j++)
                resSubseq[j] = string[i];
            arr[iArr] = resSubseq;
            iArr++;
            int outerShift = 3;
            int shiftCounter = 1;
            while (start > 0 && center + shift + shiftCounter < size)
            {
                if (string[start - 1] == string[center + shift + shiftCounter])
                {
                    start--;
                    int tmpSize = center + shift + shiftCounter - start + 1;
                    char *tmpArr = (char *)malloc(sizeof(char) * tmpSize);
                    for (int i = 0, j = start; i < tmpSize, j < center + shift + shiftCounter + 1; i++, j++)
                        tmpArr[i] = string[j];
                    shiftCounter++;
                    outerShift++;
                    arr[iArr] = tmpArr;
                    iArr++;
                }
                else
                {
                    break;
                }
            }
            shift += outerShift;
            start += outerShift;
        }
        else
        {
            shift++;
            start++;
        }
    }
    arr[iArr] = NULL;
    return arr;
}

int main()
{
    char string[buff];
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';

    char **result = DMU(string, strlen(string));
    if (result[0] == NULL)
    {
        printf("no palindromes");
    }
    for (int i = 0; result[i] != NULL; i++)
    {
        printf("%s ", result[i]);
    }
}