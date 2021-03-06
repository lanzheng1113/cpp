#include <iostream>
#include <string>
#include <functional>   // std::less  std::greater
#include "PriorityQueue.h"

class Person
{
public:
	// default constructor
	Person() : age(0) {}
	Person(int age, std::string name) {
		this->age = age; this->name = name;
	}
	bool operator <(const Person& rhs) const
	{
		return this->age < rhs.age;
	}
	int age;
	std::string name;
};
void testIntegers()
{
	PriorityQueue<int> queue;
	std::cout<<"enqueue 1-10: "<<std::endl;
	int i = 0;
	while(i++ < 10)
		queue.enqueue(i);
	std::cout<<"dequeue till empty: "<<std::endl;
    while(!queue.isEmpty())
		std::cout<<queue.dequeue()<<"\t";
	std::cout<<std::endl;
}
void testPerson()
{
	PriorityQueue<Person> queue;
	queue.enqueue(Person(24,"Calvin"));
	queue.enqueue(Person(30,"Benny"));
	queue.enqueue(Person(28,"Alison"));
	std::cout<<"dequeue till empty: "<<std::endl;
    while(!queue.isEmpty())
	{
		Person p = queue.dequeue();
		std::cout<<p.age<<", "<<p.name<<std::endl;
	}
	std::cout<<std::endl;
}

int main(int argc, char *argv[])
{
	testIntegers();
	testPerson();
	return 0;
}
