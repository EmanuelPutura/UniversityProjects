#include "ccheap.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MaxHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);

    CC_HEAP* heap = NULL;
    if (NULL == MaxHeap)
    {
        return -1;
    }

    heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));
    if (NULL == heap)
    {
        return -1;
    }

    memset(heap, 0, sizeof(*heap));

    heap->Count = 0;

    if (NULL == InitialElements)
    {
        heap->Size = INITIAL_SIZE;
        heap->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    }
    else
    {
        heap->Size = InitialElements->Size;
        heap->Array = (int*)malloc(sizeof(int) * InitialElements->Size);
    }

    if (NULL == heap->Array)
    {
        free(heap);
        return -1;
    }

    if (NULL != InitialElements)
    {
        for (int i = 0; i < InitialElements->Count; ++i)
        {
            heap->Array[i] = InitialElements->Array[i];
        }

        BuildMaxHeap(heap);
    }

    heap->IsMaxHeap = 1;
    *MaxHeap = heap;

    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MinHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);

    CC_HEAP* heap = NULL;
    if (NULL == MinHeap)
    {
        return -1;
    }

    heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));
    if (NULL == heap)
    {
        return -1;
    }

    memset(heap, 0, sizeof(*heap));

    heap->Count = 0;

    if (NULL == InitialElements)
    {
        heap->Size = INITIAL_SIZE;
        heap->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    }
    else
    {
        heap->Size = InitialElements->Size;
        heap->Array = (int*)malloc(sizeof(int) * InitialElements->Size);
    }

    if (NULL == heap->Array)
    {
        free(heap);
        return -1;
    }

    if (NULL != InitialElements)
    {
        for (int i = 0; i < InitialElements->Count; ++i)
        {
            heap->Array[i] = InitialElements->Array[i];
        }

        BuildMinHeap(heap);
    }

    heap->IsMaxHeap = 0;
    *MinHeap = heap;

    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);

    if (NULL == Heap)
    {
        return -1;
    }

    CC_HEAP* heap = *Heap;

    free(heap->Array);
    free(heap);

    *Heap = NULL;

    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Heap)
    {
        return -1;
    }

    if (Heap->Count >= Heap->Size)
    {
        if (ResizeHeap(Heap) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    Heap->Array[Heap->Count] = Value;
    Heap->Count++;

    if (Heap->IsMaxHeap != 0)
    {
        MaxHeapBubbleUp(Heap, Heap->Count - 1);
    }
    else
    {
        MinHeapBubbleUp(Heap, Heap->Count - 1);
    }

    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Heap)
    {
        return -1;
    }

    for (int i = Heap->Count - 1; i >= 0; --i)
    {
        if (Heap->Array[i] == Value)
        {
            Heap->Array[i] = Heap->Array[Heap->Count - 1];
            Heap->Count--;

            if (Heap->IsMaxHeap != 0)
            {
                if (MaxHeapify(Heap, i) == -1)
                {
                    return -1;
                }
            }
            else
            {
                if (MinHeapify(Heap, i) == -1)
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);

    if (NULL == Heap)
    {
        return -1;
    }

    if (Heap->Count <= 0)
    {
        return -1;
    }

    *ExtremeValue = Heap->Array[0];
    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);

    if (NULL == Heap)
    {
        return -1;
    }

    if (Heap->Count <= 0)
    {
        return -1;
    }

    *ExtremeValue = Heap->Array[0];
    while (Heap->Array[0] == *ExtremeValue)
    {
        Heap->Array[0] = Heap->Array[Heap->Count - 1];
        Heap->Count--;

        if (Heap->IsMaxHeap)
        {
            if (MaxHeapify(Heap, 0) == -1)
            {
                return -1;
            }
        }
        else
        {
            if (MinHeapify(Heap, 0) == -1)
            {
                return -1;
            }
        }
    }

    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    
    if (NULL == Heap)
    {
        return -1;
    }
    
    return Heap->Count;
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(SortedVector);

    if (NULL == Heap)
    {
        return -1;
    }

    if (NULL == SortedVector)
    {
        return -1;
    }
    
    VecClear(SortedVector);
    for (int i = 0; i < Heap->Count; ++i)
    {
        VecInsertTail(SortedVector, Heap->Array[i]);
    }
    
    if (Heap->IsMaxHeap == 0)
    {
        // Build max heap
        int non_leaves = SortedVector->Count - (SortedVector->Count + 1) / 2;
        for (int i = non_leaves; i >= 0; --i)
        {
            MaxHeapifyVector(SortedVector, i);
        }
    }

    int size = SortedVector->Count;
    int initialCount = SortedVector->Count;

    for (int i = size - 1; i >= 1; --i) {
        int temp = SortedVector->Array[i];
        SortedVector->Array[i] = SortedVector->Array[0];
        SortedVector->Array[0] = temp;

        size--;
        SortedVector->Count--;
        MaxHeapifyVector(SortedVector, 0);
    }
    
    SortedVector->Count = initialCount;
    return 0;
}

int GetLeavesNumber(CC_HEAP* Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    return (Heap->Count + 1) / 2;
}

int MinHeapify(CC_HEAP* MinHeap, int index)
{
    if (NULL == MinHeap)
    {
        return -1;
    }

    int non_leaves = MinHeap->Count - GetLeavesNumber(MinHeap);
    while (index < non_leaves)
    {
        int leftChildIndex = index * 2 + 1;
        int rightChildIndex = index * 2 + 2;
        int minimum = index;

        if (leftChildIndex < MinHeap->Count && MinHeap->Array[leftChildIndex] < MinHeap->Array[minimum])
        {
            minimum = leftChildIndex;
        }
        if (rightChildIndex < MinHeap->Count && MinHeap->Array[rightChildIndex] < MinHeap->Array[minimum])
        {
            minimum = rightChildIndex;
        }

        int temp = MinHeap->Array[index];
        MinHeap->Array[index] = MinHeap->Array[minimum];
        MinHeap->Array[minimum] = temp;
        
        if (minimum == index)
        {
            break;
        }

        index = minimum;
    }

    return 0;
}

int MaxHeapify(CC_HEAP* MaxHeap, int index)
{
    if (NULL == MaxHeap)
    {
        return -1;
    }

    int non_leaves = MaxHeap->Count - GetLeavesNumber(MaxHeap);
    while (index < non_leaves)
    {
        int leftChildIndex = index * 2 + 1;
        int rightChildIndex = index * 2 + 2;
        int maximum = index;

        if (leftChildIndex < MaxHeap->Count && MaxHeap->Array[leftChildIndex] > MaxHeap->Array[maximum])
        {
            maximum = leftChildIndex;
        }
        if (rightChildIndex < MaxHeap->Count && MaxHeap->Array[rightChildIndex] > MaxHeap->Array[maximum])
        {
            maximum = rightChildIndex;
        }
        
        int temp = MaxHeap->Array[index];
        MaxHeap->Array[index] = MaxHeap->Array[maximum];
        MaxHeap->Array[maximum] = temp;

        if (maximum == index)
        {
            break;
        }

        index = maximum;
    }

    return 0;
}

int MaxHeapifyVector(CC_VECTOR* Vector, int index)
{
    if (NULL == Vector)
    {
        return -1;
    }

    int non_leaves = Vector->Count - (Vector->Count + 1) / 2;
    while (index < non_leaves)
    {
        int leftChildIndex = index * 2 + 1;
        int rightChildIndex = index * 2 + 2;
        int maximum = index;

        if (leftChildIndex < Vector->Count && Vector->Array[leftChildIndex] > Vector->Array[maximum])
        {
            maximum = leftChildIndex;
        }
        if (rightChildIndex < Vector->Count && Vector->Array[rightChildIndex] > Vector->Array[maximum])
        {
            maximum = rightChildIndex;
        }

        int temp = Vector->Array[index];
        Vector->Array[index] = Vector->Array[maximum];
        Vector->Array[maximum] = temp;

        if (maximum == index)
        {
            break;
        }

        index = maximum;
    }

    return 0;
}

int MinHeapBubbleUp(CC_HEAP* MinHeap, int index)
{
    if (NULL == MinHeap)
    {
        return -1;
    }

    int parent = (index - 1) / 2;
    while (index && MinHeap->Array[index] < MinHeap->Array[parent])
    {
        int temp = MinHeap->Array[index];
        MinHeap->Array[index] = MinHeap->Array[parent];
        MinHeap->Array[parent] = temp;

        index = parent;
    }

    return 0;
}

int MaxHeapBubbleUp(CC_HEAP* MaxHeap, int index)
{
    if (NULL == MaxHeap)
    {
        return -1;
    }

    int parent = (index - 1) / 2;
    while (index && MaxHeap->Array[index] > MaxHeap->Array[parent])
    {
        int temp = MaxHeap->Array[index];
        MaxHeap->Array[index] = MaxHeap->Array[parent];
        MaxHeap->Array[parent] = temp;

        index = parent;
    }

    return 0;
}

int BuildMaxHeap(CC_HEAP* MaxHeap)
{
    if (NULL == MaxHeap)
    {
        return -1;
    }

    int non_leaves = MaxHeap->Count - GetLeavesNumber(MaxHeap);
    for (int i = non_leaves; i >= 0; --i)
    {
        MaxHeapify(MaxHeap, i);
    }

    return 0;
}

int BuildMinHeap(CC_HEAP* MinHeap)
{
    if (NULL == MinHeap)
    {
        return -1;
    }

    int non_leaves = MinHeap->Count - GetLeavesNumber(MinHeap);
    for (int i = non_leaves; i >= 0; --i)
    {
        MinHeapify(MinHeap, i);
    }

    return 0;
}

int ResizeHeap(CC_HEAP* Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    int* newArray = (int*)malloc(sizeof(int) * Heap->Size * 2);
    if (NULL == newArray)
    {
        return -1;
    }

    for (int i = 0; i < Heap->Count; ++i)
    {
        newArray[i] = Heap->Array[i];
    }

    free(Heap->Array);
    Heap->Array = newArray;
    Heap->Size = Heap->Size * 2;

    return 0;
}
