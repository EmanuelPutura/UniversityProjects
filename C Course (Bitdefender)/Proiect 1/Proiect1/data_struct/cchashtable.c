#include <string.h>
#include "cchashtable.h"
#include "common.h"

#define INITIAL_SIZE    31
#define MAX_LOAD_FACTOR 0.75

int HtCreate(CC_HASH_TABLE **HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_HASH_TABLE* htb = NULL;

    if (NULL == HashTable)
    {
        return -1;
    }

    htb = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));
    if (NULL == htb)
    {
        return -1;
    }

    memset(htb, 0, sizeof(*htb));

    htb->Count = 0;
    htb->Size = INITIAL_SIZE;
    htb->Heads = (PLIST_NODE*)malloc(sizeof(PLIST_NODE) * INITIAL_SIZE);

    if (NULL == htb->Heads)
    {
        free(htb);
        return -1;
    }

    memset(htb->Heads, 0, sizeof(PLIST_NODE) * INITIAL_SIZE);
    *HashTable = htb;
    return 0;
}

int HtDestroy(CC_HASH_TABLE **HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    CC_HASH_TABLE* htb = *HashTable;

    if (NULL == HashTable)
    {
        return -1;
    }

    for (int i = 0; i < htb->Size; ++i)
    {
        PLIST_NODE current = htb->Heads[i];

        while (NULL != current)
        {
            PLIST_NODE next = current->Next;
            free(current->Key);
            free(current);
            current = next;
        }
    }

    free(htb->Heads);
    free(htb);

    *HashTable = NULL;
    return 0;
}

int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    if (HtHasKey(HashTable, Key) == 1)
    {
        return -1;
    }

    if (GetLoadFactor(HashTable) >= MAX_LOAD_FACTOR)
    {
        if (ResizeAndRehash(HashTable) == -1)
        {
            return -1;
        }
    }

    int hash = Hash(HashTable, Key);
    int keyLength = Strlen(Key) + 1;

    PLIST_NODE newNode = (PLIST_NODE)malloc(sizeof(LIST_NODE));
    if (NULL == newNode)
    {
        return -1;
    }

    newNode->Key = (char*)malloc(keyLength * sizeof(char));
    if (NULL == newNode->Key)
    {
        return -1;
    }
    
    Strcpy(newNode->Key, Key);
    newNode->Value = Value;
    newNode->Next = HashTable->Heads[hash];
    HashTable->Heads[hash] = newNode;
    HashTable->Count++;

    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    PLIST_NODE current = HashTable->Heads[Hash(HashTable, Key)];
    while (NULL != current)
    {
        if (Strcmp(Key, current->Key) == 0)
        {
            *Value = current->Value;
            return 0;
        }

        current = current->Next;
    }

    return -1;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    PLIST_NODE current = HashTable->Heads[Hash(HashTable, Key)];
    PLIST_NODE previous = NULL;

    while (NULL != current)
    {
        if (Strcmp(Key, current->Key) == 0)
        {
            if (NULL == previous)
            {
                HashTable->Heads[Hash(HashTable, Key)] = current->Next;
            }
            else
            {
                previous->Next = current->Next;
            }

            free(current->Key);
            free(current);

            HashTable->Count--;

            return 0;
        }

        previous = current;
        current = current->Next;
    }

    return -1;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    PLIST_NODE current = HashTable->Heads[Hash(HashTable, Key)];
    while (NULL != current)
    {
        if (Strcmp(Key, current->Key) == 0)
        {
            return 1;
        }

        current = current->Next;
    }

    return 0;
}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    CC_HASH_TABLE_ITERATOR *iterator = NULL;

    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable)
    {
        return -1;
    }
    if (NULL == Iterator)
    {
        return -1;
    }
    if (NULL == Key)
    {
        return -1;
    }

    iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
    if (NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;
    iterator->Position = 0;
    iterator->CurrentNode = NULL;

    if (HashTable->Count == 0)
    {
        return -2;
    }

    PLIST_NODE current = HashTable->Heads[0];
    
    int i = 0;
    while (NULL == current)
    {
        ++i;
        current = HashTable->Heads[i];
    }

    *Key = current->Key;
    iterator->CurrentNode = current;
    iterator->Position = i;

    *Iterator = iterator;

    return 0;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Iterator);

    if (NULL == Iterator || NULL == Key)
    {
        return -1;
    }

    if (NULL == Iterator->CurrentNode->Next)
    {
        int i = Iterator->Position + 1;
        PLIST_NODE current = Iterator->HashTable->Heads[i];

        while (NULL == current)
        {
            ++i;
            current = Iterator->HashTable->Heads[i];
        }

        Iterator->Position = i;
        Iterator->CurrentNode = current;
        
        if (NULL == current)
        {
            return -2;
        }
    }
    else
    {
        Iterator->CurrentNode = Iterator->CurrentNode->Next;
    }

    return 0;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
    CC_UNREFERENCED_PARAMETER(Iterator);

    free(*Iterator);
    return -1;
}

int HtClear(CC_HASH_TABLE *HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (NULL == HashTable)
    {
        return -1;
    }

    for (int i = 0; i < HashTable->Size; ++i)
    {
        PLIST_NODE current = HashTable->Heads[i];

        while (NULL != current)
        {
            PLIST_NODE next = current->Next;
            free(current->Key);
            free(current);
            current = next;
        }

        HashTable->Heads[i] = NULL;
    }

    HashTable->Count = 0;
    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (NULL == HashTable)
    {
        return -1;
    }

    return HashTable->Count;
}

int CharHash(char* str)
{
    int hash = 5381;
    int c;
    while (c = *str++)
    {
        hash = ((hash << 5) + hash) ^ c; /* hash * 33 ^ c */
    }

    return hash;
}

int IntHash(CC_HASH_TABLE* HashTable, int no)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    return no % HashTable->Size;
}

int Hash(CC_HASH_TABLE* HashTable, char* str)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    return IntHash(HashTable, CharHash(str));
}

int Strcmp(char* X, char* Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }

        // move to the next pair of characters
        X++;
        Y++;
    }

    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int Strlen(char* str)
{
    for (int len = 0;; ++len)
    {
        if (str[len] == 0)
        {
            return len;
        }
    }
}

// Function to implement `strcpy()` function
char* Strcpy(char* destination, char* source)
{
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }

    // take a pointer pointing to the beginning of the destination string
    char* ptr = destination;

    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    // include the terminating null character
    *destination = '\0';

    // the destination is returned by standard `strcpy()`
    return ptr;
}

double GetLoadFactor(CC_HASH_TABLE* HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    return HashTable->Count / (double)HashTable->Size;
}

int ResizeAndRehash(CC_HASH_TABLE* HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    int newSize = 2 * HashTable->Size;

    PLIST_NODE* newHeads = (PLIST_NODE*)malloc(sizeof(PLIST_NODE) * newSize);
    if (NULL == newHeads)
    {
        return -1;
    }

    memset(newHeads, 0, sizeof(PLIST_NODE) * newSize);
    int oldSize = HashTable->Size;
    HashTable->Size = newSize;

    for (int i = 0; i < oldSize; ++i)
    {
        PLIST_NODE current = HashTable->Heads[i];
        
        while (NULL != current)
        {
            int newPosition = Hash(HashTable, current->Key);
            if (newPosition == -1)
            {
                return -1;
            }

            PLIST_NODE next = current->Next;

            if (NULL != newHeads[newPosition])
            {
                current->Next = newHeads[newPosition];
                newHeads[newPosition] = current;
            }
            else
            {
                current->Next = NULL;
                newHeads[newPosition] = current;
            }

            current = next;
        }
    }

    return 0;
}
