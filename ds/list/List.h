#ifndef _LISElemType_H_
#define _LISElemType_H_

template <class  T>
class List
{
public:
    virtual ~List(){}
    //add methods
	virtual void addFromHead(const T& data)=0;
	virtual void addFromTail(const T& data)=0;
	//delete methods
	virtual void removeFromHead()=0;
	virtual void removeFromTail()=0;
	virtual void remove(const T& data)=0;
	//check methods
	virtual bool containsOf(const T& data)=0;
	virtual bool isEmpty()=0;
	//get methods
	virtual int getSize()=0;
	//for testing,print list content
	virtual void print()=0;
};
template <class  T>
class SNode
{
public:
	SNode()
	{
	   next = 0;
    }
    SNode(T v,SNode* n=0):data(v),next(n)
	{
	}
public:
	T data;
	SNode* next;
};
template<class T>
class DNode
{
public:
	DNode()
	{
	  prev = next = 0;
    }
	DNode(T v,DNode* p,DNode* n):data(v),prev(p),next(n)
	{
	}
public:
	T data;
    DNode *prev,*next;
};
#endif