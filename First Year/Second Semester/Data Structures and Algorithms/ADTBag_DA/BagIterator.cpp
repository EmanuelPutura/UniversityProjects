#include <exception>
#include "BagIterator.h"
#include "Bag.h"

#include <exception>

using namespace std;

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = 0;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
void BagIterator::first() {
	this->current = 0;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
void BagIterator::next() {
	if (this->current >= this->bag.positions_length)
		throw std::exception();
	else
		this->current++;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
bool BagIterator::valid() const {
	return this->current < this->bag.positions_length;
}

/*
* Time Complexity Analysis:
* Total Complexity: θ(1)
*/
TElem BagIterator::getCurrent() const
{
	if (this->current >= this->bag.positions_length)
		throw std::exception();
	int unique_position = this->bag.positions_elements[this->current];
	return this->bag.unique_elements[unique_position];
}
