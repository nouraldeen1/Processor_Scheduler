#pragma once
#include <iostream>
using namespace std;
#ifndef CIRCULAR_Queue
#define CIRCULAR_Queue
#include"Node.h"
template<class T>
class CircularQueue
{
private:
	Node<T>* Front; // front pointer

	Node<T>* Rear;// rear pointer

	int count;//  Number of elements in the list

public:


	CircularQueue() // Constructor
	{
		Front = nullptr;
		Rear = nullptr;
		count = 0;
	}


	void Enqueue(T item)// Insert a new element
	{
		Node<T>* NewNode = new Node <T>;
		NewNode->setItem(item);
		if (IsEmpty()) // case 1
		{
			Front = NewNode;
			Rear = NewNode;
			Rear->setNext(Front);
			count++;
		}
		else // case 2 "generic"
		{
			Rear->setNext(NewNode);
			Rear = NewNode;
			Rear->setNext(Front);
			count++;
		}
	}


	bool IsEmpty() // check if the list has no element or not
	{
		return (count == 0);
	}


	bool Dequeue(T& item) // Delete the first element (if possible) and return by reffernce the deleted item
	{
		if (IsEmpty()) // case 1 
			return false;
		else
		{
			Node<T>* temp = new Node <T>;
			if (count == 1) // case 2
			{
				temp = Front;
				item = temp->getItem();
				Front = nullptr;
				Rear = nullptr;
				delete temp;
				temp = nullptr;
				count--;
				return true;
			}
			else // case 3 "generic"
			{
				temp = Front;
				Rear->setNext(temp->getNext());
				Front = temp->getNext();
				item = temp->getItem();
				temp->setNext(nullptr);
				delete temp;
				temp = nullptr;
				count--;
				return true;
			}
		}
	}


	T PeekRear() // To get the item in the rear
	{
		return Rear->getItem();
	}


	int getSize() // get number of elements in the list
	{
		return count;
	}

	void PrintInformation() // Print list information on console
	{
		Node<T>* ptr = new Node<T>;
		ptr = Front;
		if (IsEmpty())
			return; // does not print anything
		else if (getSize() != 1) // number of elements in the list greater than one element
		{
			do
			{
				cout << ptr->getItem() << ", "; // Print all elements except rear
				ptr = ptr->getNext();
			} while (ptr != Rear);
			cout << ptr->getItem(); // print the rear
		}
		else
			cout << ptr->getItem();
	}


	void Clear(T& item) // Dequeue all element and make the list empty
	{
		while (!IsEmpty())
			Dequeue(item);
	}


	~CircularQueue()
	{

	}

};
#endif
