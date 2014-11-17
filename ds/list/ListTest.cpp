#include <iostream>
#include "CDLL.h"
#include "CDLL.cpp"
#include "SLL.h"
#include "SLL.cpp"
#include "CSLL.h"
#include "CSLL.cpp"

void SLLTestUnit();
void CSLLTestUnit();
void CDLLTestUnit();

int main(int argc, char *argv[])
{   
	std::cout<<"single linked list test:"<<std::endl;
	SLLTestUnit();
	std::cout<<"circular single linked list test:"<<std::endl;
	CSLLTestUnit();
	std::cout<<"circular doubly linked list test:"<<std::endl;
	CDLLTestUnit();
	return 0;
}
void SLLTestUnit()
{
    List<int> *list = new SLL<int>();
    
	list->addFromHead(5);
	list->addFromHead(4);
	list->addFromHead(7);
	list->addFromTail(9);
	list->addFromHead(3);
	std::cout<<"init content:\t\t";
	list->print();
	
	
	list->remove(3);
	std::cout<<"remove 3:\t\t";
	list->print();

	list->remove(9);
	std::cout<<"remove 9:\t\t";
	list->print();
    
    std::cout<<"contain -1?:\t\t"<<
		(list->containsOf(-1)?"yes":"no")<<std::endl;
	std::cout<<"contain 4?:\t\t"<<
		(list->containsOf(4)?"yes":"no")<<std::endl;
	
	list->removeFromHead();
	std::cout<<"remove head:\t\t";
	list->print();

	list->addFromTail(12);
	std::cout<<"add tail 12:\t\t";
	list->print();

    std::cout<<"list size:\t\t"<<list->getSize()<<std::endl;

	list->remove(5);
    std::cout<<"remove 5:\t\t";
	list->print();

	list->removeFromTail();
	std::cout<<"remove tail:\t\t";
	list->print();

	//free memory
	std::cout<<"delete list:\t\t";
	delete list;
}
void CSLLTestUnit()
{
    List<int> *list = new CSLL<int>();
    
	list->addFromHead(5);
	list->addFromHead(4);
	list->addFromHead(7);
	list->addFromTail(9);
	list->addFromHead(3);
	std::cout<<"init content:\t\t";
	list->print();
	
	
	list->remove(3);
	std::cout<<"remove 3:\t\t";
	list->print();

	list->remove(9);
	std::cout<<"remove 9:\t\t";
	list->print();
    
    std::cout<<"contain -1?:\t\t"<<
		(list->containsOf(-1)?"yes":"no")<<std::endl;
	std::cout<<"contain 4?:\t\t"<<
		(list->containsOf(4)?"yes":"no")<<std::endl;
	
	list->removeFromHead();
	std::cout<<"remove head:\t\t";
	list->print();

	list->addFromTail(12);
	std::cout<<"add tail 12:\t\t";
	list->print();

    std::cout<<"list size:\t\t"<<list->getSize()<<std::endl;

	list->remove(5);
    std::cout<<"remove 5:\t\t";
	list->print();

	list->removeFromTail();
	std::cout<<"remove tail:\t\t";
	list->print();

	//free memory
	std::cout<<"delete list:\t\t";
	delete list;
}
void CDLLTestUnit()
{
    CDLL<int> *list = new CDLL<int>();
    
	list->addFromHead(5);
	list->addFromHead(4);
	list->addFromHead(7);
	list->addFromTail(9);
	list->addFromHead(3);
	std::cout<<"init content:\t\t";
	list->print();

	std::cout<<"inverse print:\t\t";
	list->printInverse();
	
	list->remove(3);
	std::cout<<"remove 3:\t\t";
	list->print();

	list->remove(9);
	std::cout<<"remove 9:\t\t";
	list->print();
    
    std::cout<<"contain -1?:\t\t"<<
		(list->containsOf(-1)?"yes":"no")<<std::endl;
	std::cout<<"contain 4?:\t\t"<<
		(list->containsOf(4)?"yes":"no")<<std::endl;
	
	list->removeFromHead();
	std::cout<<"remove head:\t\t";
	list->print();

	list->addFromTail(12);
	std::cout<<"add tail 12:\t\t";
	list->print();

    std::cout<<"list size:\t\t"<<list->getSize()<<std::endl;

	list->remove(5);
    std::cout<<"remove 5:\t\t";
	list->print();

	list->removeFromTail();
	std::cout<<"remove tail:\t\t";
	list->print();

	//free memory
	std::cout<<"delete list:\t\t";
	delete list;
}