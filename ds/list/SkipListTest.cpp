#include <iostream>
#include "SkipList.h"
#include "SkipList.cpp"

void testUnit1();
void testUnit2();
void testUnit3();
void testUnit4();

int main(int argc, char *argv[])
{
	testUnit4();
	return 0;
}
void testUnit4()
{
	SkipList<char> list;
	std::cout<<"insert a: "<<std::endl;
	list.insert('a');
	std::cout<<"insert f: "<<std::endl;
	list.insert('f');
	std::cout<<"insert b: "<<std::endl;
	list.insert('b');
	std::cout<<"insert k: "<<std::endl;
	list.insert('k');
	std::cout<<"insert e: "<<std::endl;
	list.insert('e');
	std::cout<<"insert d: "<<std::endl;
	list.insert('d');
	list.print();
	
	std::cout<<"remove f: "<<std::endl;
	list.remove('f');
	list.print();
}
void testUnit3()
{
	SkipList<int> list;
	list.print();
	std::cout<<"find 12 : "<<(list.find(12) ? "yes":"no")<<std::endl;

	std::cout<<"insert 7: "<<std::endl;
	list.insert(7);

	list.print();
	std::cout<<"remove 7: "<<std::endl;
	list.remove(7);
	list.print();
	std::cout<<std::endl;

	std::cout<<"insert 12: "<<std::endl;
	list.insert(12);
	std::cout<<"insert 45: "<<std::endl;
	list.insert(45);
	std::cout<<"insert 32: "<<std::endl;
	list.insert(32);

	list.print();
	std::cout<<"remove 12: "<<std::endl;
	list.remove(12);
	list.print();
	std::cout<<std::endl;

	std::cout<<"insert 27: "<<std::endl;
	list.insert(27);
	std::cout<<"insert 88: "<<std::endl;
	list.insert(88);
	std::cout<<"find 88 : "<<(list.find(88) ? "yes":"no")<<std::endl;
	list.print();
	std::cout<<"remove 45: "<<std::endl;
	list.remove(45);
	list.print();
	int *p = list.find(88);
	*p = 119;
	std::cout<<"modify element 88 to 119:"<<std::endl;
	list.print();
	std::cout<<std::endl;

}
void testUnit2()
{
	SkipList<int> list;
	std::cout<<"insert 7: "<<std::endl;
	list.insert(7);
	std::cout<<"insert 12: "<<std::endl;
	list.insert(12);
	std::cout<<"insert 45: "<<std::endl;
	list.insert(45);
	std::cout<<"insert 32: "<<std::endl;
	list.insert(32);
	std::cout<<"insert 27: "<<std::endl;
	list.insert(27);
	std::cout<<"insert 88: "<<std::endl;
	list.insert(88);
	list.print();
	std::cout<<"find 7 : "<<(list.find(7) ? "yes":"no")<<std::endl;
	std::cout<<"find 32 : "<<(list.find(32) ? "yes":"no")<<std::endl;
	std::cout<<"find 23 : "<<(list.find(23) ? "yes":"no")<<std::endl;
	std::cout<<"find 85 : "<<(list.find(85) ? "yes":"no")<<std::endl;
	std::cout<<"find 88 : "<<(list.find(88) ? "yes":"no")<<std::endl;
	int *p = list.find(45);
	*p = 54;
	std::cout<<"modify element 45 to 54:"<<std::endl;
	list.print();
}
void testUnit1()
{

	SkipList<int> list;
	std::cout<<"insert 7: "<<std::endl;
	list.insert(7);
	list.print();

	std::cout<<"insert 32: "<<std::endl;
	list.insert(32);
	list.print();

	std::cout<<"insert 14: "<<std::endl;
	list.insert(14);
	list.print();

	std::cout<<"insert 21: "<<std::endl;
	list.insert(21);
	list.print();

	std::cout<<"insert 71: "<<std::endl;
	list.insert(71);
	list.print();

	std::cout<<"insert 37: "<<std::endl;
	list.insert(37);
	list.print();

	std::cout<<"insert 85: "<<std::endl;
	list.insert(85);
	list.print();

	std::cout<<"insert 117: "<<std::endl;
	list.insert(117);
	list.print();

}