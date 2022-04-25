#include "cctree.h"
#include "common.h"
#include "string.h"

int TreeCreate(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }

    CC_TREE* tree = (CC_TREE*)malloc(sizeof(CC_TREE));
    if (tree == NULL)
    {
        return -1;
    }

    memset(tree, 0, sizeof(tree));

    tree->Head = NULL;
    tree->Count = 0;

    *Tree = tree;
    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }

    CC_TREE* tree = *Tree;
    TreeDestroyHelper(tree->Head);

    free(tree);
    tree = NULL;

    *Tree = NULL;
    return 0;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (Tree == NULL)
    {
        return -1;
    }

    Tree->Head = TreeInsertHelper(Tree->Head, Value);
    return 0;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree || NULL == Tree->Head)
    {
        return -1;
    }

    while (TreeRemoveNode(Tree, Value) != -1);

    return 0;
}

int TreeContains(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    PTREE_NODE current = Tree->Head;

    while (current != NULL)
    {
        if (current->Value > Value)
        {
            current = current->LeftChild;
        }
        else if (current->Value < Value)
        {
            current = current->RightChild;
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

int TreeGetCount(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    return Tree->Count;
}

int TreeGetHeight(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    return TreeHeigthHelper(Tree->Head);
}

int TreeClear(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);

    if (NULL == Tree)
    {
        return -1;
    }

    TreeDestroyHelper(Tree->Head);

    return 0;
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    if (NULL == Tree->Head)
    {
        return -1;
    }

    TreeTraversePreorder(Tree->Head, &Index, Value);
    return 0;
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    if (NULL == Tree->Head)
    {
        return -1;
    }

    TreeTraverseInorder(Tree->Head, &Index, Value);
    return 0;
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Tree)
    {
        return -1;
    }

    if (NULL == Tree->Head)
    {
        return -1;
    }

    TreeTraversePostorder(Tree->Head, &Index, Value);

    return 0;
}

void TreeDestroyHelper(TREE_NODE* Node)
{
    if (Node == NULL)
        return;

    TreeDestroyHelper(Node->LeftChild);
    TreeDestroyHelper(Node->RightChild);
    free(Node);
    Node = NULL;
}

TREE_NODE* TreeInsertHelper(TREE_NODE* Node, int Value)
{
    if (Node == NULL)
    {
        Node = (TREE_NODE*)malloc(sizeof(TREE_NODE));
        if (NULL == Node)
        {
            return NULL;
        }

        Node->Value = Value;
        Node->LeftChild = NULL;
        Node->RightChild = NULL;

        return Node;
    }

    if (Node->Value > Value)
    {
        Node->LeftChild = TreeInsertHelper(Node->LeftChild, Value);
    }
    else
    {
        Node->RightChild = TreeInsertHelper(Node->RightChild, Value);
    }

    return Node;
}

int TreeRemoveNode(CC_TREE* Tree, int Value)
{
    if (NULL == Tree)
    {
        return -1;
    }

    if (NULL == Tree->Head)
    {
        return -1;
    }

    // If the head has the given value
    if (Tree->Head->Value == Value)
    {
        // If the head has no children
        if (Tree->Head->LeftChild == NULL && Tree->Head->RightChild == NULL)
        {
            free(Tree->Head);
            Tree->Head = NULL;
            return 0;
        }

        // If the only child of the head is the left one
        if (Tree->Head->LeftChild != NULL && Tree->Head->RightChild == NULL)
        {
            PTREE_NODE removedNode = Tree->Head;
            Tree->Head = Tree->Head->LeftChild;
            free(removedNode);
            removedNode = NULL;

            return 0;
        }

        // If the only child of the head is the right one
        if (Tree->Head->LeftChild == NULL && Tree->Head->RightChild != NULL)
        {
            PTREE_NODE removedNode = Tree->Head;
            Tree->Head = Tree->Head->RightChild;
            free(removedNode);
            removedNode = NULL;

            return 0;
        }

        // If the head has two children
        if (Tree->Head->LeftChild != NULL && Tree->Head->RightChild != NULL)
        {
            PTREE_NODE maxParent = TreeGetMaxParent(Tree->Head->LeftChild);

            if (maxParent == NULL)
            {
                PTREE_NODE removedNode = Tree->Head;
                Tree->Head = Tree->Head->LeftChild;
                free(removedNode);
                removedNode = NULL;

                return 0;
            }

            Tree->Head->Value = maxParent->RightChild->Value;
            PTREE_NODE removedNode = maxParent->RightChild;
            maxParent->RightChild = maxParent->RightChild->LeftChild;
            free(removedNode);

            return 0;
        }
    }

    PTREE_NODE parent = NULL;
    PTREE_NODE current = Tree->Head;

    while (current != NULL)
    {
        if (current->Value < Value)
        {
            parent = current;
            current = current->RightChild;
        }
        else if (current->Value > Value)
        {
            parent = current;
            current = current->LeftChild;
        }
        else
        {
            if (current->LeftChild == NULL && current->RightChild == NULL)
            {
                if (parent->LeftChild == current)
                {
                    parent->LeftChild = NULL;
                }
                else
                {
                    parent->RightChild = NULL;
                }

                free(current);
                current = NULL;

                return 0;
            }

            if (current->LeftChild != NULL && current->RightChild == NULL)
            {
                if (parent->LeftChild == current)
                {
                    parent->LeftChild = current->LeftChild;
                    free(current);
                    current = NULL;
                }
                else
                {
                    parent->RightChild = current->LeftChild;
                    free(current);
                    current = NULL;
                }

                return 0;
            }

            if (current->LeftChild == NULL && current->RightChild != NULL)
            {
                if (parent->LeftChild == current)
                {
                    parent->LeftChild = current->RightChild;
                    free(current);
                    current = parent->LeftChild;
                }
                else
                {
                    parent->RightChild = current->RightChild;
                    free(current);
                    current = parent->RightChild;
                }

                return 0;
            }

            if (current->LeftChild != NULL && current->RightChild != NULL)
            {
                if (parent->LeftChild == current)
                {
                    PTREE_NODE parentOfMax = TreeGetMaxParent(current->LeftChild);

                    if (parentOfMax == NULL)
                    {
                        PTREE_NODE nodeToRemove = current;
                        current = current->LeftChild;
                        parent->LeftChild = current;
                        free(nodeToRemove);
                        nodeToRemove = NULL;

                        return 0;
                    }

                    current->Value = parentOfMax->RightChild->Value;
                    PTREE_NODE nodeToRemove = parentOfMax->RightChild;
                    parentOfMax->RightChild = parentOfMax->RightChild->LeftChild;
                    free(nodeToRemove);
                }
                else
                {
                    PTREE_NODE parentOfMax = TreeGetMaxParent(current->LeftChild);

                    if (parentOfMax == NULL)
                    {
                        PTREE_NODE nodeToRemove = current;
                        current = current->LeftChild;
                        parent->RightChild = current;
                        free(nodeToRemove);
                        nodeToRemove = NULL;

                        return 0;
                    }

                    current->Value = parentOfMax->RightChild->Value;
                    PTREE_NODE nodeToRemove = parentOfMax->RightChild;
                    parentOfMax->RightChild = parentOfMax->RightChild->LeftChild;
                    free(nodeToRemove);
                }

                return 0;
            }
        }
    }

    return -1;
}

PTREE_NODE TreeGetMaxParent(PTREE_NODE TreeNode)
{
    if (TreeNode->RightChild == NULL)
        return NULL;

    while (TreeNode->RightChild->RightChild != NULL)
    {
        TreeNode = TreeNode->RightChild;
    }

    return TreeNode;
}

void TreeTraversePreorder(PTREE_NODE Node, int* Index, int* Value)
{
    if (NULL == Node)
    {
        return;
    }

    if (*Index <= 0)
    {
        return;
    }

    if (*Index == 1)
    {
        *Value = Node->Value;
    }

    *Index -= 1;
    TreeTraversePreorder(Node->LeftChild, Index, Value);
    TreeTraversePreorder(Node->RightChild, Index, Value);
}

void TreeTraverseInorder(PTREE_NODE Node, int* Index, int* Value)
{
    if (NULL == Node)
    {
        return;
    }

    if (*Index <= 0)
    {
        return;
    }

    if (*Index == 1)
    {
        *Value = Node->Value;
    }

    TreeTraverseInorder(Node->LeftChild, Index, Value);
    *Index -= 1;
    TreeTraverseInorder(Node->RightChild, Index, Value);
}

void TreeTraversePostorder(PTREE_NODE Node, int* Index, int* Value)
{
    if (NULL == Node)
    {
        return;
    }

    if (*Index <= 0)
    {
        return;
    }


    if (*Index == 1)
    {
        *Value = Node->Value;
    }

    TreeTraversePostorder(Node->LeftChild, Index, Value);
    TreeTraversePostorder(Node->RightChild, Index, Value);
    *Index -= 1;
}

int TreeHeigthHelper(PTREE_NODE Node)
{
    if (Node == NULL)
    {
        return -1;
    }
    else
    {
        // compute the depth of each subtree
        int leftDepth = TreeHeigthHelper(Node->LeftChild);
        int rightDepth = TreeHeigthHelper(Node->RightChild);

        // get the max of the two computed depths
        if (leftDepth > rightDepth)
        {
            return(leftDepth + 1);
        }
        else
        {
            return(rightDepth + 1);
        }
    }
}
