#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
ListIterator::ListIterator(const IteratedList& list) : list(list), current(list.head) {
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
void ListIterator::first() {
	current = list.head;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
void ListIterator::next() {
	if (!valid())
		throw std::exception();
	current = list.next[current];
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
bool ListIterator::valid() const {
	return current != -1;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
TElem ListIterator::getCurrent() const {
	if (!valid())
		throw std::exception();
	return list.elements[current];
}



