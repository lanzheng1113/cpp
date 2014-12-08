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

void randomInsertTest(int testTimes,int elemCount);
void simpleTest() ;
void randomSearchTest(int testTimes,int elemCount,int searchTime);

int main(int arc,char** argv)
{
	randomSearchTest(5,100,10); // 随机插入和查找测试
	//randomInsertTest(1,100);	//随机插入删除测试
	return 0;
}
void simpleTest() {
	     int elements[] = {44,55,66,77,88,99};
	     SplayTree<int,int> tree;
		 for (int * begin = elements;begin != elements+6 ;++begin) {
			 tree.insert(*begin,*begin);
		 }
		 std::cout<<"inorder: \t"<<std::endl;
		 tree.inorder();
		 std::cout<<"preorder: \t"<<std::endl;
		 tree.preorder();
		 int v = 0;
		 tree.search(88,v);
		 std::cout<<"inorder: \t"<<std::endl;
		 tree.inorder();
		 std::cout<<"preorder: \t"<<std::endl;
		 tree.preorder();
}
void randomSearchTest(int testTimes,int elemCount,int searchTime) {
	 std::vector<int> ivec;
	 srand(unsigned(time(NULL)));
	 for(int x=0; x<elemCount; x++) ivec.push_back(x);
     if(searchTime > elemCount)
    	   searchTime = elemCount;
	 for(int i = 0;i < testTimes ;i++) {
		  std::random_shuffle(ivec.begin(), ivec.end());
		  SplayTree<int,int> tree;
		  std::cout<<"insert: \t";
		  for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
			  std::cout<<*it<<"\t";
			  tree.insert(*it,*it);
		   }
		   std::cout<<std::endl<<"inorder: \t";
		   tree.inorder();
		   std::random_shuffle(ivec.begin(), ivec.end());
		   //随机查找元素
		   for(std::vector<int>::iterator it = ivec.begin(),end= ivec.begin()+searchTime; it != end;++it){
			    int v;
				tree.search(*it,v);
				std::cout<<std::endl<<"searched:\t "<<*it<<std::endl<<"inorder: "<<std::endl;
				tree.inorder();
				std::cout<<"preorder:"<<std::endl;
				tree.preorder();
		   }
		  std::cout<<"Test case: "<<i<<" ok"<<std::endl;
	}
}
void randomInsertTest(int testTimes,int elemCount) {
	     std::vector<int> ivec;
	     srand(unsigned(time(NULL)));
	     for(int x=0; x<elemCount; x++) ivec.push_back(x);

		 for(int i = 0;i < testTimes ;i++) {
			  std::random_shuffle(ivec.begin(), ivec.end());
			  SplayTree<int,int> tree;
			  std::cout<<"insert: \t";
			  for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
				  std::cout<<*it<<"\t";
				  tree.insert(*it,*it);
			   }
			   std::cout<<std::endl<<"inorder: \t";
			   tree.inorder();
			   std::random_shuffle(ivec.begin(), ivec.end());
			   //随机删除元素
			   for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it){
				    tree.FindAndDelete(*it);
				    std::cout<<std::endl<<"delete: \t"<<*it<<std::endl<<"inorder: "<<std::endl;
				   	tree.inorder();
			   }
			  std::cout<<"Test case: "<<i<<" ok"<<std::endl;
		}
}

