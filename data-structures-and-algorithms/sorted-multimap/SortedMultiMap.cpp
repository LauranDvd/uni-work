#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation relation) {
	this->relationToSortBasedOn = relation;

	head = nullptr;
}

void SortedMultiMap::add(TKey key, TValue value) {
	if (head == nullptr || !relationToSortBasedOn(head->info, key)) {
		// new head
		MainNode* node = new MainNode;
		node->nextNode = head;
		node->info = key;
		node->valuesHead = new SecondaryNode;
		node->valuesHead->nextNode = nullptr;
		node->valuesHead->info = value;
		head = node;

		return;
	}

	MainNode* insertAfter = head;
	while (insertAfter->nextNode != nullptr && relationToSortBasedOn(insertAfter->nextNode->info, key))
		insertAfter = insertAfter->nextNode;

	if (insertAfter->info == key) {
		// key exists. add to its linked list the value
		SecondaryNode* newSecondaryNode = new SecondaryNode;
		newSecondaryNode->info = value;
		newSecondaryNode->nextNode = insertAfter->valuesHead;
		insertAfter->valuesHead = newSecondaryNode;
	}
	else {
		// create key
		MainNode* node = new MainNode;
		node->nextNode = insertAfter->nextNode;
		node->info = key;
		node->valuesHead = new SecondaryNode;
		node->valuesHead->nextNode = nullptr;
		node->valuesHead->info = value;
		insertAfter->nextNode = node;
	}
}

vector<TValue> SortedMultiMap::search(TKey key) const {
	vector<TValue> valuesOfGivenKey;

	MainNode* main = head;
	while (main != nullptr && main->info != key)
		main = main->nextNode;

	if (main == nullptr)
		return valuesOfGivenKey;
	SecondaryNode* secondary = main->valuesHead;
	while (secondary != nullptr) {
		valuesOfGivenKey.push_back(secondary->info);
		secondary = secondary->nextNode;
	}

	return valuesOfGivenKey;
}

bool SortedMultiMap::remove(TKey key, TValue value) {
	MainNode* main = head;
	MainNode* prevMain = nullptr;
	while (main != nullptr && main->info != key) {
		prevMain = main;
		main = main->nextNode;
	}

	if (main == nullptr)
		return false;

	SecondaryNode* secondary = main->valuesHead;
	SecondaryNode* prevSecondary = nullptr;
	while (secondary != nullptr && secondary->info != value) {
		prevSecondary = secondary;
		secondary = secondary->nextNode;
	}

	if (secondary == nullptr)
		return false;

	// remove from the list of values
	if (secondary == main->valuesHead)
		main->valuesHead = secondary->nextNode;
	else
		prevSecondary->nextNode = secondary->nextNode;
	delete secondary;

	if (main->valuesHead == nullptr) {
		// remove from the list of keys
		if (main == head)
			head = main->nextNode;
		else
			prevMain->nextNode = main->nextNode;
		delete main;
	}

	return true;
}


int SortedMultiMap::size() const {
	if (head == nullptr)
		return 0;

	int theSize = 0;

	MainNode* main = head;
	SecondaryNode* secondary = head->valuesHead;
	while (main != nullptr) {
		theSize++;

		secondary = secondary->nextNode;
		if (secondary == nullptr) {
			main = main->nextNode;
			if (main != nullptr)
				secondary = main->valuesHead;
		}
	}

	return theSize;
}

bool SortedMultiMap::isEmpty() const {
	return head == nullptr;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	if (head == nullptr)
		return;

	MainNode* main = head;
	SecondaryNode* secondary = head->valuesHead;
	while (main != nullptr) {
		auto secondaryCopy = secondary;
		secondary = secondary->nextNode;
		delete secondaryCopy;
		if (secondary == nullptr) {
			auto mainCopy = main;
			main = main->nextNode;
			delete mainCopy;
			if (main != nullptr)
				secondary = main->valuesHead;
		}
	}
}
