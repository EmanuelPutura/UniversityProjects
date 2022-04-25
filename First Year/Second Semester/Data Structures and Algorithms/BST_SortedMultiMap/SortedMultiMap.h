#pragma once
//DO NOT INCLUDE SMMITERATOR

#pragma warning(disable:6011)

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

#define INIT_CAPACITY 5

struct BSNode {
    TKey key;               // the key in the map
    TValue* values;         // the array of values corresponding to the key
    int length = 0;
    int capacity = INIT_CAPACITY;

    BSNode* leftChild = nullptr;      // left child of the node
    BSNode* rightChild = nullptr;     // right child of the node
    BSNode* parent = nullptr;         // the parent of the node
};

struct BinarySearchTree {
    BSNode* root = nullptr;
};

class SortedMultiMap {
	friend class SMMIterator;
    private:
        Relation relation;
        BinarySearchTree tree;
        int length;      // the number of (key, value) pairs in the map

        BSNode* initNode(TKey key, TValue value);
        int countDirectDescendants(BSNode* node) const;

        void resizeNodeValuesDynamicArray(BSNode* node);
        void deleteSubTree(BSNode* root);
        void deleteLeafNode(BSNode* node);
    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);
    
    //removes a key together with all its values 
    //returns a vector with the values that were previously associated to this value (and were removed) 
    vector<TValue> removeKey(TKey key);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
