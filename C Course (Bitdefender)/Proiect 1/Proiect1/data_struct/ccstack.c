#include "ccstack.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int StCreate(CC_STACK **Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    CC_STACK *stk = NULL;
    if (NULL == Stack)
    {
        return -1;
    }

    stk = (CC_STACK*)malloc(sizeof(CC_STACK));
    if (NULL == stk)
    {
        return -1;
    }

    memset(stk, 0, sizeof(*stk));

    stk->Count = 0;
    stk->Size = INITIAL_SIZE;
    stk->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == stk->Array)
    {
        free(stk);
        return -1;
    }

    *Stack = stk;

    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_STACK* stk = *Stack;

    if (NULL == Stack)
    {
        return -1;
    }

    free(stk->Array);
    free(stk);

    *Stack = NULL;

    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Count >= Stack->Size)
    {
        if (ResizeStack(Stack) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    Stack->Array[Stack->Count] = Value;
    Stack->Count++;

    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Count <= 0)
    {
        return -1;
    }

    Stack->Count--;
    *Value = Stack->Array[Stack->Count];

    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Count <= 0)
    {
        return -1;
    }

    *Value = Stack->Array[Stack->Count - 1];
    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    return Stack->Count == 0 ? 1 : 0;
}

int StGetCount(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    return Stack->Count;
}

int StClear(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    Stack->Count = 0;
    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(StackToPush);

    if (NULL == Stack || NULL == StackToPush)
    {
        return -1;
    }

    if ((Stack->Count + StackToPush->Count) >= Stack->Size)
    {
        if (ResizeStack(Stack) != 0)
        {
            return -1;  // if resize failed, then -1 is returned (error code)
        }
    }

    int current = -1;
    while (StackToPush->Count > 0)
    {
        if (StPop(StackToPush, &current) == -1)
        {
            return -1;
        }

        if (StPush(Stack, current) == -1)
        {
            return -1;
        }
    }

    return 0;
}

int ResizeStack(CC_STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    int* newArray = (int*)malloc(sizeof(int) * Stack->Size * 2);
    if (NULL == newArray)
    {
        return -1;
    }

    for (int i = 0; i < Stack->Count; ++i)
    {
        newArray[i] = Stack->Array[i];
    }

    free(Stack->Array);
    Stack->Array = newArray;
    Stack->Size = Stack->Size * 2;

    return 0;
}
