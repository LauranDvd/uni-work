#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

// overall: theta(n) -- "first" is less complex than creating the array
SMIterator::SMIterator(const SortedMap& m) : map(m){
	stack = new BSTNode*[map.size()];
	first();
}

// theta(n)
SMIterator::~SMIterator() {
	delete[] stack;
}

// best: theta(1) -- the root has no left child
// worst: theta(n) -- the tree is just a chain (to the left)
// average: theta(logn)
// overall: o(maxDepth)
void SMIterator::first(){
	index = -1;

	BSTNode* current = map.root;
	while (current != nullptr) {
		stack[++index] = current;
		current = current->leftChild;
	}
}

// best: theta(1) -- the top of the stack has no right child
// worst: theta(n) -- the top of the stack's right child's subtree contains nearly all nodes, and it's a chain (to the left)
// average: theta(logn)
// overall: o(maxDepth)
void SMIterator::next(){
	if (!valid())
		throw exception();
	
	// take top of the stack's right child and go left-left-left...
	BSTNode* current = stack[index--];
	current = current->rightChild;
	while (current != nullptr) {
		stack[++index] = current;
		current = current->leftChild;
	}
}

// theta(1)
bool SMIterator::valid() const{
	return index != -1;
}

// theta(1)
TElem SMIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return stack[index]->data;
}
