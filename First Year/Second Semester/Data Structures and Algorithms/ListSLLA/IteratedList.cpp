
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

#include <iostream>

#define INITCAPACITY 1000

// Let n be the number of elements in the list (for the time complexity analysis)

/*
* Time Complexity Analysis
* Total Time Complexity: θ(n)
*	(resize is needed <=> current capacity = n)
*/
void IteratedList::resize() {
	TElem* new_elements = new TElem[capacity * 2];
	int* new_next = new int[capacity * 2];

	for (size_t i = 0; i < capacity; ++i) {
		new_elements[i] = elements[i];
		new_next[i] = next[i];
	}

	for (size_t i = capacity; i < capacity * 2 - 1; ++i)
		new_next[i] = i + 1;
	new_next[capacity * 2 - 1] = -1;

	delete[] elements;
	delete[] next;

	elements = new_elements;
	next = new_next;
	first_empty = capacity;
	capacity *= 2;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(INITCAPACITY) => θ(1)
*/
IteratedList::IteratedList() {
	capacity = INITCAPACITY;
	head = -1;
	first_empty = 0;
	length = 0;
	elements = new TElem[capacity];
	next = new int[capacity];

	for (size_t i = 0; i < capacity - 1; ++i)
		next[i] = i + 1;
	next[capacity - 1] = -1;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
int IteratedList::size() const {
	return length;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(INITCAPACITY) => θ(1)
*/
bool IteratedList::isEmpty() const {
	return length == 0;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(INITCAPACITY) => θ(1)
*/
ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(INITCAPACITY) => θ(1)
*/
TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid())
		throw std::exception();
	return pos.getCurrent();
}

/*
* Time Complexity Analysis
* BC: the element to be removed is found at the first iteration of the while loop: θ(1)
* WC: the element to be removed is found at the last iteration of the while loop: θ(n)
* Total Time Complexity: O(n)
*/
TElem IteratedList::remove(ListIterator& pos) {
	if (!pos.valid())
		throw std::exception();

	TElem element = pos.getCurrent();
	int index = pos.current;
	int current = head, previous = -1;

	// the position is valid, hence we know for sure that the element exists in the list => current cannot be -1
	while (current != index) {
		previous = current;
		current = next[current];
	}

	// remove head case
	if (current == head)
		head = next[head];
	else
		next[previous] = next[current];

	// now add the current position to the empty spaces
	next[current] = first_empty;
	first_empty = current;
	pos.next();
	length--;

	return element;
}

/*
* Time Complexity Analysis
* BC: there is no element between start and end positions => nothing to remove: θ(1)
* WC: start is an iterator set to the beginning of the list, end is set to the end of the list => all the elements have to be removed: θ(n)
* Total Time Complexity: O(n)
*/
void IteratedList::removeBetween(ListIterator start, ListIterator end) {
	if (!start.valid() || !end.valid())
		throw std::exception();

	int previous = start.current;
	start.next();
	int s_index = start.current, e_index = end.current;   // [s_index, e_index)
	int current = s_index;

	int cnt = 0;
	while (current != e_index && (current != -1 || cnt == 0)) {
		current = next[current];
		cnt++;
	}
	if (current != e_index)
		throw std::exception();

	current = s_index;

	while (current != e_index) {
		if (current == head) {
			head = next[head];
		}
		else {
			next[previous] = next[current];
		}

		int pos = current;
		current = next[current];
		next[pos] = first_empty;
		first_empty = pos;
		length--;
	}
}

/*
* Time Complexity Analysis
* BC: the searched element is found at the first iteration of the while loop: θ(1)
* WC: the searched element is found at the last iteration of the while loop: θ(n)
* Total Time Complexity: O(n)
*/
ListIterator IteratedList::search(TElem e) const {
	auto iterator = first();
	while (iterator.valid() && iterator.getCurrent() != e)
		iterator.next();
	return iterator;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid())
		throw std::exception();

	TElem old_value = pos.getCurrent();
	int index = pos.current;
	elements[index] = e;

	return old_value;
}

/*
* Time Complexity Analysis
* BC: no resize is needed: θ(1)
* WC: resize is needed: θ(n)
* Total Time Complexity: θ(1) amortized
*/
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid())
		throw std::exception();
	if (first_empty == -1)
		resize();

	int current = pos.current;
	int new_position = first_empty;
	first_empty = next[first_empty];
	elements[new_position] = e;
	next[new_position] = next[current];
	next[current] = new_position;

	pos.next();
	length++;
}

/*
* Time Complexity Analysis
* BC: no resize is needed and the list is empty: θ(1)
* WC: resize is needed and/or the list is not empty: θ(n)
* Total Time Complexity: O(n)
*/
void IteratedList::addToEnd(TElem e) {
	// if resize is needed
	if (first_empty == -1)
		resize();

	// case when this is the first element added to the list
	if (head == -1) {
		head = first_empty;
		elements[first_empty] = e;
		first_empty = next[first_empty];
		next[head] = -1;
	}
	else {
		int current = head;
		while (next[current] != -1)
			current = next[current];

		next[current] = first_empty;
		elements[first_empty] = e;
		int new_position = first_empty;
		first_empty = next[first_empty];
		next[new_position] = -1;
	}
	length++;
}

/*
* Time Complexity Analysis
* BC: no resize is needed: θ(1)
* WC: resize is needed: θ(n)
* Total Time Complexity: θ(1) amortized
*/
void IteratedList::addToBeginning(TElem e) {
	if (first_empty == -1)
		resize();

	int new_position = first_empty;
	first_empty = next[first_empty];
	next[new_position] = head;
	head = new_position;
	elements[new_position] = e;
	length++;
}

/*
* Time Complexity Analysis
* Total Time Complexity: θ(1)
*/
IteratedList::~IteratedList() {
	delete[] elements;
	delete[] next;
}
