#include <assert.h>
#include <iostream>
#include "../Headers/SortedMultiMap.h"
#include "../Headers/SMMIterator.h"
#include <exception>
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
    	it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}


void testGetKeyRange()
{
    SortedMultiMap smm = SortedMultiMap(relation1);

    assert(smm.getKeyRange() == -1);

    smm.add(1,2);
    smm.add(1,3);

    assert(smm.getKeyRange() == 0);

    smm.add(0, 0);
    smm.add(2, 2);

    assert(smm.getKeyRange() == 2);

    smm.add(-10, 10);
    smm.add(20, 20);

    assert(smm.getKeyRange() == 30);
}

