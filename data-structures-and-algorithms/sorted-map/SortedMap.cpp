#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

// theta(1)
SortedMap::SortedMap(Relation r) {
	root = nullptr;
	relationToSortBasedOn = r;
}

// best: theta(1) -- empty tree
// worst: theta(n) -- the tree is a chain (to the left) and k is smallest than all keys
// average: theta(logn) -- on average, maxDepth=logn
// overall: o(maxDepth)
TValue SortedMap::add(TKey key, TValue value) {
	if (root == nullptr) {
		root = new BSTNode;
		root->data = make_pair(key, value);
		root->leftChild = root->rightChild = root->parent = nullptr;
		return NULL_TVALUE;
	}

	BSTNode* father = root;
	while (true) {
		if (father->data.first == key)
			break;

		if (relationToSortBasedOn(key, father->data.first)) {
			if (father->leftChild == nullptr)
				break;
			father = father->leftChild;
		}
		else {
			if (father->rightChild == nullptr)
				break;
			father = father->rightChild;
		}
	}

	if (father->data.first == key) {
		// key exists
		TValue oldValue = father->data.second;
		father->data.second = value;
		return oldValue;
	}

	// new key
	BSTNode* added = new BSTNode;
	added->leftChild = added->rightChild = nullptr;
	added->parent = father;
	added->data = make_pair(key, value);
	if (relationToSortBasedOn(key, father->data.first))
		father->leftChild = added;
	else
		father->rightChild = added;

	splay(added);

	return NULL_TVALUE;
}

// best: theta(1) -- empty tree
// worst: theta(n) -- the tree is a chain (to the left) and k is the smallest key
// average: theta(logn) -- on average, maxDepth=logn
// overall: o(maxDepth)
TValue SortedMap::search(TKey key) const {
	BSTNode* node = root;
	while (node != nullptr && node->data.first != key) {
		if (relationToSortBasedOn(key, node->data.first))
			node = node->leftChild;
		else
			node = node->rightChild;
	}
	if (node == nullptr)
		return NULL_TVALUE;
	return node->data.second;
}

// best: theta(1) -- empty tree
// worst: theta(n) -- the tree is a chain (to the left) and k is the smallest key
// average: theta(logn)
// overall: o(maxDepth)
TValue SortedMap::remove(TKey key) {
	BSTNode* node = root;
	while (node != nullptr && node->data.first != key) {
		if (relationToSortBasedOn(key, node->data.first))
			node = node->leftChild;
		else
			node = node->rightChild;
	}
	if (node == nullptr)
		return NULL_TVALUE;

	TValue oldValue = node->data.second;

	if (node == root && node->leftChild == nullptr && node->rightChild == nullptr) {
		delete node;
		root = nullptr;
		return oldValue;
	}

	if (node->leftChild == nullptr && node->rightChild == nullptr) {
		// leaf
		if (node->parent->leftChild == node)
			node->parent->leftChild = nullptr;
		else
			node->parent->rightChild = nullptr;
	}
	else if (node->leftChild == nullptr || node->rightChild == nullptr) {
		// node has just one child. the parent will skip node and point to that child
		BSTNode* sonOfNode = node->leftChild;
		if (sonOfNode == nullptr)
			sonOfNode = node->rightChild;

		if (node == root)
			root = sonOfNode;
		else {
			if (node->parent->leftChild == node)
				node->parent->leftChild = sonOfNode;
			else
				node->parent->rightChild = sonOfNode;
			sonOfNode->parent = node->parent;
		}
	}
	else {
		// take the smallest in the right subtree of "node" (will be a leaf) and bring its value to "node"
		// then delete that leaf
		BSTNode* smallestOnRight = node->rightChild;
		BSTNode* parentOfSmallest = node;
		while (smallestOnRight->leftChild != nullptr) {
			parentOfSmallest = smallestOnRight;
			smallestOnRight = smallestOnRight->leftChild;
		}
		swap(node->data, smallestOnRight->data);
		parentOfSmallest->leftChild = nullptr;
	}
	delete node;
	return oldValue;
}

// theta(n)
int SortedMap::size() const {
	return getSizeOfSubtree(root);
}

// theta(1)
bool SortedMap::isEmpty() const {
	return root == nullptr;
}

// theta(n*logn)
TValue SortedMap::mostFrequent() const {
	if (isEmpty())
		return NULL_TVALUE;
	TValue* allValues = new TValue[size()];
	int countValues = 0;
	dfsAndUpdateListOfValues(root, allValues, &countValues);

	mergesort(allValues, 0, countValues - 1);

	TValue toReturn = allValues[0];
	int cntBest = 1, cntCurr = 0;
	for (int i = 1; i < countValues; i++)
		if (allValues[i] == allValues[i - 1]) {
			cntCurr++;
			if (cntCurr > cntBest) {
				cntBest = cntCurr;
				toReturn = allValues[i];
			}
		}
		else
			cntCurr = 1;

	delete[] allValues;

	return toReturn;
}

// complexity: see the constructor of SMIterator
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// theta(n)
SortedMap::~SortedMap() {
	dfsAndDestroy(root);
}

void printRecursively(BSTNode* node) {
	if (node == nullptr)
		return;

	cout << "Node has value " << node->data.first << " and its children have ";
	if (node->leftChild != nullptr)
		cout << node->leftChild->data.first << " ";
	if (node->rightChild != nullptr)
		cout << node->rightChild->data.first << " ";
	cout << "\n";

	printRecursively(node->leftChild); printRecursively(node->rightChild);
}

void SortedMap::print() {
	printRecursively(root);
}

void SortedMap::splay(BSTNode* node) {
	// bring node to the root!

	while (this->root != node) {
		if (node->parent == root) {
			if (node->parent->leftChild == node)
				rotateRight(node->parent);
			else if (node->parent->rightChild == node)
				rotateLeft(node->parent);
		}

		// left-left (father is left of grandfather, node is left of father)
		else if (node->parent->leftChild == node && node->parent->parent->leftChild == node->parent) {
			rotateRight(node->parent->parent);
			rotateRight(node->parent);
		}
		else if (node->parent->rightChild == node && node->parent->parent->rightChild == node->parent) {  // right-right
			rotateLeft(node->parent->parent);
			rotateLeft(node->parent);
		}
		else if (node->parent->rightChild == node && node->parent->parent->leftChild == node->parent) {  // left-right
			rotateLeft(node->parent);
			rotateRight(node->parent);
		}
		else if (node->parent->leftChild == node && node->parent->parent->rightChild == node->parent) {  // right-left
			rotateRight(node->parent);
			rotateLeft(node->parent);
		}
		else {
			cout << (node->parent->leftChild == node) << "\n";
			cout << node->parent->parent->data.first << " " << node->parent->data.first << " " << node->data.first << "\n";
		}
	}
}

void SortedMap::rotateLeft(BSTNode* node) {
	BSTNode* x = node, * y = x->rightChild, * z = y->leftChild, * p = x->parent;
	x->rightChild = z;
	x->parent = y;
	y->leftChild = x;
	y->parent = p;
	if (z != nullptr)
		z->parent = x;
	
	if (x == root)
		root = y;
	else if (p->leftChild == x)
		p->leftChild = y;
	else
		p->rightChild = y;
}

void SortedMap::rotateRight(BSTNode* node) {
	BSTNode* x = node, * y = x->leftChild, * z = y->rightChild, * p = x->parent;
	x->leftChild = z;
	x->parent = y;
	y->rightChild = x;
	y->parent = p;
	if (z != nullptr)
		z->parent = x;

	if (x == root)
		root = y;
	else if (p->leftChild == x)
		p->leftChild = y;
	else
		p->rightChild = y;
}

// theta(size of subtree)
int SortedMap::getSizeOfSubtree(BSTNode* subroot) const {
	if (subroot == nullptr)
		return 0;
	return 1 + getSizeOfSubtree(subroot->leftChild) + getSizeOfSubtree(subroot->rightChild);
}

// theta(size of subtree)
void SortedMap::dfsAndDestroy(BSTNode* node) {
	if (node == nullptr)
		return;
	dfsAndDestroy(node->leftChild);
	dfsAndDestroy(node->rightChild);
	delete node;
}

// theta(size of subtree)
void SortedMap::dfsAndUpdateListOfValues(BSTNode* node, TValue* allValues, int* countValues) const {
	if (node == nullptr)
		return;
	allValues[*countValues] = node->data.second;
	(*countValues)++;
	dfsAndUpdateListOfValues(node->leftChild, allValues, countValues);
	dfsAndUpdateListOfValues(node->rightChild, allValues, countValues);
}

// theta(n*logn)
void SortedMap::mergesort(TValue* theArray, int leftIndex, int rightIndex) const {
	if (leftIndex >= rightIndex)
		return;

	int middleIndex = (leftIndex + rightIndex) / 2;
	mergesort(theArray, leftIndex, middleIndex);
	mergesort(theArray, middleIndex + 1, rightIndex);

	TValue* sortedSubarray = new TValue[rightIndex - leftIndex + 1];
	int idxLeft = leftIndex, idxRight = middleIndex + 1, idxNewOrder = 0;
	while (idxLeft <= middleIndex && idxRight <= rightIndex) {
		if (theArray[idxLeft] <= theArray[idxRight])
			sortedSubarray[idxNewOrder++] = theArray[idxLeft++];
		else
			sortedSubarray[idxNewOrder++] = theArray[idxRight++];
	}
	while (idxLeft <= middleIndex)
		sortedSubarray[idxNewOrder++] = theArray[idxLeft++];
	while (idxRight <= rightIndex)
		sortedSubarray[idxNewOrder++] = theArray[idxRight++];
	for (int i = leftIndex; i <= rightIndex; i++)
		theArray[i] = sortedSubarray[i - leftIndex];
	delete[] sortedSubarray;
}
