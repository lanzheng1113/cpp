#include <iostream>
#include "ArrayStack.h"
#include "ArrayStack.cpp"
#include "LinkedListStack.h"


int main(int argc, char *argv[])
{   
	//Stack<int> *stack = new ArrayStack<int,5>();
	Stack<int> *stack = new LinkedListStack<int>();
	std::cout<<"push 1-7"<<std::endl;
	stack->push(1);
	stack->push(2);
	stack->push(3);
	stack->push(4);
	stack->push(5);
	stack->push(6);
	stack->push(7);
	std::cout<<"get top: "<<stack->getTop()<<std::endl;
	std::cout<<"pop top: "<<stack->pop()<<std::endl;
    std::cout<<"get top: "<<stack->getTop()<<std::endl;
	std::cout<<"pop top: "<<stack->pop()<<std::endl;
    
	std::cout<<"stack size: "<<stack->getSize()<<std::endl;
	std::cout<<"clear stack"<<std::endl;
    stack->clear();
    std::cout<<"stack isEmpty: "<<(stack->isEmpty()?"yes":"no")<<std::endl;
    std::cout<<"push 1-7"<<std::endl;
    stack->push(1);
	stack->push(2);
	stack->push(3);
	stack->push(4);
	stack->push(5);
	stack->push(6);
	stack->push(7);
	std::cout<<"pop till empty:"<<std::endl;
    while(!stack->isEmpty())
		std::cout<<stack->pop()<<"\t";
	std::cout<<std::endl;
	delete stack;
	return 0;
}