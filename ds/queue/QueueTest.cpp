#include <iostream>
#include "ArrayQueue.h"
#include "LinkedListQueue.h"
#include "ResizingArrayQueue.h"

int main(int argc, char *argv[])
{
	//Queue<int> *queue = new ArrayQueue<int,15>();
	Queue<int> *queue = new LinkedListQueue<int>();
	//Queue<int> *queue = new ResizingArrayQueue<int,5>();
	std::cout<<"enqueue 1-10"<<std::endl;
	int i = 0;
	while(i++ < 10)
		queue->enqueue(i);
	//std::cout<<"queue full ? "<<(queue->isFull() ? "yes":"no")<<std::endl;
	
	std::cout<<"queue length: "<<queue->getLength()<<std::endl;

	std::cout<<"dequeue: "<<queue->dequeue()<<std::endl;
	std::cout<<"dequeue: "<<queue->dequeue()<<std::endl;

    

	std::cout<<"clear queue" << std::endl;
	queue->clear();

	std::cout<<"enqueue 1-10"<<std::endl;
	i = 0;
	while(i++ < 10)
		queue->enqueue(i);
	std::cout<<"dequeue till empty: ";
    while(!queue->isEmpty())
		std::cout<<queue->dequeue()<<"\t";

	std::cout<<std::endl;

	delete queue;
	return 0;
}
