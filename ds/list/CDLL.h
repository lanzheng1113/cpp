#ifndef _CIRCULAR_DOUBLE_LINK_LIST_
#define _CIRCULAR_DOUBLE_LINK_LIST_

#include "List.h"
template<class T>
class CDLL : public List<T>
{
public:
    CDLL();
    ~CDLL();
	void addFromHead(const T& data);
	void addFromTail(const T& data);
	void removeFromHead();
	void removeFromTail();
	void remove(const T& data);
	bool containsOf(const T& data);
	bool isEmpty();
	int  getSize();
	void print();
	void printInverse();
private:
	DNode<T>* tail;
};

#endif
