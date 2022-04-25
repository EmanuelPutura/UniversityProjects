#pragma once
//DO NOT INCLUDE BAGITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
class BagIterator; 

#define INITIAL_M 5
#define DELETED -111112

class Bag {

private:
	int m, length;
	TElem* elems;

	// hash functions
	int hashFunction(TElem element, int probe_no) const;
	int firstHash(TElem element) const;
	int secondHash(TElem element) const;

	inline double getLoadFactor() const;

	bool isPrime(int number) const;
	int findNextPrime(int number) const;
	
	void resizeAndRehash();

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//removes all occurrences of elem from the Bag 
	//returns the number of elements removed 
	int removeAllOccurrences(TElem elem);

	//destructor
	~Bag();
};