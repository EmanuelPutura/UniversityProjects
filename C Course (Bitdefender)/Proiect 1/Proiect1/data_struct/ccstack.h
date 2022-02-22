#pragma once

typedef struct _CC_STACK{
    int* Array;
    int Size;
    int Count;
} CC_STACK;

int StCreate(CC_STACK **Stack);
int StDestroy(CC_STACK **Stack);

int StPush(CC_STACK *Stack, int Value);
int StPop(CC_STACK *Stack, int *Value);

// Gets top of stack without popping the value
int StPeek(CC_STACK *Stack, int *Value);

//  Returns:
//       1  - Stack is empty
//       0  - Stack is not empty
//      -1  - Error or invalid parameter
int StIsEmpty(CC_STACK *Stack);

// Returns the number of elements in the stack
int StGetCount(CC_STACK *Stack);

// Removes all elements from the stack
int StClear(CC_STACK *Stack);

// StPushStack removes all the elements from the StackToPush and appends
// them to the first stack
// ex: Stack1: 1, 2, 3
//     Stack2: 1, 4, 5
// After push: Stack1: 1, 2, 3, 1, 4, 5
//             Stack2: empty
int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush);

// Resizes the vector by reallocating the memory, increasing the capacity of the vector
static int ResizeStack(CC_STACK *Stack);
