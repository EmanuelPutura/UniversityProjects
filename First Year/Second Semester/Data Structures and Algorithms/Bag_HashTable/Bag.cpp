#include "Bag.h"
#include "BagIterator.h"
#include <exception>
using namespace std;

#define MAX_LOADFACTOR 0.6

/*
* Time Complexity: θ(1)
*/
int Bag::hashFunction(TElem element, int probe_no) const {
	return (firstHash(element) + secondHash(element) * probe_no) % m;
}

/*
* Time Complexity: θ(1)
*/
int Bag::firstHash(TElem element) const {
	int ret = element % m;
	if (ret < 0) ret = -ret;
	return ret;
}

/*
* Time Complexity: θ(1)
*/
int Bag::secondHash(TElem element) const {
	int ret = element % (m - 1);
	if (ret < 0) ret = -ret;
	ret++;
	return ret;
}

/*
* Time Complexity: θ(1)
*/
inline double Bag::getLoadFactor() const {
	return (double)length / m;
}

/*
* Time Complexity: θ(sqrt(number))
*/
bool Bag::isPrime(int number) const
{
	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int d = 3; d * d <= number; d += 2)
		if (number % d == 0) return false;
	return true;
}

// Assumes that the parameter is prime
int Bag::findNextPrime(int number) const
{
	while (!isPrime(number))
		number++;
	return number;
}

/*
* Time Complexity: θ(m) on average, θ(n^2) in the worst case scenario
*/
void Bag::resizeAndRehash() {
	int past_m = m;
	m = findNextPrime(2 * m);
	length = 0;

	TElem* past_elems = elems;
	elems = new TElem[m];

	for (size_t i = 0; i < m; ++i)
		elems[i] = NULL_TELEM;
	
	for (size_t i = 0; i < past_m; ++i)
		if (past_elems[i] != NULL_TELEM && past_elems[i] != DELETED) {
			int probe_no = 0;
			int position = hashFunction(past_elems[i], probe_no);
			while (probe_no < m && elems[position] != NULL_TELEM && elems[position] != DELETED) {
				probe_no++;
				position = hashFunction(past_elems[i], probe_no);
			}

			elems[position] = past_elems[i];
			length++;
		}
	delete past_elems;
}

/*
* --> For the hashtable:
* Choose m as a prime number and design secondHash() in such a way that it always returns a value from the {1, ..., m - 1} set
* Let n be the number of occupied positions in the hashtable
* 
* Time Complexity: θ(1)
*/
Bag::Bag() {
	m = INITIAL_M;
	length = 0;
	
	elems = new TElem[m];
	for (size_t i = 0; i < m; ++i)
		elems[i] = NULL_TELEM;
}

/*
* Time Complexity: θ(1) amortized on average, θ(n) in the worst case scenario
*/
void Bag::add(TElem elem) {
	if (getLoadFactor() >= MAX_LOADFACTOR)
		resizeAndRehash();

	int probe_no = 0;
	int position = hashFunction(elem, probe_no);
	while (probe_no < m && elems[position] != NULL_TELEM && elems[position] != DELETED) {
		probe_no++;
		position = hashFunction(elem, probe_no);
	}

	elems[position] = elem;
	length++;
}

/*
* Time Complexity: θ(1) on average, θ(n) in the worst case scenario
*/
bool Bag::remove(TElem elem) {
	int probe_no = 0;
	int position = hashFunction(elem, probe_no);
	while (probe_no < m && elems[position] != elem && elems[position] != NULL_TELEM) {
		probe_no++;
		position = hashFunction(elem, probe_no);
	}

	if (elems[position] == elem) {
		elems[position] = DELETED;
		length--;
		return true;
	}
	
	return false;
}

/*
* Time Complexity: θ(1) on average, θ(n) in the worst case scenario
* => BC: θ(1), WC: θ(n)
* => Total complexity: O(n)
*/
int Bag::removeAllOccurrences(TElem elem) {
	int probe_no = 0, cnt = 0;
	int position = hashFunction(elem, probe_no);
	while (probe_no < m && elems[position] != NULL_TELEM) {
		if (elems[position] == elem) {
			elems[position] = DELETED;
			length--;
			cnt++;
		}
		probe_no++;
		position = hashFunction(elem, probe_no);
	}

	return cnt;
}

/*
* Time Complexity: θ(1) amortized on average, θ(n) in the worst case scenario
*/
bool Bag::search(TElem elem) const {
	int probe_no = 0;
	int position = hashFunction(elem, probe_no);
	while (probe_no < m && elems[position] != elem && elems[position] != NULL_TELEM) {
		probe_no++;
		position = hashFunction(elem, probe_no);
	}

	return elems[position] == elem;
}

/*
* Time Complexity: θ(1) amortized on average, θ(n) in the worst case scenario
*/
int Bag::nrOccurrences(TElem elem) const {
	int probe_no = 0, cnt = 0;
	int position = hashFunction(elem, probe_no);
	while (probe_no < m && elems[position] != NULL_TELEM) {
		if (elems[position] == elem) cnt++;
		probe_no++;
		position = hashFunction(elem, probe_no);
	}
	return cnt;
}

/*
* Time Complexity: θ(1)
*/
int Bag::size() const {
	return length;
}

/*
* Time Complexity: θ(1)
*/
bool Bag::isEmpty() const {
	return length == 0;
}

/*
* Time Complexity: θ(1)
*/
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

/*
* Time Complexity: θ(1)
*/
Bag::~Bag() {
	delete elems;
}

