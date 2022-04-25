#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <iostream>


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	
	// 5 10 7 1 11 -3
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		// std::cout << e << ' ';
		it.next();
	}
	// std::cout << '\n';

	// Extra operation tests

	b.add(1);
	b.add(1);
	assert(b.size() == 8);
	assert(b.removeAllOccurrences(1) == 3);
	assert(b.size() == 5);

	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		assert(e != 1);
		it.next();
	}

	assert(!b.removeAllOccurrences(-5));
}
