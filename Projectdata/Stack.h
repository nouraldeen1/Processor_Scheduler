#pragma once
#include "Node.h"
#include <iostream>
using namespace std;
#ifndef STACK
#define STACK

template <typename T>
class Stack
{
	Node<T>* top;													//Pointer to the top of the stack
public:
	Stack()															//Constructor
	{
		top = NULL;
	}
	bool isEmpty()													//Checks whether the stack is empty or not
	{
		if (top == NULL)
			return true;
		return false;
	}
	void push(const T& newItem)										//Puts an item in the stack
	{
		Node<T>* newNode = new Node<T>(newItem);
		if (isEmpty())
			top = newNode;
		else
		{
			Node<T>* temp = top;
			top = newNode;
			top->setNext(temp);
		}
	}
	bool pop()														//Removes an item from the stack
	{
		if (isEmpty())
			return false;
		else if (top->getNext())
		{
			Node<T>* temp = top;
			top = top->getNext();
			delete temp;
			return true;
		}
		delete top;
		top = NULL;
		return true;
	}
	T peak()														//Returns the value of the top item of the stack
	{
		return top->getItem();
	}
	bool display()													//EXTRA: displays the stack
	{
		if (isEmpty())
			return false;
		Node<T>* temp = top;
		while (temp)
		{
			cout << "[" << temp->getItem() << "]" << "-->";
			temp = temp->getNext();
		}
		cout << "NULL\n";
		return true;
	}
	void clear()													//Clears the stacks
	{
		while (!isEmpty())
			pop();
	}
	~Stack() {};													//Destructor
};
#endif