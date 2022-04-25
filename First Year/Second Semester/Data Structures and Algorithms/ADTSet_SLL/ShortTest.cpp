#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"

#include <iostream>

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

	// test new functionality
	// s.filter(isOdd);
	s.filter([](int e) -> bool {return e % 2; });
	assert(s.size() == 3);
	assert(!s.search(10));
	
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		assert(e % 2);
		it.next();
	}

	s.filter([](int e) -> bool {return e == -3 || e == 7; });
	assert(s.size() == 2);
	assert(s.search(-3));
	assert(s.search(7));

	s.filter([](int e) -> bool {return e % 2 == 0; });
	assert(!s.size());
}

