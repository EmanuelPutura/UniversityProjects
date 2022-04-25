#include "ccvector.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;

    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if (ResizeVector(Vector) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if (ResizeVector(Vector) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if (ResizeVector(Vector) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    for (int i = Vector->Count - 1; i > Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index + 1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);

    if (NULL == Vector)
    {
        return -1;
    }

    for (int i = Index; i < Vector->Count - 1; ++i)
    {
        Vector->Array[i] = Vector->Array[i + 1];
    }

    Vector->Count--;
    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < 0 || Index >= Vector->Count)
    {
        return -1;
    }

    *Value = Vector->Array[Index];
    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return 0;
    }

    Vector->Count = 0;
    return 0;
}

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return 0;
    }

    if (QuickSort(Vector, 0, Vector->Count - 1) == -1)
    {
        return -1;
    }

    return 0;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
    CC_UNREFERENCED_PARAMETER(DestVector);
    CC_UNREFERENCED_PARAMETER(SrcVector);

    if (NULL == DestVector || NULL == SrcVector)
    {
        return -1;
    }

    if ((DestVector->Count + SrcVector->Count) >= DestVector->Size)
    {
        if (ResizeVector(DestVector) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    for (int i = 0; i < SrcVector->Count; ++i)
    {
        DestVector->Array[DestVector->Count + i] = SrcVector->Array[i];
    }

    DestVector->Count = DestVector->Count + SrcVector->Count;
    return 0;
}

int ResizeVector(CC_VECTOR* Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    int *newArray = (int*)malloc(sizeof(int) * Vector->Size * 2);
    if (NULL == newArray)
    {
        return -1;
    }

    for (int i = 0; i < Vector->Count; ++i)
    {
        newArray[i] = Vector->Array[i];
    }
    
    free(Vector->Array);
    Vector->Array = newArray;
    Vector->Size = Vector->Size * 2;

    return 0;
}

int QuickSortPartition(CC_VECTOR* Vector, int begin, int end)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (begin < 0 || begin >= Vector->Count || end < 0 || end >= Vector->Count)
    {
        return -1;
    }

    int pivot = Vector->Array[end];
    int i = begin - 1;
    for (int j = begin; j < end; ++j) {
        if (Vector->Array[j] < pivot) {
            i++;

            int temp = Vector->Array[i];
            Vector->Array[i] = Vector->Array[j];
            Vector->Array[j] = temp;
        }
    }

    int temp = Vector->Array[end];
    Vector->Array[end] = Vector->Array[i + 1];
    Vector->Array[i + 1] = temp;

    return i + 1;
}

int QuickSort(CC_VECTOR* Vector, int begin, int end)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (begin < end) {
        int pivot_index = QuickSortPartition(Vector, begin, end);
        if (QuickSort(Vector, begin, pivot_index - 1) == -1 || QuickSort(Vector, pivot_index + 1, end) == -1)
        {
            return -1;
        }
    }

    return 0;
}
