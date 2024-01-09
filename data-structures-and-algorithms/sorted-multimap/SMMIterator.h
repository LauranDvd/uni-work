#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	MainNode* currentMain;
	SecondaryNode* currentSecondary;

public:
	void first();
	void nextNode();
	bool valid() const;
   	TElem getCurrent() const;
};

