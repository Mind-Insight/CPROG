#include <stdio.h>
#include <stdlib.h>

// возвращает количество возрастающих последовательностей
int getSubseqCount(int *arr, int size, int *size_additional)
{
    int counter = 0;
    int i = 0, j = 1;
    int flag = 0;
    while (j < size)
    {
        flag = 0;
        while (arr[j] > arr[i] && j < size)
        {
            i += 1;
            j += 1;
            flag = 1;
        }
        if (flag)
            counter += 1;
        else
            *size_additional += 1;
        i = j;
        j += 1;
        if (j == size)
            *size_additional += 1;
    }
    return counter;
}

int *getIntervalsArr(int *arr, int size, int sscount)
{
    // в интервалах храним {(индекс начала пп, длина пп), (...)}
    int *intervals = (int *)malloc(sscount * 2 * sizeof(int));
    int i = 0, j = 1;
    int iind = 0;
    int stInd = -1;
    while (j < size)
    {
        int localLen = 0;
        stInd = -1;
        while (arr[j] > arr[i] && j < size)
        {
            if (stInd == -1)
                stInd = i;
            i += 1;
            j += 1;
            localLen += 1;
        }
        if (localLen)
        {
            intervals[iind++] = stInd;
            intervals[iind++] = localLen + 1;
        }
        i = j;
        j += 1;
    }

    return intervals;
}

int **findIncSubseq(int *arr, int size, int *intervals, int sizeIntervals, int sscount, int additional_size)
{
    int i = 0, j = 1;
    int **pp = (int *)malloc(sizeof(int *) * (sscount + 2));
    int iind = 0;
    int ipp = 0;
    int *additional = (int *)malloc(sizeof(int) * (additional_size + 1));
    int aid = 0;
    additional[aid++] = additional_size;
    while (j < size)
    {
        if (i == intervals[iind])
        {
            int *temp = (int *)malloc(sizeof(int) * (intervals[iind + 1] + 1));
            iind += 1;
            int ilocal = 0;
            temp[ilocal] = intervals[iind];
            temp[++ilocal] = arr[i];
            ilocal += 1;
            while (arr[j] > arr[i] && j < size && ilocal < intervals[iind] + 1)
            {
                temp[ilocal] = arr[j];
                ilocal += 1;
                j += 1;
            }
            iind++;
            pp[ipp] = temp;
            ipp++;
        }
        else
        {
            additional[aid] = arr[i];
            aid++;
        }
        i = j;
        j += 1;
    }
    pp[sscount] = additional;
    pp[sscount + 1] = NULL;
    return pp;
}

int main()
{
    // хз надо ли ввод массива делать
    int arr[] = {1, 2, 3, 3, 2, 4, 5};
    // int arr[] = {1, 2, 3, 4, 5};
    // int arr[] = {5, 4, 3,2 ,1};
    int len = sizeof(arr) / sizeof(*arr);

    int size_additional = 0;
    int subseqCount = getSubseqCount(arr, len, &size_additional);
    int *intervals = getIntervalsArr(arr, len, subseqCount);

    int **pp = findIncSubseq(arr, len, intervals, subseqCount * 2, subseqCount, size_additional);
    int ipp = 1;
    for (int i = 0; pp[i] != NULL; i++)
    {
        if (pp[i + 1] == NULL)
        {
            for (int j = 0; j < size_additional + 1; j++)
            {
                printf("%d ", pp[i][j]);
            }
        }
        else
        {
            for (int j = 0; j < intervals[ipp] + 1; j++)
            {
                printf("%d ", pp[i][j]);
            }
            ipp += 2;
        }
        printf("\n");
    }
    return 0;
}