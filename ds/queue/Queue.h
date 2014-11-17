#ifndef _QUEUE_H_
#define _QUEUE_H_

template<typename T>
class Queue
{
public:
	virtual ~Queue(){}
    virtual void enqueue(T data) = 0;
	virtual T dequeue()= 0;
	virtual void clear()=0;
	virtual int getLength()= 0;
    virtual bool isEmpty()=0;
};
#endif
