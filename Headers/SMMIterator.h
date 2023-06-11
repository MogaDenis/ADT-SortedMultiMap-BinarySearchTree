#pragma once

#include "../Headers/SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	int currentNodeIndex;

	int* indicesInOrder;
	int addedIndices;

	void inOrderTraversal();

public:
	~SMMIterator();
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

