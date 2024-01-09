#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
typedef bool(*Condition)(TKey);   // for the extra op 
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

struct SLLA {
	TValue* elements;
	int* next;
	int capacity;
	int head, firstFree;
};

class MultiMap
{
	friend class MultiMapIterator;

private:
	pair<TKey, SLLA>* keyValues;
	int* nextBig;

	int capacityBig;
	int headBig;
	int firstFreeBig;

	int currentsize; 

	int allocatePositionBig();
	void addKey(int key);
	void initSmall(int index);
	void resizeBig();
	void freePositionBig(int pos);

	void addToSmall(SLLA& arr, TValue val);
	int allocatePositionSmall(SLLA& arr);
	void resizeSmall(SLLA& arr);
	void freePositionSmall(SLLA& arr, int pos);
public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;


	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();


};

