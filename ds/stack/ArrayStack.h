#ifndef _ARRAY_STACK_H_
#define _ARRAY_STACK_H_
#include "Stack.h"



template<typename T,int initCapacity = 5>

class ArrayStack : public Stack<T>
{
public:
	  ArrayStack(int cap=initCapacity);
	 ~ArrayStack();
      void push(T data);
	  T pop();
	  T getTop();
	  bool isEmpty();
	  void clear();
	  int getSize();
private:
	  void resize(int cap);
private:
	  T *base,*top;
      int capacity;
};
#endif
