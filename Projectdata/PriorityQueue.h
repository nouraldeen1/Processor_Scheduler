#pragma once
#include <iostream>
using namespace std;

#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

template<typename T>

class PriorityQueue
{
private:
	int capacity;								//Capacity is the number of available buckets(indices) in the array
	int size;									//Size is the actual number of buckets used
	T* heap;

	//UTILITY FUNCTIONS

	int parent(int i) { return i / 2; }
	int left(int i) { return 2 * i; }
	int right(int i) { return 2 * i + 1; }
	void siftUp(int i)							//Bubbles up the item through the heap
	{
		while (heap[i] < heap[parent(i)])
		{
			T temp = heap[parent(i)];
			heap[parent(i)] = heap[i];
			heap[i] = temp;
			i = parent(i);
		}
	}
	void siftDown(int i)						//Bubbles down the item through the heap
	{
		while (left(i) <= size)
		{
			T temp1;
			int temp = left(i);
			if (heap[left(i)] > heap[right(i)] && right(i) <= size)
				temp = right(i);
			if (heap[i] <= heap[temp])
				break;
			temp1 = heap[i];
			heap[i] = heap[temp];
			heap[temp] = temp1;
			i = temp;
		}
	}
public:
	PriorityQueue(int c)						//Parametarized constructor (Takes capacity)
	{
		capacity = c;
		size = 0;
		heap = new T[c];
	}
	bool isEmpty()								//Checks whether the heap is empty or not
	{
		if (size == 0)
			return true;
		return false;
	}
	void insert(T& item)							//Inserts an item in the heap
	{
		if (isEmpty())
		{
			heap[0] = item;
			size++;
			return;
		}
		size++;
		heap[size] = item;
		if (heap[size] < heap[parent(size)])
		{
			siftUp(size);
		}
	}
	T& dequeue()									//Dequeues the minimum priority item(root node)
	{
		if (!isEmpty())
		{
			T temp = heap[1];
			heap[1] = heap[size];
			size--;
			siftDown(1);
			return temp;
		}
	}
	T& peek()									//Returns the value of the minimum priotiy item(root node)
	{
		if (!isEmpty())
			return heap[1];
	}
	void display()								//EXTRA: displays the heap
	{
		for (int i = 1; i < size; i++)
			cout << heap[i] << ", ";
		cout << heap[size] << endl;
	}
	int getSize()								//Returns the actual size of the array
	{
		return size;
	}
	void clear()								//Clears the heap
	{
		for (int i = 1; i <= size; i++)
			heap[i] = NULL;
		size = 0;
	}

	~PriorityQueue()							//Destructor
	{

		delete[] heap;
	}
};
#endif 
