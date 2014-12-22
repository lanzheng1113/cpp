/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月22日
 *      Author: wangdq
 */

#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "adjlist.h"
#include "orthlist.h"
#include "adjmulist.h"

using namespace std;
void testCase0(std::istream &istream);
void testCase1(std::istream &istream);
void testCase2(std::istream &istream);
void testCase3(std::istream &istream);

int main() {
	string fileName;
	cout<<"input filename:"<<endl;
	cin>>fileName;
	ifstream fileis(fileName.c_str());
	if(!fileis) {
		cerr<<"could not open stream: "<<fileName<<" for reading."<<endl;
		return 1;
	}
	testCase3(fileis);
	return 0;
}
void testCase0(std::istream &istream) {
	Graph graph(istream);//创建图
	graph.printSPathFLOYD();
}
//测试邻接表
void testCase1(std::istream &istream) {
	AdjList gList(istream);
	std::cout<<"Adjacent List:"<<std::endl;
    gList.print();
    AdjList list;
    gList.getInvAdjList(list);
    std::cout<<"Inverse Adjacent List:"<<std::endl;
    list.print();
}
//测试十字链表
void testCase2(std::istream &istream)  {
     OrthList orthList(istream);
     std::cout<<"Orthogonal List:"<<std::endl;
     orthList.print();
     int vertNo = 0;
     std::cout<<"arc head as: "<<orthList.getVertNames()[vertNo]<<std::endl;
     orthList.printVertIn(vertNo);
     std::cout<<"arc tail as: "<<orthList.getVertNames()[vertNo]<<std::endl;
     orthList.printVertOut(vertNo);
}
void testCase3(std::istream &istream) {
	 AdjMulist list(istream);
	 std::cout<<"Adjacency Multilist:"<<std::endl;
	 list.print();
	 int vertNo = 2;
	 std::cout<<"edge has vert: "<<list.getVertNames()[vertNo]<<std::endl;
	 list.printEdge(vertNo);
}


