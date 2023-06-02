#pragma once
#include "Node.h"
#include <iostream>
using namespace std;
#ifndef QUEUE
#define QUEUE

template <typename T>
class Queue
{
	Node<T>* front;										//Pointer to the front of the queue
	Node<T>* rear;										//Pointer to the back of the queue
	int count;
public:
	Queue()												//Constructor
	{
		front = rear = NULL;
		count = 0;
	}
	bool isEmpty()										//Checks whether the queue is empty or not
	{
		
		if (!front)
			return true;
		return false;
	}
	void enqueue(const T& newItem)						//Enqueues a new item
	{
		Node<T>* newNode = new Node<T>(newItem);
		if (isEmpty())
		{
			front = rear = newNode;
		}
		else
		{
			rear->setNext(newNode);
			rear = newNode;
		}
		count++;
	}
	bool dequeue(T& savedNode)							//Dequeues the front item and keeps its value 
	{
		Node<T>* temp = front;
		if (isEmpty())
			return false;
		else if (front == rear)
		{
			savedNode = front->getItem();
			delete front;
			front = rear = NULL;
			count--;
			return true;
		}
		savedNode = front->getItem();
		front = front->getNext();
		delete temp;
		count--;
		return true;
	}
	bool display()										//EXTRA: displays the items in the queue
	{
		if (isEmpty())
			return false;
		Node<T>* temp = front;
		while (temp->getNext())
		{
			cout << temp->getItem() << ", ";
			temp = temp->getNext();
		}
		cout << temp->getItem();
		return true;
	}
	T peakVal()	{										//*** Returns the value of the item in the front
		// Check if the queue is empty
		if (isEmpty()) {
	
		}else
		return (front->getItemre());
	}
	T& peak() {											//Returns a Reference the item in the front
		// Check if the queue is empty
		if (isEmpty()) {

		}
		else
			return (front->getItemre());
	}
	void clear(T& lastDequeued)							//Clears the items in the queue
	{
		while (!isEmpty())
			dequeue(lastDequeued);
		count = 0;
	}
	int getCount()										//Returns the count of items in the queue
	{
		return count;
	}
	void enqueueArranged(const T& newItem){
		Node<T>* added = new Node<T>(newItem);
		if (isEmpty())
		{
			front = rear = added;
			count++;

			return;
		}else if (count == 1) {
			if (added->getItem() < front->getItem()) {
				rear = front;
				front = added;
			}else
				rear = added;		
		}else {
			Node<T>* currProcess = front;
			Node<T>* temp = new Node<T>(newItem);
			for (int i = 1; i < getCount(); i++) {

				if (currProcess->getNext()!=nullptr&&added->getItem() < currProcess->getNext()->getItem()) {
					temp->setNext(currProcess->getNext());
					currProcess->setNext(added);
					added->setNext(temp);
				}
				currProcess = currProcess->getNext();
			}
		}
		count++;
		
		
	}
	~Queue() {};										//Destructor
};
#endif
