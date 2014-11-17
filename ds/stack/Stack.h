#ifndef _STACK_H_
#define _STACK_H_

template<typename T>
class Stack
{
public:
      virtual ~Stack(){};
      virtual void push(T data)=0;
	  virtual T pop()=0;
      virtual bool isEmpty()=0;
      virtual void clear() = 0;
	  virtual T getTop()=0;
	  virtual int getSize()=0;
};
#endif
