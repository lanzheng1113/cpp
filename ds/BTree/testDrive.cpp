/*
 * testDrive.cpp
 *
 *  Created on: 2015年5月22日
 *      Author: wangdq
 */
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <vector>
#include <algorithm>// std::random_shuffle
#include <sstream>
#include <string>
#include "btree.h"
#include "btree.cpp"
#include "treeprinter.h"


void testCase0();
void testCase1();
void testCase2();
void testCase3();
void testCase4();
void testCase5();
void testCase6();
void testCase7();
void randomSearchTest(int testTimes,int elemCount,int searchTime) ;
void randomInsertTest(int testTimes,int elemCount);
void randomRemoveTest(int testTimes,int elemCount,int removeTime);
bool isAscOrdered(std::stringstream &ss);
template<typename T,int M> bool isTreeStateOk(const BTree<T,M> &tree);

const int TEST_M = 7;

int main(int argc,char** argv) {
	int index = 1;
	typedef void(*testFunc)();	// 函数指针
	testFunc fps[] = {testCase0,testCase1,testCase2,testCase3,
								testCase4,testCase5,testCase6,testCase7};
	if(argc == 2) {
		std::stringstream oss;
		oss << argv[1];
		int tmp=-1;
		oss >> tmp;
		if(tmp >= 0 && tmp <= sizeof(fps) / sizeof(*fps) )
			index = tmp;
	}
	fps[index]();
	return 0;
}
/**
 * 流的有序性测试
 */
void testCase0() {
	std::cout<<"Executing test case " << 0 << ": check stream order "<< std::endl;
	std::cout << "input a integer sequence to test if they are in ascending ordered:(Ctrl+z/d to end):"<<std::endl;
	int a = -1;
	std::stringstream sstream;
	while(std::cin >> a)
		 sstream << a << " ";
	if(!isAscOrdered(sstream)) {
		 std::cerr << "Not a ascending ordered sequence!" << std::endl;
		 sstream.clear();
	 }else {
		  std::cout << "Ordered output Ok." << std::endl;
	 }
}
//插入元素测试
void testCase1() {
	std::cout<<"Executing test case " << 1 << ": inserting elements"<< std::endl;
	int elements[] = {8,14,2,15,3,1,16,6,5,27,37,18,25,7,13,20,22,23,24};
	int count = sizeof(elements) / sizeof(int);
	BTree<int> tree;
	BTreePrinter::prefix = std::string("BTree-insert");
	for(int i=0;i < count ;++i) {
		 bool ret=tree.insert(elements[i]);
		 std::cout<<"inserted: "<<elements[i]<<(ret ? " success":" failed!") << std::endl;
		 //tree.breadthFirstTraverse();
		 BTreePrinter::toPng(&tree,std::string("insert: ")+BTreePrinter::intToString(elements[i]));
	}
	//isTreeStateOk(tree);
	BTreePrinter::toPng(&tree,std::string("Build B-Tree"));
}
//删除元素测试1
void testCase2() {
		std::cout<<"Executing test case " << 2 << ": remove elements"<< std::endl;
	    int elements[] = {8,14,2,15,3,1,16,6,5,27,37,18,25,7,13,20,22,23,24};
		int count = sizeof(elements) / sizeof(int);
		BTree<int> tree;
		BTreePrinter::prefix = std::string("BTree-remove1");
		for(int i=0;i < count ;++i) {
			 tree.insert(elements[i]);
		}
		BTreePrinter::toPng(&tree,std::string("initial B-Tree"));
		std::cout<<"tree traverse: "<<std::endl;
		tree.breadthFirstTraverse();
		int reElements[] = {6,7,8,16};
	    count = sizeof(reElements) / sizeof(int);
		for(int i=0;i < count ;++i) {
			 bool ret=tree.remove(reElements[i]);
			 std::cout<<"*********remove: "<<reElements[i]<<(ret ? " success":" failed!") << std::endl;
			 BTreePrinter::toPng(&tree,std::string("remove: ")+BTreePrinter::intToString(reElements[i]));
			 if(!isTreeStateOk(tree))
				 break;
		}
}
//删除元素测试2
void testCase3() {
	    std::cout<<"Executing test case " << 3 << ": remove elements"<< std::endl;
	    int elements[] = {8,14,2,15,3,1,16,6,5,27,37,18,25,7,13,20,22,23,24,40,42,45};
		int count = sizeof(elements) / sizeof(int);
		BTree<int> tree;
		BTreePrinter::prefix = std::string("BTree-remove2");
		for(int i=0;i < count ;++i) {
			 tree.insert(elements[i]);
		}
		std::cout<<"tree traverse: "<<std::endl;
		tree.breadthFirstTraverse();
		int reElements[] = {6,7,8,16,20,24};
	    count = sizeof(reElements) / sizeof(int);
		for(int i=0;i < count ;++i) {
			 bool ret = tree.remove(reElements[i]);
			 std::cout<<"*********remove: "<<reElements[i]<<(ret ? " success":" failed!") << std::endl;
			 if(!isTreeStateOk(tree))
			 		 break;
		}
}
//随机插入测试
void testCase4() {
	std::cout<<"Executing test case " << 4 << ": random inserting elements"<< std::endl;
	randomInsertTest(1,100);
}
// 随机删除测试
void testCase5() {
	std::cout<<"Executing test case " << 5 << ": random remove elements"<< std::endl;
	randomRemoveTest(1,100,100);
}
// 随机查找测试
void testCase6() {
	std::cout<<"Executing test case " << 6 << ": random search elements"<< std::endl;
	randomSearchTest(1,100,10);
}
//删除元素测试3
void testCase7() {
	    std::cout<<"Executing test case " << 3 << ": remove elements"<< std::endl;
	    int elements[] = {32,77,80,82};
		int count = sizeof(elements) / sizeof(int);
		BTree<int> tree;
		for(int i=0;i < count ;++i) {
			 tree.insert(elements[i]);
		}
		std::cout<<"tree traverse: "<<std::endl;
		tree.breadthFirstTraverse();
		int reElements[] = {82,80,77,32,50};
	    count = sizeof(reElements) / sizeof(int);
		for(int i=0;i < count ;++i) {
			 bool ret = tree.remove(reElements[i]);
			 std::cout<<"*********remove: "<<reElements[i]<<(ret ? " success":" failed!") << std::endl;
			 if(!isTreeStateOk(tree))
			 		break;
		}
		// 再次插入
		int insertElements[] = {8,14,2,15,3,1,16,6,5,27,37,18,25,7,13,20,22,23,24};
		count = sizeof(insertElements) / sizeof(int);
		for(int i=0;i < count ;++i) {
			 bool ret=tree.insert(insertElements[i]);
			 std::cout<<"inserted: "<<insertElements[i]<<(ret ? " success":" failed!") << std::endl;
		}
		isTreeStateOk(tree);
}

//随机插入测试
void randomInsertTest(int testTimes,int elemCount) {
	 std::vector<int> ivec;
	 srand(unsigned(time(NULL)));
	 for(int x=0; x<elemCount; x++) ivec.push_back(x);

		 for(int i = 0;i < testTimes ;i++) {
			std::random_shuffle(ivec.begin(), ivec.end());
			BTree<int,TEST_M> tree;
			std::cout << TEST_M << " way B-Tree: "<<std::endl;
			std::cout<<"insert: \t";
			for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
				std::cout<<*it<<"\t";
				tree.insert(*it);
			 }
			if(!isTreeStateOk(tree))
					break;
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
		  BTree<int,TEST_M> tree;
		  std::cout << TEST_M << " way B-Tree: "<<std::endl;
		   std::cout<<"insert: \t";
			for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
				std::cout<<*it<<"\t";
				tree.insert(*it);
			 }
			if(!isTreeStateOk(tree))
					break;
		   std::random_shuffle(ivec.begin(), ivec.end());
		   //随机查找存在的元素
		   for(std::vector<int>::iterator it = ivec.begin(),end= ivec.begin()+searchTime; it != end;++it){
			    BTreeNode<int,TEST_M>* p = tree.search(*it);
			    if(p != 0) {
			    	     std::cout<<"found: "<<*it<<std::endl;
			    }else {
			    	std::cerr<<"error occurred."<<std::endl;
			    	return;
			    }
		   }
		   //查找不存在的数据
		   int notExistElement = 2+elemCount;
		   BTreeNode<int,TEST_M>* p = tree.search(2+notExistElement);
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
		  BTree<int,TEST_M> tree;
		  std::cout << TEST_M << " way B-Tree: "<<std::endl;
		  std::cout<<"insert: \t";
		 for(std::vector<int>::iterator it = ivec.begin(); it != ivec.end();++it) {
		 		std::cout<<*it<<"\t";
		 		tree.insert(*it);
		  }
		 if(!isTreeStateOk(tree))
		 			break;
		   std::random_shuffle(ivec.begin(), ivec.end());
		   //随机删除存在的元素
		   for(std::vector<int>::iterator it = ivec.begin(),end= ivec.begin()+removeTime; it != end;++it){
			   bool ret = tree.remove(*it);
			   std::cout<<"*********remove: "<<*it<<(ret ? " success":" failed!") << std::endl;
			   if(!isTreeStateOk(tree))
			   			break;
		   }
		   std::cout<<"Test case: "<<i<<" ok"<<std::endl;
	}
}
/**
 * 检查流是否升序
 * in c++11 use std::is_sorted instead
 */
bool isAscOrdered(std::stringstream &ss) {

	    long a = 0,b=0;
	    ss >> a;
	    bool ret = true;
	    while(ss >> b) {
	    	 if(b < a) {
	    		 ret = false;
	    		 break;
	    	 }
	    	 a = b;
	    }
	    return ret;
}
/**
 * 根据有序遍历检测树状态是否正常
 * 用于调试
 */
template<typename T,int M>
bool isTreeStateOk(const BTree<T,M> &tree) {
	std::stringstream sstream;
	tree.orderedTraverse(sstream);
	bool ret = true;
	std::cout << "*******************************"<<std::endl;
	if(sstream.eof()) {
		std::cout << "Tree status: ordered traverse,empty ,no output."<<std::endl;
	}
	else if(!isAscOrdered(sstream)) {
			 std::cerr << "Tree status: ordered traverse,Error occurred!" << std::endl;
			 ret = false;
	 }else
		  std::cout << "Tree status: ordered traverse,ascending ordered output Ok." << std::endl;
	if(ret) {
		std::cout<<"tree breadth first traverse: "<<std::endl;
		tree.breadthFirstTraverse();
	}
	std::cout << "*******************************"<<std::endl<<std::endl;
	return ret;
}
