#include "SetIterator.h"
#include "Set.h"

#include <exception>

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
SetIterator::SetIterator(const Set& m) : set(m)
{
	currentElement = m.sl_list.head;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
void SetIterator::first() {
	currentElement = set.sl_list.head;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
void SetIterator::next() {
	if (currentElement == nullptr)
		throw std::exception();
	currentElement = currentElement->next;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
TElem SetIterator::getCurrent()
{
	if (currentElement == nullptr)
		throw std::exception();
	return currentElement->info;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
bool SetIterator::valid() const {
	return currentElement != nullptr;
}



