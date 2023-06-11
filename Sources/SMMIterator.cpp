#include "../Headers/SMMIterator.h"
#include "../Headers/SortedMultiMap.h"
#include <iostream>


// Traverse all nodes => Theta(n)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d)
{
	this->indicesInOrder = new int[map.numberOfElements];
	this->currentNodeIndex = 0;
	this->addedIndices = 0;

	this->inOrderTraversal();
}


// Theta(n)
void SMMIterator::inOrderTraversal()
{
	int* stack = new int[map.numberOfElements];
	int stackedNodes = 0;
	int nodeIndex = map.root;

	while (nodeIndex != -1 || stackedNodes != 0)
	{
		while (nodeIndex != -1)
		{
			stack[stackedNodes++] = nodeIndex;
			nodeIndex = map.elements[nodeIndex].left;
		}

		nodeIndex = stack[--stackedNodes];

		this->indicesInOrder[this->addedIndices++] = nodeIndex;

		nodeIndex = map.elements[nodeIndex].right;
	}

	delete[] stack;
}


// Theta(1)
void SMMIterator::first()
{
	this->currentNodeIndex = 0;
}


// Theta(1)
void SMMIterator::next()
{
	if (!this->valid())
		throw std::exception();

	this->currentNodeIndex++;
}


// Theta(1)
bool SMMIterator::valid() const
{
	return this->currentNodeIndex < this->addedIndices;
}


// Theta(1)
TElem SMMIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();

	return map.elements[this->indicesInOrder[this->currentNodeIndex]].getData();
}


SMMIterator::~SMMIterator()
{
	delete[] this->indicesInOrder;
}


