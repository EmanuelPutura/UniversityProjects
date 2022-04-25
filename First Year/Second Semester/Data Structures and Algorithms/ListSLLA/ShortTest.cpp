#include "ShortTest.h"

#include <assert.h>
#include <exception>


#include "IteratedList.h"
#include "ListIterator.h"

#include <iostream>

using namespace std;

void testAll() {
	IteratedList list = IteratedList();
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	assert(list.size() == 1);
	assert(!list.isEmpty());

	ListIterator it = list.search(1);
	assert(it.valid());
	assert(it.getCurrent() == 1);
	it.next();
	assert(!it.valid());
	it.first();
	assert(it.valid());
	assert(it.getCurrent() == 1);

	assert(list.remove(it) == 1);
	assert(list.size() == 0);
	assert(list.isEmpty());

	list.addToEnd(1);
	list.addToEnd(3);
	list.addToEnd(7);
	ListIterator it3 = list.first();
	list.addToPosition(it3, 77);
	list.addToPosition(it3, 44);
	assert(list.size() == 5);

	ListIterator it2 = list.first();
	assert(it2.getCurrent() == 1);
	it2.next();
	assert(it2.getCurrent() == 77);
	it2.next();
	assert(it2.getCurrent() == 44);
	it2.next();
	assert(it2.getCurrent() == 3);
	it2.next();
	assert(it2.getCurrent() == 7);
	it2.next();
	assert(it2.valid() == false);

	IteratedList list2 = IteratedList();
	list2.addToBeginning(4);
	list2.addToEnd(5);
	list2.addToBeginning(3);
	list2.addToEnd(6);
	list2.addToBeginning(2);
	list2.addToEnd(7);
	int i = 2;
	ListIterator it4 = list2.first();

	// 2 3 4 5 6 7
	while (it4.valid()) {
		assert(it4.getCurrent() == i);
		i++;
		it4.next();
	}

	ListIterator it5 = list2.first();
	ListIterator it6 = list2.first();
	it6.next();
	it6.next();
	it6.next();

	list2.removeBetween(it5, it6);
	assert(list2.size() == 4);

	ListIterator it7 = list2.first();
	while (it7.valid()) {
		assert(it7.getCurrent() != 4 && it7.getCurrent() != 3);
		i++;
		it7.next();
	}
	
	it5.first();
	it6.first();
	it6.next();
	list2.removeBetween(it5, it6);
	assert(list2.size() == 4);

}


