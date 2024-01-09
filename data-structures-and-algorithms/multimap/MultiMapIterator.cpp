#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>

// identical to "first"
MultiMapIterator::MultiMapIterator(const MultiMap& theMap): multiMap(theMap) {
	first();
}

// theta(1)
TElem MultiMapIterator::getCurrent() const{
	if (!valid())
		throw exception();

	return make_pair(multiMap.keyValues[bigIndex].first, multiMap.keyValues[bigIndex].second.elements[smallIndex]);
}

// theta(1)
bool MultiMapIterator::valid() const {
	return bigIndex != -1 && smallIndex != -1;
}

// worst: theta(MAX_ABS_TKEY) -- if "current" points to the key with the smallest keyCode's last value, and no other key has values
// best: theta(1) -- "current" doesn't point to the last value of a key ("last" node in the internal SLLA)
// average: theta(MAX_ABS_TKEY / numberOfPairs) -- if the values are distributed evenly among keys,
// then it'll have to advance MAX_ABS_TKEY/numberOfPairs keyCodes (if noPairs>MAX_ABS_TKEY, it will be theta(1))
//
// overall: O(MAX_ABS_TKEY)
void MultiMapIterator::next() {
	if (!valid())
		throw exception();

	smallIndex = multiMap.keyValues[bigIndex].second.next[smallIndex];
	if (smallIndex == -1) {  // end of this key
		bigIndex = multiMap.nextBig[bigIndex];
		if (bigIndex != -1)
			smallIndex = multiMap.keyValues[bigIndex].second.head;
	}
}


void MultiMapIterator::first() {
	bigIndex = multiMap.headBig;
	smallIndex = multiMap.keyValues[bigIndex].second.head;
}
