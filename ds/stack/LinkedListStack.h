#ifndef _LINKED_LIST_STACK_H_
#define _LINKED_LIST_STACK_H_

#include <list>

template<typename T>
class LinkedListStack : public Stack<T>
{
public:
	  ~LinkedListStack()
      {
          //let std::list do for us
	  }
	  void push(T data)
      {
           list.push_front(data);
	  }
	  T pop()
	  {    
		   T data = list.front();
		   list.pop_front();
           return data;
	  }
      bool isEmpty()
      {
           return list.empty();
	  }
      void clear()
      {  
           list.clear();
	  }
	  T getTop()
      {
          return list.front();
	  }
	  int getSize()
      {
          return list.size();
	  }
private:
      std::list<T> list;
};
#endif

