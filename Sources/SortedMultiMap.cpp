#include "../Headers/SMMIterator.h"
#include "../Headers/SortedMultiMap.h"
#include <vector>
#include <exception>
using namespace std;


Node::Node(TElem data, int left, int right)
{
	this->data = data;
	this->left = left;
	this->right = right;
}

Node::Node()
{
	this->data = NULL_TELEM;
	this->left = -1;
	this->right = -1;
}

TElem Node::getData() const
{
	return this->data;
}

int Node::getLeft() const
{
	return this->left;
}

int Node::getRight() const
{
	return this->right;
}

void Node::setData(TElem& data)
{
	this->data = data;
}

void Node::setLeft(int left)
{
	this->left = left;
}

void Node::setRight(int right)
{
	this->right = right;
}

void Node::operator = (const Node& node)
{
	this->data = node.data;
	this->left = node.left;
	this->right = node.right;
}


SortedMultiMap::SortedMultiMap(Relation r) 
{
	this->numberOfElements = 0;
	this->capacity = 10;
	this->relationBetweenKeys = r;
	this->root = -1;

	this->elements = new Node[this->capacity];
}


// Copy all the elements => Theta(n)
void SortedMultiMap::resize(double factor)
{
	Node* newElementsArray = new Node[(int)(this->capacity * factor)];

	if (newElementsArray == nullptr)
		return;

	for (int i = 0; i < this->numberOfElements; i++)
		newElementsArray[i] = this->elements[i];

	this->capacity *= factor;
	delete[] this->elements;
	this->elements = newElementsArray;
}


// Best case: No elements => Theta(1)
// Average case: Find the position for the new element => Theta(log n)
// Worst case: Resize => Theta(n)
void SortedMultiMap::add(TKey c, TValue v) 
{
	TElem data = std::pair<TKey, TValue>(c, v);
	Node newNode = Node(data, -1, -1);

	if (this->numberOfElements == this->capacity)
		this->resize(2);

	if (this->numberOfElements == 0)
	{
		this->root = 0;
		this->elements[this->root] = newNode;
		this->numberOfElements++;

		return;
	}

	// Search where to insert the new pair.
	int currentNodeIndex = this->root;
	int previousNodeIndex = -1;

	while (currentNodeIndex != -1)
	{
		previousNodeIndex = currentNodeIndex;

		if (this->relationBetweenKeys(c, this->elements[currentNodeIndex].getData().first))
			currentNodeIndex = this->elements[currentNodeIndex].getLeft();
		else
			currentNodeIndex = this->elements[currentNodeIndex].getRight();
	}

	// Insert.
	if (this->relationBetweenKeys(c, this->elements[previousNodeIndex].getData().first))
		this->elements[previousNodeIndex].left = this->numberOfElements;
	else
		this->elements[previousNodeIndex].right = this->numberOfElements;
	
	this->elements[this->numberOfElements++] = newNode;
}


// Theta(log n)
vector<TValue> SortedMultiMap::search(TKey c) const 
{
	std::vector<TValue> values;

	int currentNodeIndex = this->root;

	while (currentNodeIndex != -1)
	{
		if (this->elements[currentNodeIndex].getData().first == c)
			values.push_back(this->elements[currentNodeIndex].getData().second);

		if (this->relationBetweenKeys(c, this->elements[currentNodeIndex].getData().first))
			currentNodeIndex = this->elements[currentNodeIndex].getLeft();
		else
			currentNodeIndex = this->elements[currentNodeIndex].getRight();
	}

	return values;
}


// Theta(log n)
int SortedMultiMap::getKeyRange() const
{
	if (this->isEmpty())
		return -1;

	int minKey = 0, maxKey = 0;

	int currentNodeIndex = this->root;

	// Search the min key. (The left-most node)
	while (currentNodeIndex != -1)
	{
		minKey = this->elements[currentNodeIndex].data.first;

		currentNodeIndex = this->elements[currentNodeIndex].getLeft();
	}

	currentNodeIndex = this->root;
	// Search the max key. (The right-most node)

	while (currentNodeIndex != -1)
	{
		maxKey = this->elements[currentNodeIndex].data.first;

		currentNodeIndex = this->elements[currentNodeIndex].getRight();
	}

	return maxKey - minKey;
}


// Best case: The node to be removed is the root having at most one child => Theta(1)
// Otherwise, the time complexity is Theta(log n)
bool SortedMultiMap::remove(TKey c, TValue v) 
{
	int currentNodeIndex = this->root;
	int previousNodeIndex = -1;
	bool leftChild = false;

	if (this->numberOfElements == this->capacity / 4 && this->numberOfElements > 10)
		this->resize(0.5);

	while (currentNodeIndex != -1)
	{
		if (this->elements[currentNodeIndex].getData().first == c && this->elements[currentNodeIndex].getData().second == v)
		{
			// The node has no children.
			if (this->elements[currentNodeIndex].getLeft() == -1 && this->elements[currentNodeIndex].getRight() == -1)
			{
				if (currentNodeIndex == this->root)
				{
					this->root = -1;
					this->numberOfElements--;

					return true;
				}

				if (leftChild)
					this->elements[previousNodeIndex].left = -1;
				else
					this->elements[previousNodeIndex].right = -1;
			}
			// The node has only a right child.
			else if (this->elements[currentNodeIndex].getLeft() == -1)
			{
				if (currentNodeIndex == this->root)
				{
					this->root = this->elements[currentNodeIndex].getRight();
					this->numberOfElements--;

					return true;
				}

				if (leftChild)
					this->elements[previousNodeIndex].left = this->elements[currentNodeIndex].right;
				else
					this->elements[previousNodeIndex].right = this->elements[currentNodeIndex].right;
			}
			// The node has only a left child.
			else if (this->elements[currentNodeIndex].getRight() == -1)
			{
				if (currentNodeIndex == this->root)
				{
					this->root = this->elements[currentNodeIndex].getLeft();
					this->numberOfElements--;

					return true;
				}

				if (leftChild)
					this->elements[previousNodeIndex].left = this->elements[currentNodeIndex].left;
				else
					this->elements[previousNodeIndex].right = this->elements[currentNodeIndex].left;
			}
			// The node has both children.
			else
			{
				// Find the "maximum" in the left subtree.
				int maxNodeIndex = this->elements[currentNodeIndex].getLeft();
				int previousMaxNodeIndex = maxNodeIndex;
				// TKey maxKey = this->elements[maxNodeIndex].getData().first;

				while (this->elements[maxNodeIndex].getRight() != -1)
				{
					// maxKey = this->elements[maxNodeIndex].getData().first;

					previousMaxNodeIndex = maxNodeIndex;
					maxNodeIndex = this->elements[maxNodeIndex].getRight();
				}

				if (previousMaxNodeIndex == maxNodeIndex)
				{
					this->elements[maxNodeIndex].right = this->elements[currentNodeIndex].right;
					this->elements[currentNodeIndex] = this->elements[maxNodeIndex];
				}
				else 
				{
					this->elements[previousMaxNodeIndex].right = -1;

					this->elements[currentNodeIndex].data = this->elements[maxNodeIndex].data;
				}
			}

			this->numberOfElements--;
			return true;
		}

		previousNodeIndex = currentNodeIndex;

		if (this->relationBetweenKeys(c, this->elements[currentNodeIndex].getData().first))
		{
			currentNodeIndex = this->elements[currentNodeIndex].getLeft();
			leftChild = true;
		}
		else
		{
			currentNodeIndex = this->elements[currentNodeIndex].getRight();
			leftChild = false;
		}
	}

	return false;
}


// Theta(1)
int SortedMultiMap::size() const 
{
	return this->numberOfElements;
}


// Theta(1)
bool SortedMultiMap::isEmpty() const 
{
	return this->numberOfElements == 0;
}


// Traverse all nodes => Theta(n)
SMMIterator SortedMultiMap::iterator() const 
{
	return SMMIterator(*this);
}


SortedMultiMap::~SortedMultiMap() 
{
	delete[] this->elements;
}
