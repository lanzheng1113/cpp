/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月8日
 *      Author: wangdq
 */

#include "biheap.h"
#include "biheap.cpp"
#include <iostream>
void heapTest() ;

int main(int argc,char** argv) {
	heapTest();
	return 0;
}

void heapTest() {

    int keys[] = {2,8,6,1,10,15,3,12,11};
    int count = sizeof(keys) / sizeof(int);
    BiHeapNode<int,int> *nodes = new BiHeapNode<int,int>[count];
    for(int i = 0; i < count;i++) {
    	nodes[i].key = keys[i];
    	nodes[i].value = 2*keys[i];
    }
	BiHeap<int,int> heap(nodes,nodes+count);
	heap.traverse();
	//删除所有元素
	while(!heap.isEmpty()) {
		 std::cout<<"remove root: "<<std::endl;
		 BiHeapNode<int,int> node;
		 heap.removeTop(node);
		 heap.traverse();
	}
	//重新插入
	for(int i = 0; i < count;i++) {
		  heap.insert(keys[i],2*keys[2]);
	}
	std::cout<<"after insert: "<<std::endl;
	heap.traverse();
	delete[] nodes;
}
