#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class Node
{
public:
    TElem data;
    int left, right;

    Node(TElem data, int left, int right);
    Node();

    TElem getData() const;
    int getLeft() const;
    int getRight() const;

    void setData(TElem& data);
    void setLeft(int left);
    void setRight(int right);

    void operator = (const Node& node);
};


class SortedMultiMap {
	friend class SMMIterator;
    private:

        int numberOfElements;
        int capacity;
        Relation relationBetweenKeys;

        Node* elements;
        int root;

        void resize(double factor);

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    int getKeyRange() const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
