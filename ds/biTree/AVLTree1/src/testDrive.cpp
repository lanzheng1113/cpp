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
	/*
	int elements[] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
	//int elements[] = {50,25,75,10,30,60,80,5,15,27,55,1};
	int size = sizeof(elements) /sizeof(int);
	AVLTree<int,int> avlTree;
	for(int i = 0 ;i < size ;i++) {
		avlTree.insert(elements[i],elements[i]);
	}
	avlTree.inorderTraverse();
    //随机删除元素直到为空
	while(!avlTree.isEmpty()) {
		int r = rand() % size;
		bool ret = avlTree.FindAndDelete(elements[r]);
		if(!ret) continue;
		std::cout<<std::endl<<"delete: "<<elements[r]<<std::endl;
		avlTree.inorderTraverse();
	}*/
	randomTest();
	return 0;
}
void randomTest() {
	     std::vector<int> ivec;
	     srand(unsigned(time(NULL)));
	     for(int x=0; x<100; x++) ivec.push_back(x);
	     int testTimes = 5;
		 for(int i = 0;i < testTimes ;i++) {
			  random_shuffle(ivec.begin(), ivec.end());
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

