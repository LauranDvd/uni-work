#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
	capacityBig = 1;
	firstFreeBig = 0;
	headBig = -1;
	currentsize = 0;

	keyValues = new pair<TKey, SLLA>[1];
	keyValues[0].first = -1;

	nextBig = new int[1];
	nextBig[0] = -1;
}


void MultiMap::freePositionSmall(SLLA& arr, int position) {
	arr.next[position] = arr.firstFree;
	arr.firstFree = position;
}

void MultiMap::freePositionBig(int position) {
	nextBig[position] = firstFreeBig;
	firstFreeBig = position;
}

void MultiMap::resizeSmall(SLLA& arr) {
	int newCapacity = arr.capacity * 2;
	
	TValue* newElems = new TValue[newCapacity];
	for (int i = 0; i < arr.capacity; i++)
		newElems[i] = arr.elements[i];
	TValue* newNext = new int[newCapacity];
	for (int i = 0; i < arr.capacity; i++)
		newNext[i] = arr.next[i];

	arr.firstFree = arr.capacity;
	for (int i = arr.firstFree; i < newCapacity - 1; i++)
		newNext[i] = i + 1;
	newNext[newCapacity - 1] = -1;

	delete arr.elements;
	arr.elements = newElems;
	delete arr.next;
	arr.next = newNext;
	arr.capacity = newCapacity;
}

int MultiMap::allocatePositionSmall(SLLA& arr) {
	if (arr.firstFree == -1) {
		// no more space, reallocate
		resizeSmall(arr);
	}

	int allocated = arr.firstFree;
	arr.firstFree = arr.next[arr.firstFree];
	return allocated;
}

void MultiMap::addToSmall(SLLA& arr, TValue val) {
	int allocatedPos = allocatePositionSmall(arr);
	arr.elements[allocatedPos] = val;
	arr.next[allocatedPos] = arr.head;
	arr.head = allocatedPos;
}

void MultiMap::initSmall(int index) {
	// init keyValues[index].second
	keyValues[index].second.capacity = 1;
	keyValues[index].second.head = -1;
	keyValues[index].second.firstFree = 0;

	keyValues[index].second.elements = new TValue[1];
	keyValues[index].second.next = new int[1];
	keyValues[index].second.next[0] = -1;
}

void MultiMap::resizeBig() {
	int newCap = capacityBig * 2;

	pair<TKey, SLLA>* newElems = new pair<TKey, SLLA>[newCap];
	for (int i = 0; i < capacityBig; i++)
		newElems[i] = keyValues[i];
	int* newNext = new int[newCap];
	for (int i = 0; i < capacityBig; i++)
		newNext[i] = nextBig[i];

	firstFreeBig = capacityBig;
	for (int i = firstFreeBig; i < newCap - 1; i++)
		newNext[i] = i + 1;
	newNext[newCap - 1] = -1;

	delete keyValues;
	keyValues = newElems;
	delete nextBig;
	nextBig = newNext;
	capacityBig = newCap;
}

int MultiMap::allocatePositionBig() {
	if (firstFreeBig == -1) {
		// no more space, reallocate
		resizeBig();
	}

	int allocated = firstFreeBig;
	firstFreeBig = nextBig[firstFreeBig];
	return allocated;
}

void MultiMap::addKey(int key) {
	int allocatedPos = allocatePositionBig();
	keyValues[allocatedPos].first = key;
	initSmall(allocatedPos);
	nextBig[allocatedPos] = headBig;
	headBig = allocatedPos;
}

void MultiMap::add(TKey key, TValue value) {
	if (search(key).size() == 0) {
		addKey(key);
	}

	int positionKey = headBig;
	while (keyValues[positionKey].first != key)
		positionKey = nextBig[positionKey];
	
	addToSmall(keyValues[positionKey].second, value);
	currentsize++;
	return;
}

bool MultiMap::remove(TKey key, TValue value) {
	int positionKey = headBig, prevPositionKey = -1;
	while (positionKey != -1 && keyValues[positionKey].first != key) {
		prevPositionKey = positionKey;
		positionKey = nextBig[positionKey];
	}
	if (positionKey == -1)
		return false;

	SLLA& arr = keyValues[positionKey].second;

	int position = arr.head, prevPosition = -1;
	while (position != -1 && arr.elements[position] != value) {
		prevPosition = position;
		position = arr.next[position];
	}

	if (position == -1)
		return false;
	
	if (prevPosition != -1)
		arr.next[prevPosition] = arr.next[position];
	else  // head
		arr.head = arr.next[arr.head];
	freePositionSmall(arr, position); 
	if (arr.head == -1) {
		delete arr.elements;
		delete arr.next;
		if (prevPositionKey != -1)
			nextBig[prevPositionKey] = nextBig[positionKey];
		else  // head
			headBig = nextBig[headBig];
		freePositionBig(positionKey);
	}

	currentsize--;

	return true;
}

vector<TValue> MultiMap::search(TKey key) const {
	int positionKey = headBig;
	while (positionKey != -1 && keyValues[positionKey].first != key) {
		positionKey = nextBig[positionKey];
	}
	if (positionKey == -1)
		return vector<TValue>(0);

	SLLA& arr = keyValues[positionKey].second;
	vector<TValue> theValues;

	int position = arr.head;
	while (position != -1) {
		theValues.push_back(arr.elements[position]);
		position = arr.next[position];
	}
	
	return theValues;
}

int MultiMap::size() const {
	return currentsize;
}

bool MultiMap::isEmpty() const {
	return currentsize == 0;
}


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

MultiMap::~MultiMap() { 
	int position = headBig;
	while (position != -1) {
		delete keyValues[position].second.elements;
		delete keyValues[position].second.next;
		position = nextBig[position];
	}
	delete keyValues;
	delete nextBig;
}

