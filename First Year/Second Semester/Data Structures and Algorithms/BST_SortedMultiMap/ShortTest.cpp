#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());

    // custom tests
    SortedMultiMap map{ relation1 };
    map.add(1, 2);
    map.add(1, 3);
    map.add(2, 3);
    map.add(3, 6);
    map.add(2, 5);
    map.add(0, 7);
    
    assert(map.size() == 6);
    
    // Lab operation tests
    std::vector<TValue> ret = map.removeKey(1);
    assert(ret.size() == 2);
    assert(ret[0] == 2);
    assert(ret[1] == 3);
    assert(map.size() == 4);
    
    ret = map.removeKey(5);
    assert(ret.size() == 0);
    
    ret = map.removeKey(2);
    assert(ret.size() == 2);
    assert(map.size() == 2);

    ret = map.removeKey(3);
    assert(ret[0] == 6);
    assert(map.size() == 1);
}

