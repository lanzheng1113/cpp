#ifndef _ARRAY_QUEUE_H_
#define _ARRAY_QUEUE_H_

#include <exception>
#include "Queue.h"

template<typename T,int maxCapacity = 128>
class ArrayQueue : public Queue<T>
{
public:
    ArrayQueue():front(0),rear(0)
	{
	}
    void enqueue(T data)
	{
       if((rear+1)% maxCapacity == front)
	   {  
		  std::cerr<<"logic error : enqueue at full queue. "<<std::endl;
          throw std::logic_error ("enqueue at full queue");
	   }
	   queue[rear] = data;
	   rear = (rear+1) % maxCapacity;//rear point to the next of the last 
	}
	T dequeue()
	{
       if(front == rear)
	   {   
		   std::cerr<<"logic error : dequeue at empty queue. "<<std::endl;
		   throw std::logic_error("dequeue at empty queue");
	   }
       T data = queue[front];
	   front = (front+1) % maxCapacity; // move front to the next position
	   return data;
	}
	int getLength()
	{
      return (rear-front+maxCapacity) % maxCapacity;
	}
	void clear()
	{
       rear = front = 0;
	}
    bool isEmpty()
	{
       return front == rear;
	}
	bool isFull()
	{
		return (rear+1) % maxCapacity == front ;
	}
private:
	int front,rear;
    T queue[maxCapacity];
};

#endif