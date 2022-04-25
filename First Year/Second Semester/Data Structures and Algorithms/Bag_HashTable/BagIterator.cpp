#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <iostream>

using namespace std;

/*
* Time Complexity:
* -> BC: an occupied position is found at the first iteration - θ(1)
* -> WC: There are no elements in the hashtable - θ(m)
* -> Total time complexity: O(m)
*/
BagIterator::BagIterator(const Bag& c): bag(c) {
	position = 0;
	while (position < bag.m && (bag.elems[position] == NULL_TELEM || bag.elems[position] == DELETED))
		position++;
}

/*
* Time Complexity:
* -> BC: an occupied position is found at the first iteration - θ(1)
* -> WC: There are no elements in the hashtable - θ(m)
* -> Total time complexity: O(m)
*/
void BagIterator::first() {
	position = 0;
	while (position < bag.m && (bag.elems[position] == NULL_TELEM || bag.elems[position] == DELETED))
		position++;
}

/*
* Time Complexity:
* -> BC: an occupied position is found at the first iteration - θ(1)
* -> WC: There are no elements in the hashtable - θ(m)
* -> Total time complexity: O(m)
*/
void BagIterator::next() {
	if (!valid())
		throw std::exception();
	position++;
	while (position < bag.m && (bag.elems[position] == NULL_TELEM || bag.elems[position] == DELETED))
		position++;
}

/*
* Time Complexity: θ(1)
*/
bool BagIterator::valid() const {
	return position < bag.m && position >= 0;
}

/*
* Time Complexity: θ(1)
*/
TElem BagIterator::getCurrent() const {
	if (!valid())
		throw std::exception();
	return bag.elems[position];
}
