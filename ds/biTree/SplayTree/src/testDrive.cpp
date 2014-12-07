/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月4日
 *      Author: wangdq
 */

#include "splaytree.h"
#include "splaytree.cpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <algorithm>    // std::random_shuffle

using namespace std;

void randomInsertTest();
void simpleTest() ;

int main()
{
	simpleTest();

	return 0;
}
void simpleTest() {
	     int elements[] = {44,55,66,77,88,99};
	     SplayTree<int,int> tree;
		 for (int * begin = elements;begin != elements+6 ;++begin) {
			 tree.insert(*begin,*begin);
		 }
		 tree.inorderTraverse();
		 std::cout<<"\n\n";
		 std::cout<<"\n\n";
		 tree.preorder();
		 int v = 0;
		 tree.search(88,v);
		 std::cout<<"\n\n";
		 tree.inorderTraverse();
		 std::cout<<"\n\n";
		 tree.preorder();
}
void randomInsertTest() {
	     std::vector<int> ivec;
	     srand(unsigned(time(NULL)));
	     for(int x=0; x<100; x++) ivec.push_back(x);
	     int testTimes = 1;
		 for(int i = 0;i < testTimes ;i++) {
			  std::random_shuffle(ivec.begin(), ivec.end());
			  SplayTree<int,int> tree;
			  int count = rand() % 100+1;
			  std::cout<<std::endl<<"Insert: ";
			   for(int j= 0 ;j < count ;j++) {
				    std::cout<<ivec[j]<<"  ";
				    tree.insert(ivec[j],ivec[j]);
			 	}
			   std::cout<<std::endl<<"elements: ";
			   tree.inorderTraverse();
			     //随机删除元素直到为空
			 	while(!tree.isEmpty()) {
			 		int r = rand() % count;
			 		bool ret = tree.FindAndDelete(ivec[r]);
			 		if(!ret) continue;
			 		std::cout<<std::endl<<"Delete: "<<ivec[r]<<std::endl;
			 		tree.inorderTraverse();
			 	}
			 	std::cout<<std::endl<<"Test case: "<<i<<" ok"<<std::endl;
		}
}

