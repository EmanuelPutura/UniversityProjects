#pragma warning(disable:6386)

#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

/*
* Time Complexity Analysis: θ(1)
*/
Bag::Bag() {
	this->unique_capacity = this->positions_capacity = 1;  // default initial capacity for the dynamic arrays
	this->unique_length = this->positions_length = 0;  // start position in the dynamic arrays
	this->unique_elements = new TElem[this->unique_capacity];
	this->positions_elements = new int[this->positions_capacity];
}

Bag::Bag(const Bag& other) {
	delete[] this->unique_elements;
	delete[] this->positions_elements;

	this->unique_capacity = other.unique_capacity;
	this->positions_capacity = other.positions_capacity;

	this->unique_elements = new TElem[this->unique_capacity];
	this->positions_elements = new int[this->positions_capacity];

	this->unique_length = other.unique_length;
	this->positions_length = other.positions_length;

	for (int i = 0; i < this->unique_length; ++i)
		this->unique_elements[i] = other.unique_elements[i];
	for (int i = 0; i < this->unique_length; ++i)
		this->positions_elements[i] = other.positions_elements[i];
}

Bag& Bag::operator=(const Bag& other)
{
	delete[] this->unique_elements;
	delete[] this->positions_elements;

	this->unique_capacity = other.unique_capacity;
	this->positions_capacity = other.positions_capacity;

	this->unique_elements = new TElem[this->unique_capacity];
	this->positions_elements = new int[this->positions_capacity];

	this->unique_length = other.unique_length;
	this->positions_length = other.positions_length;

	for (int i = 0; i < this->unique_length; ++i)
		this->unique_elements[i] = other.unique_elements[i];
	for (int i = 0; i < this->unique_length; ++i)
		this->positions_elements[i] = other.positions_elements[i];

	return *this;
}

/*
* Time Complexity Analysis:
* Let n be the number of elements in the bag and u be the number of unique elements in the bag (u <= n).
* BC: θ(1) - when all best cases from the below cycles occur
* WC: θ(n) - when all worst cases from the below cycles occur
* Total complexity: O(n) (for asymptotic time analysis)
* (for amortized time analysis: O(u) amortized)
*/
void Bag::add(TElem elem) {
	/*
	* BC: θ(1) - when the if condition is false
	* WC: θ(n) - when the if condition is true
	* Total Complexity: O(n) (for asymptotic time analysis)
	*					θ(1) amortized (for amortized time analysis)
	*/
	// resize the positions dynamic array if needed
	if (this->positions_length == this->positions_capacity) {
		this->positions_capacity *= 2;
		int* new_elems = new int[this->positions_capacity];
		for (int i = 0; i < this->positions_length; ++i)
			new_elems[i] = this->positions_elements[i];
		delete[] this->positions_elements;
		this->positions_elements = new_elems;
	}

	/*
	* BC: the element is found on the first iteration => θ(1)
	* WC: the element is not found => θ(u)
	* AC: θ(u)
	* Total complexity: O(u)
	*/
	int position = -1;
	for (int i = 0; i < this->unique_length; ++i) {
		if (elem == this->unique_elements[i]) {
			position = i;
			break;
		}
	}

	/*
	* BC: θ(1) - when no resize is needed
	* WC: θ(u) - when resize is needed
	* Total Complexity: O(u) (for asymptotic time analysis)
	*					θ(1) amortized (for amortized time analysis)
	*/
	// this means that the element is first added in the unique DA
	if (position == -1) {
		// resize the unique dynamic array if needed
		if (this->unique_length == this->unique_capacity) {
			this->unique_capacity *= 2;
			TElem* new_elems = new TElem[this->unique_capacity];
			for (int i = 0; i < this->unique_length; ++i)
				new_elems[i] = this->unique_elements[i];
			delete[] this->unique_elements;
			this->unique_elements = new_elems;
		}
		this->unique_elements[this->unique_length] = elem;
		this->positions_elements[this->positions_length] = this->unique_length;
		this->unique_length++;
		this->positions_length++;
	}
	else {  // this means that the element was found in the unique dynamic array
		this->positions_elements[this->positions_length] = position;
		this->positions_length++;
	}
}

/*
* Time Complexity Analysis:
* BC: θ(nr) - for all the below best cases
* WC: θ(n + nr) - for all the below worst cases
* Total Complexity: O(n + nr) in asymptotic time analysis, or
*					O(u + nr) amortized in amortized time analysis
*/
void Bag::addOccurrences(int nr, TElem elem) {
	if (nr < 0)
		throw std::exception();

	/*
	* BC: θ(1) - when the if condition is false
	* WC: θ(n + log(nr)) - when resize is needed (and nr is very big, so more resizes are needed)
	* Total Complexity θ(1) amortized or O(n + log(nr))
	*/
	// resize the positions dynamic array if needed
	if ((this->positions_length + nr) >= this->positions_capacity) {
		
		while ((this->positions_length + nr) >= this->positions_capacity)
			this->positions_capacity *= 2;
		
		int* new_elems = new int[this->positions_capacity];
		for (int i = 0; i < this->positions_length; ++i)
			new_elems[i] = this->positions_elements[i];
		delete[] this->positions_elements;
		this->positions_elements = new_elems;
	}

	/*
	* BC: the element is found on the first iteration => θ(1)
	* WC: the element is not found => θ(u)
	* AC: θ(u)
	* Total complexity: O(u)
	*/
	int position = -1;
	for (int i = 0; i < this->unique_length; ++i) {
		if (elem == this->unique_elements[i]) {
			position = i;
			break;
		}
	}

	/*
	* condition true: θ(nr) amortized (or in asymptotic time analysis O(u + nr))
	* condition false: θ(nr)
	*/
	// this means that the element is first added in the unique DA
	if (position == -1) {
		// θ(1) amortized or O(u), when resize is needed
		// resize the unique dynamic array if needed
		if (this->unique_length == this->unique_capacity) {
			this->unique_capacity *= 2;
			TElem* new_elems = new TElem[this->unique_capacity];
			for (int i = 0; i < this->unique_length; ++i)
				new_elems[i] = this->unique_elements[i];
			delete[] this->unique_elements;
			this->unique_elements = new_elems;
		}
		this->unique_elements[this->unique_length] = elem;  // add the element in the unique array

		// θ(nr)
		for (int i = 0; i < nr; ++i) {
			this->positions_elements[this->positions_length] = this->unique_length;
			this->positions_length++;
		}
		this->unique_length++;
	}
	else {  // this means that the element was found in the unique dynamic array
		// θ(nr)
		for (int i = 0; i < nr; ++i) {
			this->positions_elements[this->positions_length] = position;
			this->positions_length++;
		}
	}
}

/*
* Time Complexity Analysis:
* Let n be the number of elements in the bag and u be the number of unique elements in the bag (u <= n).
* BC: θ(1) - for all the below best cases
* WC: θ(n) - for all the below worst cases
* Total Complexity: O(n + u), which is basically O(n), because we know that u <= n.
*/
bool Bag::remove(TElem elem) {
	/*
	* BC: θ(1) - when the element is found at the first iteration
	* WC: θ(u) - when the element is not found
	* AC: θ(u)
	* Total Complexity: O(u)
	*/
	// find the element position in the unique dynamic array 
	int position = -1;
	for (int i = 0; i < this->unique_length; ++i)
		if (elem == this->unique_elements[i]) {
			position = i;
			break;
		}
	if (position == -1) return false;  // this means the element was not found
	
	/*
	* BC: θ(1) - the element is found twice on the first two positions
	* WC: θ(n) - the element is not found twice
	* AC: θ(n)
	* Total Complexity: O(n)
	*/
	// now check if the element appears at least twice in the bag - if not, remove the element from the unique dynamic array
	int count = 0, positions_index = 0;
	for (int i = 0; i < this->positions_length; ++i) {
		if (position == this->positions_elements[i]) {
			count++;
			if (count == 1) positions_index = i;
			else break;
		}
	}
	
	/*
	* If condition true => θ(n) - WC
	* If condition false => θ(1) - BC
	* => O(n)
	*/
	// if the element is unique in the bag
	if (count == 1) {
		// remove the element from the unique dynamic array
		// the order in the bag is not important, hence just move the last element to the removed position and descrease the length of the array
		this->unique_elements[position] = this->unique_elements[this->unique_length - 1];
		this->unique_length--;
		// now update the position of the moved element
		for (int i = 0; i < this->positions_length; ++i)
			if (this->positions_elements[i] == this->unique_length)
				this->positions_elements[i] = position;
		// and now just make the move also in the positions dynamic array
		this->positions_elements[positions_index] = this->positions_elements[this->positions_length - 1];
		this->positions_length--;
	}
	else {  // if the element is not unique in the bag
		this->positions_elements[positions_index] = this->positions_elements[this->positions_length - 1];
		this->positions_length--;
	}
	return true;  // the element was removed
}

/*
* Time Complexity Analysis:
* BC: θ(1) - the element is found after the first iteration
* WC: θ(u) - the element is not found
* AC: θ(u)
* Total Complexity: O(u)
*/
bool Bag::search(TElem elem) const {
	for (int i = 0; i < this->unique_length; ++i)
		if (elem == this->unique_elements[i])
			return true;
	return false;
}

/*
* Time Complexity Analysis:
* BC: θ(u) - when the element is not found
* WC: θ(n)
* AC: θ(n)
* Total Complexity: O(n) (also Ω(u))
*/
int Bag::nrOccurrences(TElem elem) const {
	/*
	* BC: θ(1) - the element is found at the first iteration
	* WC: θ(u) - the element is not found
	* AC: θ(u)
	* Total Complexity: O(u)
	*/
	// first find the element's position in the unique dynamic array
	int count = 0, position = -1;
	for (int i = 0; i < this->unique_length; ++i)
		if (elem == this->unique_elements[i]) {
			position = i;
			break;
		}
	if (position == -1) return 0;  // the element was not found => Total Complexity: θ(u)

	/*
	* Total Complexity: θ(n)
	*/
	// now find the number of occurences by parsing the positions dynamic array
	for (int i = 0; i < this->positions_length; ++i)
		if (this->positions_elements[i] == position)
			count++;
	return count;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
int Bag::size() const {
	return this->positions_length;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
bool Bag::isEmpty() const {
	return this->positions_length == 0;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
Bag::~Bag() {
	delete[] this->unique_elements;
	delete[] this->positions_elements;
}
