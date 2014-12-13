/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月13日
 *      Author: wangdq
 */

#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <vector>
#include <algorithm>// std::random_shuffle
#include "rbtree.h"
#include "rbtree.cpp"

void testCase0();

int main() {

	testCase0();
	return 0;
}

//插入元素测试
void testCase0() {
	int elements[] = {12,1,9,2,0,11,7,19, 4 ,15,18,5,14,13,10,16,6,3,8,17};
	int count = sizeof(elements) / sizeof(int);
	RBTree<int> tree;
	for(int i=0;i < count ;++i) {
		 tree.insert(elements[i]);
		 std::cout<<"inserted: "<<elements[i]<<",traverse: "<<std::endl;
		 tree.inorder();
		 std::cout<<std::endl;
	}
}
