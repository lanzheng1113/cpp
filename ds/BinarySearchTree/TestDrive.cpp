/*
 * TestDrive.cpp
 *
 *  Created on: 2015年5月14日
 *      Author: wangdq
 */
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <algorithm>    // std::random_shuffle
#include <sstream>
#include "bst.h"
#include "dswtree.h"
#include "avltree.h"
#include "treeprinter.h"
#include "splaytree.h"
#include "timef.h"

void testCase0();
void testCase1();
void testCase2();
void testCase3();
void testCase4();
void testCase5();
void testCase6();
void testCase7();
void testCase8();
void testCase9();
void testCase10();
void testCase11();
void testCase12();
void getRandomNumber(std::vector<int> &ivec,int endNum,int startNum);


int main(int argc,char** argv) {
	int index = 0;
	typedef void(*testFunc)();	// 函数指针
	testFunc fps[] = {testCase0,testCase1,testCase2,testCase3,
								testCase4,testCase5,testCase6,testCase7,
								testCase8,testCase9,testCase10,
								testCase11,testCase12};
	if(argc == 2) {
		std::stringstream oss;
		oss << argv[1];
		int tmp=-1;
		oss >> tmp;
		if(tmp >= 0 && tmp <= sizeof(fps) / sizeof(*fps) )
			index = tmp;
	}
	std::cout<<"Executing test case: " << index << std::endl;
	fps[index]();
	return 0;
}
/**
 * 二叉树的插入和删除测试
 */
void testCase0() {
	 int insertEle[] = {20,15,30,17,25,19,40,32,50};
	 BST bst;
	 BiTreePrinter::prefix=std::string("BST-testcase0-bymerging");
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  bst.insert(*begin);
	 }
	 bst.toPng(std::string("builded BST"));
	 bst.bwritePng = false;
	 bst.inorder();
	 std::cout<<"\n\n";
	 bst.bwritePng = true;
	 bst.findAndRemoveByMerging(20);
	 /*
	 bst.findAndRemoveByMerging(30);
	 bst.findAndRemoveByMerging(20);
	 bst.findAndRemoveByMerging(50);
	 bst.findAndRemoveByCopying(25);*/
	 bst.toPng(std::string("final BST"));
	 bst.bwritePng = false;
	 bst.inorder();
	 std::cout<<"\n\n";
}
/**
 * 二叉树的搜索和遍历
 */
void testCase1() {
	 int insertEle[] = {20,15,30,17,25,19,40,32,50};
	 BST bst;
	 bst.bwritePng = false;		// 不写入png文件
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  bst.insert(*begin);
	 }
	 BSTNode* node = bst.search(20);
	 std::cout<<"Height of node 20: " << bst.getHeight(node)<<"\n\n";
	 BSTNode* prev=0;
	 node = bst.iterativeSearch(20,prev);
	 std::cout<<"Height of node 20: " << bst.getHeight(node)<<"\n\n";
	 std::cout << "breadth first : "<<std::endl;
	 bst.breadthFirst();
	 std::cout << "\n\n";

	 std::cout << "******************"<<std::endl;
	 std::cout << "recursive pre-order: "<<std::endl;
	 bst.preorder();
	 std::cout<<"\n\n";
	 std::cout << "iterative pre-order : "<<std::endl;
	 bst.iterativePreorder();
	 std::cout<<"\n\n";

	 std::cout << "******************"<<std::endl;
	 std::cout << "recursive in-order: "<<std::endl;
	 bst.inorder();
	 std::cout<<"\n\n";
	 std::cout << "MorrisInorder : "<<std::endl;
	 bst.MorrisInorder();
	 std::cout<<"\n\n";
	 std::cout << "iterative in-order : "<<std::endl;
	 bst.iterativeInorder();
	 std::cout<<"\n\n";

	 std::cout << "******************"<<std::endl;
	 std::cout << "recursive post-order: "<<std::endl;
	 bst.postorder();
	 std::cout<<"\n\n";
	 std::cout << "iterative post-order : "<<std::endl;
	 bst.iterativePostorder();
	 std::cout<<"\n\n";

}
/**
 * 从有序数组构建平衡二叉树
 */
void testCase2() {
	 int insertEle[] = {9,7,6,3,4,2,5,1,0,8};
	 BiTreePrinter::prefix=std::string("BST-testcase2");
	 std::sort(insertEle,insertEle+sizeof(insertEle) / sizeof(insertEle[0]));  // sort the insertEle
	 BST bst;
	 bst.bwritePng = false;
	 bst.balanceTree(insertEle,0,sizeof(insertEle) / sizeof(insertEle[0])-1);
	 bst.bwritePng = true;
	 bst.toPng(std::string("BST from ordered array"));
}
/**
 * DSW算法构建平衡二叉树
 */
void testCase3() {
	int insertEle[] = {20,15,30,17,25,19,40,32,50};
	 DSWTree dsw;
	 BiTreePrinter::prefix=std::string("DSW");
	 dsw.bwritePng = false;
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  dsw.insert(*begin);
	 }
	 dsw.bwritePng = true;
	 dsw.toPng("initial BST");
	 dsw.balance();
	 dsw.toPng("final BST");
}
/**
 * AVL 插入测试
 */
void testCase4() {
	int insertEle[] = {13,24,37,90,53,10,30,27,15,7,41,35};
	 AVLTree avl;
	 BiTreePrinter::prefix="AVL-insert";
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  bool ret = avl.insert(*begin);
		  std::cout<< "insert: "<< *begin <<" "<< (ret ? "success" : "failed")<< std::endl;
	 }
	 avl.toPng("final AVL");
}
/**
 * AVL remove by merging 测试
 */
void testCase5() {
	int insertEle[] = {13,24,37,90,53,10,30,27,15,7,41,35};
	int removeEles[] = {10,15,37,35,24,30};
	 AVLTree avl;
	 BiTreePrinter::prefix = "AVL-removeByMerging";
	 avl.bwritePng = false;
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin)
		   avl.insert(*begin);
	 avl.bwritePng = true;
	 avl.toPng("initial AVL");
	 for (int * begin = removeEles;begin != removeEles+sizeof(removeEles) / sizeof(removeEles[0]) ;++begin) {
		 bool  ret = avl.findAndRemoveByMerging(*begin);
		 std::cout<< "delete: "<< *begin <<  (ret ? "success" : "failed")<< std::endl;
	 }
	 avl.toPng("final AVL");
}
/**
 * AVL  remove by copying测试
 */
void testCase6() {
	int insertEle[] = {13,24,37,90,53,10,30,27,15,7,41,35};
	int removeEles[] = {10,15,37,35,24,30};
	 AVLTree avl;
	 BiTreePrinter::prefix  = "AVL-removeByCopying";
	 avl.bwritePng = false;
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin)
		   avl.insert(*begin);
	 avl.bwritePng = true;
	 avl.toPng("initial AVL");
	 for (int * begin = removeEles;begin != removeEles+sizeof(removeEles) / sizeof(removeEles[0]) ;++begin) {
		 bool  ret = avl.findAndRemoveByCopying(*begin);
		 std::cout<< "delete: "<< *begin <<  (ret ? "success" : "failed")<< std::endl;
	 }
	avl.toPng("final AVL");
}
/**
 * SplayTree 测试
 */
void testCase7() {
	 int insertEle[] = {44,55,66,77,88,99};
	 int searchEle[] = {44,66,88};
	 int removeEle[] = {55,88};
	 SplayTree stree;
	 BiTreePrinter::prefix=std::string("SplayTree");
	 for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		 stree.insert(*begin);
	 }
	 for (int * begin = searchEle;begin != searchEle+sizeof(searchEle) / sizeof(searchEle[0]) ;++begin) {
	 		stree.search(*begin);
	  }
	 for (int * begin = removeEle;begin != removeEle+sizeof(removeEle) / sizeof(removeEle[0]) ;++begin) {
	 	 		stree.findAndRemoveByCopying(*begin);
	 }
	 stree.toPng("final SplayTree");
}
/**
 * 中序遍历速度测试
 */
void testCase8() {
	 std::vector<int> initVec;
	 const long nodeCount = 1000000;
	 std::cout << "preparing data" << std::endl;
	 getRandomNumber(initVec,0,nodeCount);
	 std::random_shuffle(initVec.begin(), initVec.end());
	 BST tree;
	 tree.bwritePng = false;
	 tree.bshowVisitInfo = false;	// 不显示访问节点信息
	 std::cout << "Inserting " << nodeCount << " nodes:"<<std::endl <<"[";
	 long count = 0;
	 for(std::vector<int>::iterator it = initVec.begin(); it != initVec.end();++it,++count) {
		 	 tree.insert(*it);
		 	 if(count % (nodeCount / 100) == 0)
		 		 std::cout << std::unitbuf << "#" << std::nounitbuf;
	 }
	 std::cout <<"]" << std::endl;
     uint64 curms = GetTimeMs64();
     const int times = 10;
     for(int i=0;i < times;i++) {
    	 tree.inorder();
     }
    uint64 passms = GetTimeMs64()-curms;
    std::cerr<<"递归中序遍历平均: "<<passms/times << " ms "<<std::endl;

     curms = GetTimeMs64();
	 for(int i=0;i < times;i++) {
		 tree.iterativeInorder();
	 }
	 passms = GetTimeMs64()-curms;
	 std::cerr<<"显式借助栈的中序遍历平均: "<<passms/times << " ms "<<std::endl;

	  curms = GetTimeMs64();
	  for(int i=0;i < times;i++) {
		 tree.MorrisInorder();
	  }
	  passms = GetTimeMs64()-curms;
	  std::cerr<<"Morris中序遍历平均: "<<passms/times << " ms "<<std::endl;
}
/**
 * 测试利用dot文件转换png图片程序
 */
void testCase9() {
	int insertEle[] = {23,14,28,10,19,26,30,8,12,15,22,25,27,29,32};
	BST bst;
	BiTreePrinter::prefix = std::string("bigBST");
	for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  bst.insert(*begin);
	}
	bst.toPng("final BST");
	std::cout << "done."<<std::endl;
}
/**
 * 遍历过程
 */
void testCase10() {
	int insertEle[] = {15,4,20,1,7,16,25};
	BST bst;
	bst.bwritePng = false;
	bst.bshowVisitInfo = false;
	BiTreePrinter::prefix = std::string("traverse");
	for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  bst.insert(*begin);
	}
	bst.bwritePng = true;
	bst.toPng("initial BST");

	BiTreePrinter::prefix = std::string("traverse-preorder");
	BiTreePrinter::fileCounter = 1;
	bst.toPng("BST pre-order traversing");
	bst.preorder();

	BiTreePrinter::prefix = std::string("traverse-inorder");
	BiTreePrinter::fileCounter = 1;
	bst.toPng("BST in-order traversing");
	bst.inorder();

	BiTreePrinter::prefix = std::string("traverse-postorder");
	BiTreePrinter::fileCounter = 1;
	bst.toPng("BST post-order traversing");
	bst.postorder();

	BiTreePrinter::prefix = std::string("traverse-breadthfirst");
	BiTreePrinter::fileCounter = 1;
	bst.toPng("BST breadth first traversing");
	bst.breadthFirst();
	std::cout << "\n\n";
}
/**
 * Morris中序遍历测试
 */
void testCase11() {
	int insertEle[] = {10,5,20,3,7};
	BST bst;
	bst.bwritePng = false;
	BiTreePrinter::prefix = std::string("traverse-Morris");
	for (int * begin = insertEle;begin != insertEle+sizeof(insertEle) / sizeof(insertEle[0]) ;++begin) {
		  bst.insert(*begin);
	}
	std::cout << "Morris in-order traversing" << std::endl;
	bst.MorrisInorder();
	std::cout<<std::endl;
}
/**
 * 读取输入数据建立BST
 */
void testCase12() {
	BST bst;
	int data = -1;
	bst.bwritePng = false;
	std::cout << "input data to create a Binary search tree"<<std::endl;
	std::cout << "please input integer data(Ctrl+D/Z to end):" << std::endl;
	while(std::cin >> data) {
		bst.insert(data);
	}
	std::cin.clear();
	std::cout << "input a string to describe the BST:"<<std::endl;
	std::string desp;
	std::getline (std::cin,desp);

	std::cin.clear();
	std::cout << "input a filename to save the BST:"<<std::endl;
	std::string filename;
	std::getline (std::cin,filename);
	BiTreePrinter::prefix = filename;

	std::cin.clear();
	std::cout << "input a picture number to order:"<<std::endl;
	int number;
	std::cin >> number;
	BiTreePrinter::fileCounter = number;


	bst.bwritePng = true;

	std::cout<<"Begin creating BST and transform it to picture..."<<std::endl;
	bst.toPng(desp);
	std::cout<<"Done" << std::endl;
}
void getRandomNumber(std::vector<int> &ivec,int start,int end) {
	for(int x = start; x<end; x++)
		ivec.push_back(x);
}
