#include <new>
#include <exception>
#include <algorithm>    //std::copy
#include "ArrayStack.h"

template<typename T,int initCapacity>
ArrayStack<T,initCapacity>::ArrayStack(int cap)
:capacity(cap)
{
	base = new T[capacity];
	top = base ; // empty stack
}

template<typename T,int initCapacity>
ArrayStack<T,initCapacity>::~ArrayStack()
{
	delete[] base;
	std::cout<<"Free Array Stack Memory"<<std::endl;
}

template<typename T,int initCapacity>
void ArrayStack<T,initCapacity>::push(T data)
{
	 if(top - base >= capacity)    //stack size over capacity
	 {  
	     resize(2*capacity);	//resize as needed
	 }
	 *top++ = data;
}
template<typename T,int initCapacity>
T ArrayStack<T,initCapacity>::pop()
{
	if(top == base)
	{
		throw std::logic_error("pop at empty stack");
	}
	return *--top;
}

template<typename T,int initCapacity>
T ArrayStack<T,initCapacity>::getTop()
{
	 if(top == base)
	{
	   throw std::logic_error("getTop at empty stack");
	}
	return *(top-1);
}

template<typename T,int initCapacity>
bool ArrayStack<T,initCapacity>::isEmpty() 
{
	return top == base;
}

template<typename T,int initCapacity>
void ArrayStack<T,initCapacity>::clear()
{
	top = base;
}

template<typename T,int initCapacity>
int ArrayStack<T,initCapacity>::getSize()
{
	return top-base;
}
template<typename T,int initCapacity>
void ArrayStack<T,initCapacity>::resize(int cap)
{  
   if(cap <= capacity)
	   return;
   int size = top - base;
   
   T* mem = 0;
   try
   {
	  mem = new T[cap];//reallocate memory
   }
   catch (const std::bad_alloc& ba)
   {
	  std::cerr << "stack out of memory " << ba.what() <<std::endl;
	  delete[] base;
	  throw;
   }
   if(mem != 0)
   {  
	  std::copy(base,base+size,mem);	//copy elements
	  delete[] base;	//release old memory
	  base = mem;	//reset base
	  top = base+size;	//reset top
	  capacity = cap;	//update capacity
   }
}