/*
 * spath.cpp
 *  图的最短路径问题
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */
#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "adjlist.h"

using namespace std;
void testCase0(std::istream &istream);
void testCase1(std::istream &istream);
int main() {
	string fileName;
	cout<<"input filename:"<<endl;
	cin>>fileName;
	ifstream fileis(fileName.c_str());
	if(!fileis) {
		cerr<<"could not open stream: "<<fileName<<" for reading."<<endl;
		return 1;
	}
	testCase1(fileis);
	return 0;
}
void testCase0(std::istream &istream) {
	Graph graph(istream);//创建图
	graph.printSPathFLOYD();
}
void testCase1(std::istream &istream) {
	AdjList gList(istream);
	std::cout<<"Adjacent List:"<<std::endl;
    gList.print();
    AdjList list;
    gList.getInvAdjList(list);
    std::cout<<"Inverse Adjacent List:"<<std::endl;
    list.print();
}

