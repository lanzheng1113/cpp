/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月4日
 *      Author: wangdq
 */

#include "AVLTree.h"
#include "AVLTree.cpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>

using namespace std;

void randomTest();

int main()
{
	randomTest();
	return 0;
}
void randomTest() {
	     std::vector<int> ivec;
	     srand(unsigned(time(NULL)));
	     for(int x=0; x<100; x++) ivec.push_back(x);
	     int testTimes = 5;
		 for(int i = 0;i < testTimes ;i++) {
			  std::random_shuffle(ivec.begin(), ivec.end());
			  AVLTree<int,int> avlTree;
			  int count = rand() % 100;
			  std::cout<<std::endl<<"Insert: ";
			   for(int j= 0 ;j < count ;j++) {
				    std::cout<<ivec[j]<<"  ";
			 		avlTree.insert(ivec[j],ivec[j]);
			 	}
			 	avlTree.inorderTraverse();
			 	std::cout<<std::endl<<"Tree height: "<<avlTree.height()<<std::endl;
			     //随机删除元素直到为空
			 	while(!avlTree.isEmpty()) {
			 		int r = rand() % count;
			 		bool ret = avlTree.FindAndDelete(ivec[r]);
			 		if(!ret) continue;
			 		std::cout<<std::endl<<"Delete: "<<ivec[r]<<std::endl;
			 		avlTree.inorderTraverse();
			 	}
			 	std::cout<<std::endl<<"Test case: "<<i<<" ok"<<std::endl;
		}
}

