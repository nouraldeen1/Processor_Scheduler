#pragma once
#include "pairedNode.h"
#include <iostream>
using namespace std;

template <typename T>
struct item
{
	T FirstItem;
	T SecondItem;
};

template <typename T>
class PairedNode
{
	item<T> I;
	PairedNode<T>* next;
public:
	PairedNode()												//Default constructor
	{
		next = nullptr;
	}
	PairedNode(T newItem1, T newItem2)										//Parameterized constructor	
	{
		I.FirstItem = newItem1;
		I.SecondItem = newItem2;
		next = nullptr;
	}

	//Setters

	void setItem(T newItem1, T newItem2)
	{
		I.FirstItem = newItem1;
		I.SecondItem = newItem2;
	}
	void setNext(PairedNode<T>* newNext)
	{
		next = newNext;
	}

	//Getters 

	item<T> getItem()
	{
		return I;
	}
	PairedNode<T>* getNext()
	{
		return next;
	}
	~PairedNode() {};
};