/*
 * testDrive.cpp
 *
 *  Created on: 2015年5月21日
 *      Author: wangdq
 */
#include <iterator>     // std::ostream_iterator
#include <algorithm>
#include "biheap.h"
#include "biheap.cpp"

void heapTest1();
void heapTest2();
void heapTest3();
void heapTest4();
void heapTest5();
void heapTest6();


int main(int argc, char** argv) {
	heapTest6();
	return 0;
}
// 从顶到底构建heap
void heapTest1() {
	int keys[] = {2,8,6,1,10,15,3,12,11};
	int count = sizeof(keys) / sizeof(int);
	BiHeap<int> heap(keys,keys+count);
	heap.traverse();
	std::cout << std::endl;
}
// 从底到顶构建heap
void heapTest2() {
	int keys[] = {2,8,6,1,10,15,3,12,11};
	int count = sizeof(keys) / sizeof(int);
	BiHeap<int> heap(keys,keys+count,true);
	heap.traverse();
	std::cout << std::endl;
}
// 插入操作
void heapTest3() {
	int keys[] = {49,38,65,97,76,13,27};
	int count = sizeof(keys) / sizeof(int);
	BiHeap<int> heap;
	for(int *pbegin=keys; pbegin != keys+count; ++pbegin)
			heap.push(*pbegin);
	heap.traverse();
	std::cout << std::endl;
}
// 基于heap的优先级队列 出队列和入队列操作
void heapTest4() {
	int keys[] = {2,8,6,1,10,15,3,12,11};
	int count = sizeof(keys) / sizeof(int);
	BiHeap<int> heap(keys,keys+count,true);
	while(!heap.isEmpty()) {
		int top;
		heap.pop(top);
		std::cout << "pop: " << top << std::endl;
	}
}
// 重新分配内存测试
void heapTest5() {
	int keys[] = {2,8,6,1,10,15,3,12,11,49,38,65,97,76,13,27};
	int count = sizeof(keys) / sizeof(int);
	BiHeap<int,3> heap;	// 初始大小较小
	for(int *pbegin=keys; pbegin != keys+count; ++pbegin)
		heap.push(*pbegin);
	heap.traverse();
	std::cout << std::endl;
}
// 堆排序测试  升序
void heapTest6() {
	int keys[] = {2,8,6,1,10,15,3,12,11,49,38,65,97,76,13,27};
	int count = sizeof(keys) / sizeof(int);
	BiHeap<int>::sort(keys, keys+count);
	std::cout << "sorted result: "<<std::endl;
	std::ostream_iterator<int> out_it (std::cout,"\t");
	std::copy ( keys, keys+count, out_it );
	std::cout << std::endl;
}
