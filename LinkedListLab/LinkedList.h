#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "LinkedListInterface.h"
#include <stddef.h>
#include <sstream>
using namespace std;

/** Linked List */
template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:

	size_t listSize = 0;

	struct Node
	{
		T data;
		Node* next;
		Node(const T& d) : data(d), next(NULL) {}
		Node(const T& d, Node* n) : data(d), next(n) {}
	};

	Node* head;

	bool contains(T value)
	{
		Node* node_ptr = head;
		while (node_ptr != NULL)
		{
			if (node_ptr->data == value)
			{
				return true;
			}
			node_ptr = node_ptr->next;
		}
		return false;
	}

public:
	LinkedList() { this->head = NULL; }
	~LinkedList() { clear(); }

	/** Insert Node at beginning of linked list (no duplicates) */
	virtual bool insertHead(T value)
	{
		if (contains(value))
		{
			return false;
		}

		Node* bob = new Node(value);
		bob->next = head;
		head = bob;

		listSize++;
		return true;
	}

	/** Insert Node at end of linked list (no duplicates) */
	virtual bool insertTail(T value)
	{
		if (contains(value))
		{
			return false;
		}

		Node* node_ptr = head;
		while (node_ptr->next != NULL)
		{
			node_ptr = node_ptr->next;
		}

		Node* bob = new Node(value);
		node_ptr->next = bob;

		listSize++;
		return true;
	}

	/** Insert node after matchNode (no duplicates) */
	virtual bool insertAfter(T matchNode, T node)
	{
		if (contains(node))
		{
			return false;
		}
		Node* node_ptr = head;           // find insertion point
		while (node_ptr->data != matchNode)
		{
			node_ptr = node_ptr->next;
			if (node_ptr == NULL)
			{
				return false;
			}
		}

		// insert "Bob" after "matchNode"
		Node* bob = new Node(node);
		bob->next = node_ptr->next;      // Step 1
		node_ptr->next = bob;            // Step 2

		listSize++;
		return true;
	}

	/** Remove Node from linked list */
	virtual bool remove(T value)
	{
		Node* node_ptr = head;          // point to the first node
		size_t positionCtr = 0;

		while (node_ptr != NULL)
		{
			if (node_ptr->data == value)
			{
				if (positionCtr == 0)
				{
					Node* temp = head;
					head = head->next;
					delete temp;
				}
				else if (node_ptr->next == NULL)
				{
					node_ptr = head;
					Node* prevNode = node_ptr;
					while (node_ptr->next != NULL)
					{
						prevNode = node_ptr;
						node_ptr = node_ptr->next;
					}
					prevNode->next = NULL;
					delete node_ptr;
				}
				else
				{
					node_ptr = head;
					Node* prevNode = node_ptr;
					for (size_t i = 0; i < positionCtr; i++)
					{
						prevNode = node_ptr;
						node_ptr = node_ptr->next;
					}
					prevNode->next = node_ptr->next;
					delete node_ptr;
				}
				listSize--;
				return true;
			}
			positionCtr++;
			node_ptr = node_ptr->next;
		}
		return false;
	}

	/** Remove all Nodes from linked list */
	virtual bool clear()
	{
		Node* node_ptr = head;
		Node* temp;
		while (node_ptr != NULL)
		{
			temp = node_ptr;
			node_ptr = node_ptr->next;
			delete(temp);
		}
		head = NULL;
		listSize = 0;
		return true;
	}

	/** Return a reference to the value at Node(index)
		Throw an error if out of range.
	NOTE: STL list does NOT support the at accessor. */
	virtual T at(int index)
	{
		Node* node_ptr = head;
		int nodeCtr = 0;
		while (node_ptr != NULL)
		{
			if (nodeCtr == index)
			{
				return node_ptr->data;
			}
			node_ptr = node_ptr->next;
			nodeCtr++;
		}
		if (index < 0 || head == NULL || nodeCtr <= index)
		{
			throw 20;
			return 0;
		}
		return 0;
	}

	/** Returns the number of nodes in the linked list */
	virtual size_t size() const
	{
		return listSize;
	}

	/** Return a level order traversal of a Linked List as a string */
	virtual std::string toString() const
	{
		if (listSize == 0)
		{
			return "Empty";
		}
		stringstream ss;
		Node* node_ptr = head;           // point to the first node
		while (node_ptr != NULL)         // stop at the last node
		{
			ss << node_ptr->data;
			if (node_ptr->next != NULL)
			{
				ss << " ";
			}
			node_ptr = node_ptr->next;    // move to the next node
		}
		return ss.str();
	}

	
};
#endif   // LINKED_LIST_H
