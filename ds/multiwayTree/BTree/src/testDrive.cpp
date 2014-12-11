/*
 * testDrive.cpp
 *
 *Created on: 2014年12月10日
 *Author: wangdq
 */

#include "btree.h"
#include "btree.cpp"
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <vector>
#include <algorithm>// std::random_shuffle

void testCase0();
void testCase1();
void randomInsertTest(int testTimes,int elemCount);
void randomSearchTest(int testTimes,int elemCount,int searchTime) ;
void randomRemoveTest(int testTimes,int elemCount,int removeTime);

int main() {
	//randomInsertTest(1,100);
	//randomSearchTest(1,100,10);
	randomRemoveTest(1,100,100);
	return 0;
}
//插入元素测试
void testCase0() {
	//int elements[] = {8,14,2,15,3,1,16,6,5,27,37,18,25,7,13,20,22,23,24};
	int elements[] = {4,12,7,24,9,5,25,6,3,	19,15,10,11,8,23,17,	16,18,2	,20,22,21,	1,13,	0,14	};
	int count = sizeof(elements) / sizeof(int);
	BTree<int> tree;
	for(int i=0;i < count ;++i) {
		 tree.insert(elements[i]);
		 std::cout<<"inserted: "<<elements[i]<<",traverse: "<<std::endl;
		 tree.breadFirstTraverse();
	}
	tree.orderedTraverse();
}
//删除元素测试
void testCase1() {
	    int elements[] = {1,8,12,3,10,0,7,18,2,19,14,17,4,16,15,6,13,11,5,9};
		int count = sizeof(elements) / sizeof(int);
		BTree<int> tree;
		for(int i=0;i < count ;++i) {
			 tree.insert(elements[i]);
		}
		std::cout<<"tree traverse: "<<std::endl;
		tree.breadFirstTraverse();
		int reElements[] = {13,11,3,19,18};
	   count = sizeof(reElements) / sizeof(int);
		for(int i=0;i < count ;++i) {
			tree.remove(reElements[i]);
			std::cout<<"removed: "<<reElements[i]<<",traverse: "<<std::endl;
			tree.breadFirstTraverse();
			std::cout<<"ordered traverse: \t";
			 tree.orderedTraverse();
		}
}
//随机插入测试
void randomInsertTest(int testTimes,int elemCount) {
	 std::vector<int> ivec;
	 srand(unsigned(time(NULL)));
	 for(int x=0; x<elemCount; x++) ivec.push_back(x);

		 for(int i = 0;i < testTimes ;i++) {
			std::random_shuffle(ivec.begin(), ivec.end());
			BTree<int> tree;
			std::cout<<"insert: \t";
			for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
				std::cout<<*it<<"\t";
				tree.insert(*it);
			 }
			 std::cout<<std::endl<<"ordered traverse: \t";
			 tree.orderedTraverse();
			 std::cout<<"bread first traverse:";
			 tree.breadFirstTraverse();
			std::cout<<"Test case: "<<i<<" ok"<<std::endl;
		}
}
//随机查找测试
void randomSearchTest(int testTimes,int elemCount,int searchTime) {
	 std::vector<int> ivec;
	 srand(unsigned(time(NULL)));
	 for(int x=0; x<elemCount; x++) ivec.push_back(x);
     if(searchTime > elemCount)
    	   searchTime = elemCount;
	 for(int i = 0;i < testTimes ;i++) {
		  std::random_shuffle(ivec.begin(), ivec.end());
		  BTree<int> tree;
		   std::cout<<"insert: \t";
			for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
				std::cout<<*it<<"\t";
				tree.insert(*it);
			 }
			 std::cout<<std::endl<<"ordered traverse: \t";
			 tree.orderedTraverse();
			 std::cout<<"bread first traverse:";
			 tree.breadFirstTraverse();
		   std::random_shuffle(ivec.begin(), ivec.end());
		   //随机查找存在的元素
		   for(std::vector<int>::iterator it = ivec.begin(),end= ivec.begin()+searchTime; it != end;++it){
			    BTreeNode<int>* p = tree.search(*it);
			    if(p != 0) {
			    	     std::cout<<"found: "<<*it<<std::endl;
			    }else {
			    	std::cerr<<"error occurred."<<std::endl;
			    	return;
			    }
		   }
		   //查找不存在的数据
		   int notExistElement = 2+elemCount;
		   BTreeNode<int>* p = tree.search(2+notExistElement);
		   if(p == 0) {
		   			std::cout<<"not found: "<<2+elemCount<<std::endl; // 未找到则Ok
			}else {
				std::cerr<<"error occurred."<<std::endl; // 出错
				return;
			}
		   std::cout<<"Test case: "<<i<<" ok"<<std::endl;
	}
}
//随机删除测试
void randomRemoveTest(int testTimes,int elemCount,int removeTime) {
	 std::vector<int> ivec;
	 srand(unsigned(time(NULL)));
	 for(int x=0; x<elemCount; x++) ivec.push_back(x);
     if(removeTime > elemCount)
    	 removeTime = elemCount;
	 for(int i = 0;i < testTimes ;i++) {
		  std::random_shuffle(ivec.begin(), ivec.end());
		  BTree<int> tree;
		  std::cout<<"insert: \t";
		 for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
		 		std::cout<<*it<<"\t";
		 		tree.insert(*it);
		  }
		   std::cout<<std::endl<<"ordered traverse: \t";
		   tree.orderedTraverse();
		   std::cout<<"bread first traverse:";
		   tree.breadFirstTraverse();
		   std::random_shuffle(ivec.begin(), ivec.end());
		   //随机删除存在的元素
		   for(std::vector<int>::iterator it = ivec.begin(),end= ivec.begin()+removeTime; it != end;++it){
			   std::cout<<"*********remove: "<<*it<<std::endl;
			   tree.remove(*it);
			   std::cout<<"bread first  traverse: "<<std::endl;
			   tree.breadFirstTraverse();
			   std::cout<<"ordered traverse: \t";
			   tree.orderedTraverse();
		   }
		   std::cout<<"Test case: "<<i<<" ok"<<std::endl;
	}
}
