#ifndef _LINKED_LIST_QUEUE_H_
#define _LINKED_LIST_QUEUE_H_

#include <list>
#include "Queue.h"

template<typename T>
class LinkedListQueue : public Queue<T>
{
public:
	void enqueue(T data)
	{
	   list.push_back(data);
	}
	T dequeue()
	{
       T data = list.front();
	   list.pop_front();
	   return data;
	}
	void clear()
	{
       list.clear();
	}
	int getLength()
	{
       return list.size();
	}
    bool isEmpty()
	{
       return list.empty();
	}
private:
     std::list<T> list;
};

#endif
