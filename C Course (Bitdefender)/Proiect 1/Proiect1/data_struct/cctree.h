#pragma once

typedef struct _TREE_NODE {
    int Value;
    struct _TREE_NODE* LeftChild;
    struct _TREE_NODE* RightChild;
} TREE_NODE, *PTREE_NODE;

typedef struct _CC_TREE {
    PTREE_NODE Head;
    int Count;
} CC_TREE;

int TreeCreate(CC_TREE **Tree);
int TreeDestroy(CC_TREE **Tree);

// Duplicates are allowed
int TreeInsert(CC_TREE *Tree, int Value);

// Removes all elements equal to Value
int TreeRemove(CC_TREE *Tree, int Value);


//  Returns:
//       1  - Tree contains Value
//       0  - Tree does not contain Value
//      -1  - Error or invalid parameter
int TreeContains(CC_TREE *Tree, int Value);

// Returns the number of elements in Tree or -1 in case of error or invalid parameter
int TreeGetCount(CC_TREE *Tree);

// Returns the height of Tree or -1 in case of error or invalid parameter
int TreeGetHeight(CC_TREE *Tree);

// Removes every element of the tree
int TreeClear(CC_TREE *Tree);

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value);

static void TreeDestroyHelper(TREE_NODE* Node);

static TREE_NODE* TreeInsertHelper(TREE_NODE* Node, int Value);

static PTREE_NODE TreeGetMaxParent(PTREE_NODE Tree);

static int TreeRemoveNode(CC_TREE* Tree, int Value);

static void TreeTraversePreorder(PTREE_NODE Node, int* Index, int* Value);

static void TreeTraverseInorder(PTREE_NODE Node, int* Index, int* Value);

static void TreeTraversePostorder(PTREE_NODE Node, int* Index, int* Value);

static int TreeHeigthHelper(PTREE_NODE Node);
