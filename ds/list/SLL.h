#ifndef _SINGLE_LINK_LIST_
#define _SINGLE_LINK_LIST_
#include "List.h"

template <class  T>
class SLL : public List<T>
{
public:
    SLL();
    ~SLL();
	void addFromHead(const T& data);
	void addFromTail(const T& data);
	void removeFromHead();
	void removeFromTail();
	void remove(const T& data);
	bool containsOf(const T& data);
	bool isEmpty();
	int getSize();
	void print();
private:
	SNode<T> *head,*tail;
};
#endif
