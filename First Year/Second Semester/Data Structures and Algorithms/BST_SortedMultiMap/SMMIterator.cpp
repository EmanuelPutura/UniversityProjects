#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <iostream>

/*
* Total Time Complexity: O(n)
* WC: θ(n) - all the nodes (but for the root) are a left child of some other node
* BC: θ(1) - the tree is empty
*/
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	currentNode = map.tree.root;
	
	if (currentNode == nullptr) {
		firstNode = nullptr;
		return;
	}

	while (currentNode->leftChild != nullptr)
		currentNode = currentNode->leftChild;
	firstNode = currentNode;
}

/*
* Total Time Complexity: O(n)
*/
void SMMIterator::first(){
	currentNode = map.tree.root;

	if (currentNode == nullptr) {
		firstNode = nullptr;
		return;
	}

	while (currentNode->leftChild != nullptr)
		currentNode = currentNode->leftChild;
	firstNode = currentNode;

	currentIndex = 0;
}

/*
* Total Time Complexity: O(n)
* WC: θ(n) - all the nodes (but for the root and one right child of it) are a left child of some other node and the current node is the root
* BC: θ(1) - for the current key, not all of its values were considered as current elements yet
*/
void SMMIterator::next(){
	if (currentNode == nullptr)
		throw std::exception();

	if (currentIndex < currentNode->length - 1) {
		currentIndex++;
		return;
	}
	else
		currentIndex = 0;

	if (currentNode->rightChild != nullptr) {
		currentNode = currentNode->rightChild;

		while (currentNode->leftChild != nullptr)
			currentNode = currentNode->leftChild;
	}
	else {
		while (currentNode->parent != nullptr && currentNode->parent->rightChild == currentNode)
			currentNode = currentNode->parent;
		if (currentNode != nullptr) currentNode = currentNode->parent;
	}
}

/*
* Total Time Complexity: θ(1)
*/
bool SMMIterator::valid() const{
	if (currentNode == nullptr) return false;
	if (currentNode->length <= currentIndex) return false;
	return true;
}

/*
* Total Time Complexity: θ(1)
*/
TElem SMMIterator::getCurrent() const{
	if (currentNode == nullptr)
		throw std::exception();
	return TElem{ currentNode->key, currentNode->values[currentIndex] };
}


