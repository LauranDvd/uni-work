#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	first();
}

void SMMIterator::first(){
	currentMain = map.head;
	if (currentMain != nullptr)
		currentSecondary = currentMain->valuesHead;
}

void SMMIterator::nextNode(){
	if (!valid())
		throw exception();

	currentSecondary = currentSecondary->nextNode;
	if (currentSecondary == nullptr) {
		currentMain = currentMain->nextNode;
		if (currentMain != nullptr)
			currentSecondary = currentMain->valuesHead;
	}
}

bool SMMIterator::valid() const{
	return currentMain != nullptr && currentSecondary != nullptr;
}

TElem SMMIterator::getCurrent() const{
	if (!valid())
		throw exception();

	return { currentMain->info, currentSecondary->info };
}


