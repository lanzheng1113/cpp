/*
 * TestDrive.cpp
 *
 *  Created on: 2014年12月2日
 *      Author: wangdq
 */
#include <iostream>
#include "bst.h"
#include "bst.cpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <algorithm>    // std::random_shuffle

void randomTest() ;
void simpleTest();

int main(int argc,char** argv) {
	randomTest();
	 return 0;
}
void simpleTest() {
	int elements[] = {7,3,8,5,14};
	 BST<int> bst;
	 for (int * begin = elements;begin != elements+5 ;++begin) {
		  bst.insert(*begin);
	 }
	 bst.inorder();
	 std::cout<<"\n\n";
	 bst.findAndDeleteByCopying(5);
	 std::cout<<"\n\n";
	 bst.inorder();
}
void randomTest() {
	     std::vector<int> ivec;
	     srand(unsigned(time(NULL)));
	     for(int x=0; x<100; x++) ivec.push_back(x);
	     int testTimes = 1;
		 for(int i = 0;i < testTimes ;i++) {
			  std::random_shuffle(ivec.begin(), ivec.end());
			  BST<int> tree;
			  int count = rand() % 100;
			  std::cout<<std::endl<<"Insert: ";
			   for(int j= 0 ;j < count ;j++) {
				    std::cout<<ivec[j]<<"  ";
				    tree.insert(ivec[j]);
			 	}
			   std::cout<<std::endl<<"elements:";
			   tree.inorder();
			     //随机删除元素直到为空
			 	while(!tree.isEmpty()) {
			 		int r = rand() % count;
			 		bool ret = tree.findAndDeleteByCopying(ivec[r]);
			 		if(!ret) continue;
			 		std::cout<<std::endl<<"Deleted: "<<ivec[r]<<std::endl;
			 		std::cout.flush();
			 		tree.inorder();
			 	}
			 	std::cout<<std::endl<<"Test case: "<<i<<" ok"<<std::endl;
		}
}
