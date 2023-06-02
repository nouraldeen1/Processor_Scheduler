#pragma once
#ifndef NODE
#define NODE

template <typename T>
class Node
{
	T item;												//The item to be stored in the node
	Node<T>* next;										//Pointer to the next node []--->[]
	//*** FORKING
	Node<T>* left;										//Pointer to the left child
	Node<T>* right;										//Pointer to the right child
public:
	Node()												//Default constructor
	{
		next = nullptr;
		//*** FORKING
		left = nullptr;
		right = nullptr;
	}
	Node(T newItem)										//Parameterized constructor	
	{
		item = newItem;
		next = nullptr;
		//*** FORKING
		left = nullptr;
		right = nullptr;
	}

	//Setters

	void setItem(T newItem)
	{
		item = newItem;
	}
	void setNext(Node<T>* newNext)
	{
		next = newNext;
	}

	//*** Forking

	void setLeft(Node<T>* newLeft)
	{
		left = newLeft;
	}
	void setRight(Node<T>* newRight)
	{
		right = newRight;
	}

	//Getters 

	T getItem()
	{
		return item;
	}
	T& getItemre()
	{
		return item;
	}
	

	Node<T>* getNext()
	{
		return next;
	}

	//*** Forking
	
	Node<T>* getLeft()
	{
		return left;
	}
	Node<T>* getRight()
	{
		return right;
	}
	~Node() {};											//Destructor
};
#endif

