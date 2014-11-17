#ifndef _RESIZING_ARRAY_QUEUE_H_
#define _RESIZING_ARRAY_QUEUE_H_

#include <exception>
#include <new>			//std::bad_alloc
#include <algorithm>    //std::copy
#include "Queue.h"
/**
	A circular array buffer queue
	with a initialize capacity and can resize as needed
*/
template<typename T,int initCapacity = 64>
class ResizingArrayQueue : public Queue<T>
{
public:
	ResizingArrayQueue():capacity(initCapacity)
	{
	   queue = new T[capacity];
	   front = rear = 0;
	}
	~ResizingArrayQueue()
	{
		delete[] queue;
		std::cout<<"Free Resizing Array Queue memory"<<std::endl;
	}
	void enqueue(T data)
	{
	   if((rear+1)% capacity == front)	//queue full
	   {  
		  resize(2*capacity);	// resize as needed
	   }
	   queue[rear] = data;
	   rear = (rear+1) % capacity;//rear point to the next of the last 
	}
	T dequeue()
	{
	   if(front == rear)	//empty queue,can not dequeue
	   {   
		   std::cerr<<"logic error : dequeue at empty queue. "<<std::endl;
		   throw std::logic_error("dequeue at empty queue");
	   }
       T data = queue[front];
	   front = (front+1) % capacity; // move front to the next position
	   return data;
	}
	void clear()
	{
		front = rear;
	}
	int getLength()
	{
		return (rear-front+capacity) % capacity;
	}
    bool isEmpty()
	{
        return front == rear;
	}
private:
	void resize(int cap);
private:
	T* queue;
    int capacity;
    int front,rear;	//integer index,can treated as pointer
};

template<typename T,int initCapacity>
void ResizingArrayQueue<T,initCapacity>::resize(int cap)
{   
	T* mem = 0;
	try
	{
		mem = new T[cap];	//allocate memory
	}
	catch (const std::bad_alloc& ba)
	{
		std::cerr << "queue out of memory " << ba.what() <<std::endl;
		delete[] queue;
		throw;
	}
	if(mem != 0)
	{   
		if(front < rear)
		{
			std::copy(queue+front,queue+rear,mem);//copy from front to rear
		}else if(front > rear)
		{   
			//note source and destination pointer
			std::copy(queue+front,queue+capacity,mem);//copy from front to end
			std::copy(queue,queue+rear,mem+capacity-front);//copy from 0 to rear
		}
		int length  = (rear-front+capacity) % capacity;
		delete[] queue;	//release old memory
		queue = mem;	//reset queue pointer
		front = 0;		//reset front index
		rear = length;	//reset rear index
		capacity = cap;	//update capacity
	}
}

#endif