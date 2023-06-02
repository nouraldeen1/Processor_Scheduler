#pragma once
#include <iostream>
using namespace std;
#ifndef GENERIC_LINKED_LIST
#define GENERIC_LINKED_LIST
#include"Node.h"
template<class T>
class GenericLinkedList
{
private:
	Node<T>* Head; // Head pointer
	Node<T>* Tail; // Tail pointer
	int count;//  Number of elements in the list

public:


	GenericLinkedList() // Constructor
	{
		Head = nullptr;
		Tail = nullptr;
		count = 0;
	}


	void Insert(T item)// Insert a new element
	{
		Node<T>* NewNode = new Node <T>;
		NewNode->setItem(item);
		if (IsEmpty()) // case 1
		{
			Head = NewNode;
			Tail = NewNode;
			count++;
		}
		else // case 2 "generic"
		{
			Tail->setNext(NewNode);
			Tail = NewNode;
			count++;
		}
	}


	bool IsEmpty() // check if the list has no element or not
	{
		return (count == 0);
	}


	bool Delete(T& value) // Delete the first element (if possible) and return by reffernce the deleted item
	{
		if (IsEmpty()) // case 1 
			return false;
		else
		{
			Node<T>* temp = new Node <T>;
			if (count == 1) // case 2 "the regular scenario"
			{
				if (Head->getItem() == value)
				{
					temp = Head;
					item = temp->getItem();
					Head = nullptr;
					Tail = nullptr;
					delete temp;
					temp = nullptr;
					count--;
					return true;
				}
				else
					return false;
			}
			else // case 3 "the killing element scenario"
			{
				Node<T>* ptr = new Node<T>;
				ptr = Head;
				if (Head->getItem() == item)
				{
					temp = Head;
					item = temp->getItem();
					Head = Head->getNext();
					delete temp;
					temp = nullptr;
					count--;
					return true;
				}
				while (ptr != Tail)
				{
					if (ptr->getNext()->getItem() == value)
						break;
					else if (ptr->getNext() == Tail)
						break;
					else
						ptr = ptr->getNext();
				}
				if (ptr->getNext() && ptr->getNext()->getItem() == value && ptr->getNext() != Tail)
				{
					temp = ptr->getNext();
					ptr->setNext(temp->getNext());
					temp->setNext(nullptr);
					delete temp;
					temp = nullptr;
					count--;
					return true;
				}
				else if (ptr->getNext() && ptr->getNext()->getItem() == value && ptr->getNext() == Tail)
				{
					temp = Tail;
					Tail = ptr;
					delete temp;
					temp = nullptr;
					count--;
					return true;
				}
				else
					return false;
			}
		}
	}


	int getSize() // get number of elements in the list
	{
		return count;
	}

	void PrintInformation() // Print list information on console
	{
		Node<T>* ptr = new Node<T>;
		ptr = Head;
		if (IsEmpty())
			return;
		else if (getSize() != 1)
		{
			while (ptr != Tail)
			{
				cout << ptr->getItem() << ", "; // print all elements excpet last element 
				ptr = ptr->getNext();
			}
			cout << ptr->getItem(); // print the last element
		}
		else
			cout << ptr->getItem();
	}


	void Clear(T& item) // Dequeue all element and make the list empty
	{
		while (!IsEmpty())
			Delete(item);
	}


	~GenericLinkedList()
	{

	}

};
#endif


