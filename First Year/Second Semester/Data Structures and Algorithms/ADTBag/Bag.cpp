#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

#define INIT_CAPACITY 100

Bag::Bag() {
	this->uniqueElems = new TElem[INIT_CAPACITY];
	this->positions = new TElem[INIT_CAPACITY];
	this->capacity = INIT_CAPACITY;
}


void Bag::add(TElem elem) {
	//TODO - Implementation
}


bool Bag::remove(TElem elem) {
	//TODO - Implementation
	return false; 
}


bool Bag::search(TElem elem) const {
	//TODO - Implementation
	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	return 0; 
}


int Bag::size() const {
	//TODO - Implementation
	return 0;
}


bool Bag::isEmpty() const {
	//TODO - Implementation
	return 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
}

