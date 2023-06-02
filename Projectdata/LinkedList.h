#pragma once
#include "Node.h"
#include <iostream>


#ifndef LINKED_LIST
#define LINKED_LIST

template <class T>
class LinkedList {
	Node<T>* head;											//Pointer to the head node(inserted first)
public:
	LinkedList()											//Constructor
	{
		head = NULL;
	}
	bool isEmpty()											//Checks whether the linkedlist is empty or not
	{
		if (!head)

			return true;
		return false;
	}
	void insertFirst(const T newItem)						//Inserts at the head of the linkedlist
	{
		Node<T>* newNode = new Node<T>(newItem);
		if (isEmpty())
		{
			newNode->setNext(NULL);
			head = newNode;
		}
		else
		{
			newNode->setNext(head);
			head = newNode;
		}
	}
	void insertLast(const T& newItem)						//Inserts at the tail of the linkedlist
	{
		Node<T>* newNode = new Node<T>(newItem);
		Node<T>* temp = head;
		if (isEmpty())
		{
			newNode->setNext(NULL);
			head = newNode;
		}
		else
		{
			while (temp->getNext())
			{
				temp = temp->getNext();
			}
			temp->setNext(newNode);
		}
	}
	void displayList()										//EXTRA: displays the linkedlist
	{
		Node<T>* temp = head;
		if (temp == nullptr)
			return;
		while (temp->getNext())
		{
			cout << temp->getItem() << ", ";
			temp = temp->getNext();
		}
		cout << temp->getItem();
	}
	int count()												//Returns number of items in the linkedlist
	{
		int c = 0;
		Node<T>* temp = head;
		while (temp)
		{
			c++;
			temp = temp->getNext();
		}
		return c;
	}
	bool isFound(const T& key)								//Checks whether a given value is found or not
	{
		Node<T>* temp = head;
		while (temp)
		{
			if (key == temp->getItem())
				return true;
			temp = temp->getNext();
		}
		return false;
	}
	int countNegative()										//Counts the number of negative items in the linkedlist
	{
		int c = 0;
		Node<T>* temp = head;
		while (temp)
		{
			if (temp->getItem() < 0)
				c++;
			temp = temp->getNext();
		}
		return c;
	}
	T getMin()												//Gets the minimum value in the linkedlist
	{
		if (isEmpty())
			return NULL;
		T min = 999999;
		Node<T>* temp = head;
		while (temp)
		{
			if (temp->getItem() < min)
				min = temp->getItem();
			temp = temp->getNext();
		}
		return min;
	}
	void clear()											//Clears all items in the linkedlist
	{
		if (!isEmpty())
		{
			Node<T>* P = head;
			while (head)
			{
				P = head->getNext();
				delete head;
				head = P;
			}
		}

	}
	
	bool removeHead(T& savedNode)							//Deletes head and keeps its value
	{
		if (isEmpty())
			return false;
		Node<T>* temp = head;
		if (head->getNext() == nullptr)
		{
			savedNode = head->getItem();
			delete head;
			head = nullptr;
			return true;
		}
		savedNode = head->getItem();
		temp = head;
		head = head->getNext();
		delete temp;
		temp = nullptr;
		return true;
	}

	T& getHead()												//*** Gets the Head value
	{
		return head->getItemre();
	}

	Node<T>* getHeadPTR()										//*** Get the Head pointer
	{
		return head;
	}

	T deleteNode(Node<T>* nodeToDelete)							//*** delete a node from middle 
	{						
		if (nodeToDelete == nullptr)
			return T();
		T deletedValue = nodeToDelete->getItem();
		if (nodeToDelete == head) 
		{
			head = head->getNext();
			delete nodeToDelete;
			return deletedValue;
		}
		Node<T>* prevNode = nullptr;
		Node<T>* currentNode = head;
		while (currentNode != nullptr && currentNode != nodeToDelete) 
		{
			prevNode = currentNode;
			currentNode = currentNode->getNext();
		}
		if (currentNode == nullptr) 
		{
			// Node not found
			return T();
		}
		prevNode->setNext(currentNode->getNext());
		delete currentNode;
		return deletedValue;
	}

	T deleteLast()											//*** delete the last node
	{
		Node<T>* p = head;
		Node<T>* pre = p;
		if (isEmpty())
			return T();

		while (p->getNext())
		{
			pre = p;
			p = p->getNext();
		}
		pre->setNext(nullptr);
		T deletedValue = p->getItem();
		delete p;
		return deletedValue;
	}
	
	~LinkedList() {}										//Destructor
};
#endif
