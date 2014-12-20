/*
 * spath.cpp
 *  图的最短路径问题
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */
#include <iostream>
#include "graph.h"

using namespace std;
int main() {
	int n;
	cout<<"input vertex num"<<endl;
	cin>>n;
	//创建图
	std::cout<<"input graph data,use 'inf' to represent infinite"<<std::endl;
	Graph graph(n,std::cin);
    graph.printShortestPath(1);
}



