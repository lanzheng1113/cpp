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

using namespace std;
int main() {
	string fileName;
	cout<<"input vertex matrix filename"<<endl;
	cin>>fileName;
	ifstream fileis(fileName.c_str());
	if(!fileis) {
		cerr<<"could not open stream: "<<fileName<<" for reading."<<endl;
		return 1;
	}
	int n;
	fileis >> n;
	Graph graph(n,fileis);//创建图
	//graph.printSPathDIJ();
    //std::cout<<std::endl;
    graph.printSPathFLOYD();
}



