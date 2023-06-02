#pragma once
#include "PairedNode.h"

#ifndef PAIRED_QUEUE
#define PAIRED_QUEUE

template<typename T>
ostream& operator<<(ostream& os, const item<T>& p)					//EXTRA: overloaded << operator to display the queue 
{
	os << "(" << p.FirstItem << ", " << p.SecondItem << ")";
	return os;
}

template <typename T>
class PairedQueue
{
	PairedNode<T>* front;
	PairedNode<T>* rear;
	int count;
public:
	PairedQueue()													//Constructor
	{
		front = rear = NULL;
		count = 0;
	}
	bool isEmpty()													//Checks whether the queue is empty or not
	{
		if (!front)
			return true;
		return false;
	}
	void enqueue(const T& newItem1, const T& newItem2)				//Enqueues a new item
	{
		PairedNode<T>* newPairedNode = new PairedNode<T>(newItem1, newItem2);
		if (isEmpty())
		{
			front = rear = newPairedNode;
		}
		else
		{
			rear->setNext(newPairedNode);
			rear = newPairedNode;
		}
		count++;
	}
	bool dequeue(item<T>& savedItem)								//Dequeues the front item and keeps its value 
	{
		PairedNode<T>* temp = front;
		if (isEmpty())
			return false;
		else if (front == rear)
		{
			savedItem = front->getItem();
			delete front;
			front = rear = NULL;
			count--;
			return true;
		}
		savedItem = front->getItem();
		front = front->getNext();
		delete temp;
		count--;
		return true;
	}
	bool display()													//EXTRA: displays the items in the queue
	{
		if (isEmpty())
			return false;
		PairedNode<T>* temp = front;
		while (temp)
		{
			cout << "[" << temp->getItem() << "]" << "-->";
			temp = temp->getNext();
		}
		cout << "NULL\n";
		return true;
	}
	item<T> peak()													//Returns the item in the front
	{
		return front->getItem();
	}
	void clear(item<T>& lastDequeued)								//Clears the items in the queue
	{
		while (!isEmpty())
			dequeue(lastDequeued);
		count = 0;
	}
	int getCount()													//Returns the count of items in the queue
	{
		return count;
	}
	bool dequeueMod()												//Dequeues the front item and DOES NOT keep value 
	{
		PairedNode<T>* temp = front;
		if (isEmpty())
			return false;
		else if (front == rear)
		{
			delete front;
			front = rear = NULL;
			count--;
			return true;
		}
		front = front->getNext();
		delete temp;
		count--;
		return true;
	}
	~PairedQueue() {};
	int getSize()								//Returns the actual size of the array
	{
		return count;
	}//Destructor
};
#endif