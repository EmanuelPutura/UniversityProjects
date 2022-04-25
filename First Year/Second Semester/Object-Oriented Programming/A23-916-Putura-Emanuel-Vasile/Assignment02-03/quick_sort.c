#include "quick_sort.h"

int partition(void **arr, int low, int high, bool (*comparisonFunc)(void*, void*), void* (*getFunc)(void*), void (*swapFunc)(void*, void*))
{
    void* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (comparisonFunc(getFunc(pivot), getFunc(arr[j])))
        {
            i++;
            swapFunc(arr[i], arr[j]);
        }
    }
    swapFunc(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(void **arr, int low, int high, bool (*comparisonFunc)(void*, void*), void* (*getFunc)(void*), void (*swapFunc)(void*, void*))
{
    if (low < high)
    {
        int pi = partition(arr, low, high, comparisonFunc, getFunc, swapFunc);
        quickSort(arr, low, pi - 1, comparisonFunc, getFunc, swapFunc);
        quickSort(arr, pi + 1, high, comparisonFunc, getFunc, swapFunc);
    }
}
