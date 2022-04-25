#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// For the time complexity analysis, let n be the number of keys in the BST and h be its height

/*
* Total Time Complexity: θ(1)
*/
BSNode* SortedMultiMap::initNode(TKey key, TValue value)
{
	auto node = new BSNode;
	node->key = key;
	node->values = new TValue[node->capacity];
	node->values[0] = value;
	node->length++;
	return node;
}

/*
* Total Time Complexity: θ(1)
*/
int SortedMultiMap::countDirectDescendants(BSNode* node) const {
	int descendants = 0;
	if (node->rightChild != nullptr) descendants++;
	if (node->leftChild != nullptr) descendants++;
	return descendants;
}

/*
* Total Time Complexity: O(n)
* WC: θ(n)
* BC: θ(1)
*/
void SortedMultiMap::resizeNodeValuesDynamicArray(BSNode* node) {
	auto new_values = new TValue[node->capacity * 2];
	
	for (int i = 0; i < node->capacity; ++i)
		new_values[i] = node->values[i];
	node->capacity *= 2;

	delete node->values;
	node->values = new_values;
}

/*
* Total Time Complexity: O(n)
* WC: θ(n) - the whole tree gets deleted
* BC: θ(1) - a single node gets deleted
*/
void SortedMultiMap::deleteSubTree(BSNode* root) {
	if (root == nullptr) return;

	if (root->leftChild != nullptr)
		deleteSubTree(root->leftChild);
	if (root->rightChild != nullptr)
		deleteSubTree(root->rightChild);

	delete root->values;
	delete root;
}

/*
* Total Time Complexity: θ(1)
*/
void SortedMultiMap::deleteLeafNode(BSNode* node) {
	delete node->values;
	delete node;
}

/*
* Total Time Complexity: θ(1)
*/
SortedMultiMap::SortedMultiMap(Relation r) {
	relation = r;
	length = 0;
}

/*
* Total Time Complexity: O(h) amortized, i.e O(n)
* WC: θ(n) - we need a resize operation and all the values in the map have the same key
* BC: θ(1) - this is the first node added to the tree (hence the added node becomes the tree's root)
* AC: θ(log_2(n))
*/
void SortedMultiMap::add(TKey c, TValue v) {
	auto currentNode = tree.root;
	length++;

	if (currentNode == nullptr) {
		tree.root = initNode(c, v);
		return;
	}

	auto previousNode = currentNode;
	while (currentNode != nullptr) {
		if (currentNode->key == c) {
			if (currentNode->length == currentNode->capacity)
				resizeNodeValuesDynamicArray(currentNode);
			currentNode->values[currentNode->length] = v;
			currentNode->length++;
			return;
		}

		previousNode = currentNode;
		if (relation(currentNode->key, c))
			currentNode = currentNode->rightChild;
		else
			currentNode = currentNode->leftChild;
	}

	auto node = initNode(c, v);
	node->parent = previousNode;

	if (relation(previousNode->key, c))
		previousNode->rightChild = node;
	else
		previousNode->leftChild = node;
}

/*
* Total Time Complexity: O(n)
* WC: θ(n) - we find the key, but all the values in the map have this key. Thus, we need to iterate through all of them when adding to the vector
* BC: θ(1) - the searched key is the root and only one BST value mapped to this key
* AC: θ(log_2(n))
*/
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	auto currentNode = tree.root;
	bool found = false;

	while (currentNode != nullptr && !found) {
		if (currentNode->key == c)
			found = true;
		else if (relation(currentNode->key, c))
			currentNode = currentNode->rightChild;
		else
			currentNode = currentNode->leftChild;
	}

	if (found) {
		for (int i = 0; i < currentNode->length; ++i)
			values.push_back(currentNode->values[i]);
	}

	return values;
}

/*
* Total Time Complexity: O(n)
* WC: θ(n) - the key is found, all the elements of the map have this key and the value to be removed is the last one in the dynamic array of values corresponding to this key
* BC: θ(1) - the key is actually the root of the tree (hence it is found at the first iteration of the first while loop), the values is found on the first position of the dynamic
*			 array of values corresponding to this key and this array of values has at least 2 elements
* AC: θ(log_2(n))
*/
bool SortedMultiMap::remove(TKey c, TValue v) {
	auto currentNode = tree.root;
	auto previousNode = currentNode;
	bool found = false;

	while (currentNode != nullptr && !found) {
		if (currentNode->key == c)
			found = true;
		else if (relation(currentNode->key, c)) {
			previousNode = currentNode;
			currentNode = currentNode->rightChild;
		}
		else {
			previousNode = currentNode;
			currentNode = currentNode->leftChild;
		}
	}

	if (!found) return false;
	int position = -1;
	
	for (int i = 0; i < currentNode->length; ++i) {
		if (currentNode->values[i] == v) {
			position = i;
			break;
		}
	}

	if (position == -1) return false;
	if (currentNode->length > 1) {
		currentNode->length--;
		currentNode->values[position] = currentNode->values[currentNode->length];
		
		length--;
		if (!length)
			tree.root = nullptr;

		return true;
	}

	// the last case is when the pair (c, v) is in the map, but v is the only value mapped to the key c => we have to completely remove the key from the BST
	// currentNode is the node to be removed from the BST

	if (!countDirectDescendants(currentNode)) {  // case 1: the node has no descdendants
		deleteLeafNode(currentNode);
		if (relation(previousNode->key, c))
			previousNode->rightChild = nullptr;
		else
			previousNode->leftChild = nullptr;
	}
	else if (countDirectDescendants(currentNode) == 1) {  // case 2: the node has exactly one descendant
		auto descendant = currentNode->leftChild;
		if (currentNode->rightChild != nullptr)
			descendant = currentNode->rightChild;

		if (relation(previousNode->key, c))
			previousNode->rightChild = descendant;
		else
			previousNode->leftChild = descendant;
		descendant->parent = previousNode;

		if (tree.root->key == c && tree.root->values[0] == v)
			tree.root = descendant;

		deleteLeafNode(currentNode);
	}
	else {  // case 3: the node to be removed has two descendants 
		// first find the minimum of the right subtree (and also its parent)

		auto minimumNode = currentNode->rightChild;
		auto minimumNodeParent = currentNode;

		while (minimumNode->leftChild != nullptr) {
			minimumNodeParent = minimumNode;
			minimumNode = minimumNode->leftChild;
		}

		// "delete" the found minimum node from the right subtree
		if (!countDirectDescendants(minimumNode)) {
			if (minimumNode == currentNode->rightChild)
				minimumNodeParent->rightChild = nullptr;
			else
				minimumNodeParent->leftChild = nullptr;
		}
		else if (countDirectDescendants(minimumNode) == 1) {  // this means that the minimum found node has a right descendant (it cannot have a left one)
			if (minimumNode == currentNode->rightChild) {
				minimumNodeParent->rightChild = minimumNode->rightChild;
				minimumNode->rightChild->parent = minimumNodeParent->rightChild;
			}
			else {
				minimumNodeParent->leftChild = minimumNode->rightChild;
				minimumNode->rightChild->parent = minimumNodeParent->leftChild;
			}
		}

		minimumNode->leftChild = currentNode->leftChild;
		currentNode->leftChild->parent = minimumNode;
		minimumNode->rightChild = currentNode->rightChild;
		currentNode->rightChild->parent = minimumNode;

		if (relation(previousNode->key, c))
			previousNode->rightChild = minimumNode;
		else
			previousNode->leftChild = minimumNode;

		minimumNode->parent = previousNode;

		if (tree.root->key == c && tree.root->values[0] == v) {
			tree.root = minimumNode;
			minimumNode->parent = nullptr;
		}

		deleteLeafNode(currentNode);  // deleteLeadNode() function assumes that the given node is a leaf one; if it is not, it still works, but without managing the subtrees deletion
	}

	length--;
	if (!length)
		tree.root = nullptr;

	return true;
}

/*
* Total Time Complexity: O(n)
* WC: θ(n) - the key is found, all the elements of the map have this key => iterate through all the elements when pushing to the vector
* BC: θ(1) - the key is actually the root of the tree (hence it is found at the first iteration of the first while loop), only one value is mapped to this key and it has one or
*		     zero direct descendants (or even two, if the minimum in the right subtree is found in the first iterations of the while loop)
* AC: θ(log_2(n))
*/
vector<TValue> SortedMultiMap::removeKey(TKey key) {
	auto currentNode = tree.root;
	auto previousNode = currentNode;
	bool found = false;

	while (currentNode != nullptr && !found) {
		if (currentNode->key == key)
			found = true;
		else if (relation(currentNode->key, key)) {
			previousNode = currentNode;
			currentNode = currentNode->rightChild;
		}
		else {
			previousNode = currentNode;
			currentNode = currentNode->leftChild;
		}
	}

	if (!found) return vector<TValue>();

	length -= currentNode->length;
	vector<TValue> result_vector;
	for (int i = 0; i < currentNode->length; ++i)
		result_vector.push_back(currentNode->values[i]);

	if (!countDirectDescendants(currentNode)) {  // case 1: the node has no descdendants
		deleteLeafNode(currentNode);
		if (relation(previousNode->key, key))
			previousNode->rightChild = nullptr;
		else
			previousNode->leftChild = nullptr;
	}
	else if (countDirectDescendants(currentNode) == 1) {  // case 2: the node has exactly one descendant
		auto descendant = currentNode->leftChild;
		if (currentNode->rightChild != nullptr)
			descendant = currentNode->rightChild;

		if (relation(previousNode->key, key))
			previousNode->rightChild = descendant;
		else
			previousNode->leftChild = descendant;
		descendant->parent = previousNode;

		if (tree.root->key == key) {
			tree.root = descendant;
			descendant->parent = nullptr;
		}

		deleteLeafNode(currentNode);
	}
	else {  // case 3: the node to be removed has two descendants 
		// first find the minimum of the right subtree (and also its parent)

		auto minimumNode = currentNode->rightChild;
		auto minimumNodeParent = currentNode;

		while (minimumNode->leftChild != nullptr) {
			minimumNodeParent = minimumNode;
			minimumNode = minimumNode->leftChild;
		}

		// "delete" the found minimum node from the right subtree
		if (!countDirectDescendants(minimumNode)) {
			if (minimumNode == currentNode->rightChild)
				minimumNodeParent->rightChild = nullptr;
			else
				minimumNodeParent->leftChild = nullptr;
		}
		else if (countDirectDescendants(minimumNode) == 1) {  // this means that the minimum found node has a right descendant (it cannot have a left one)
			if (minimumNode == currentNode->rightChild) {
				minimumNodeParent->rightChild = minimumNode->rightChild;
				minimumNode->rightChild->parent = minimumNodeParent->rightChild;
			}
			else {
				minimumNodeParent->leftChild = minimumNode->rightChild;
				minimumNode->rightChild->parent = minimumNodeParent->leftChild;
			}
		}

		minimumNode->leftChild = currentNode->leftChild;
		if (currentNode->leftChild != nullptr)
			currentNode->leftChild->parent = minimumNode;
		minimumNode->rightChild = currentNode->rightChild;
		if (currentNode->rightChild != nullptr)
			currentNode->rightChild->parent = minimumNode;

		if (relation(previousNode->key, key))
			previousNode->rightChild = minimumNode;
		else
			previousNode->leftChild = minimumNode;

		if (minimumNode != nullptr)
			minimumNode->parent = previousNode;

		if (tree.root->key == key) {
			tree.root = minimumNode;
			if (minimumNode != nullptr)
				minimumNode->parent = nullptr;
		}

		deleteLeafNode(currentNode);  // note that deleteLeadNode() function assumes that the given node is a leaf one; if it is not, it still works, but without managing the subtrees deletion
	}

	if (!length)
		tree.root = nullptr;
	return result_vector;
}

/*
* Total Time Complexity: θ(1)
*/
int SortedMultiMap::size() const {
	return length;
}

/*
* Total Time Complexity: θ(1)
*/
bool SortedMultiMap::isEmpty() const {
	return length == 0;
}

/*
* Total Time Complexity: O(n) - because of the iterator's constructor complexity
*/
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

/*
* Total Time Complexity: θ(n)
*/
SortedMultiMap::~SortedMultiMap() {
	if (tree.root == nullptr) return;

	deleteSubTree(tree.root->leftChild);
	deleteSubTree(tree.root->rightChild);
	deleteLeafNode(tree.root);
}
