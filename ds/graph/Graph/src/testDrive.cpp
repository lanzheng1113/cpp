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
void testCase4(std::istream &istream);
void testCase5(std::istream &istream);
void testCase6(std::istream &istream);
void testCase7(std::istream &istream);
void testCase8(std::istream &istream);
void testCase9(std::istream &istream);

int main() {
	string fileName;
	cout<<"input filename:"<<endl;
	cin>>fileName;
	ifstream fileis(fileName.c_str());
	if(!fileis) {
		cerr<<"could not open stream: "<<fileName<<" for reading."<<endl;
		return 1;
	}
	testCase9(fileis);
	return 0;
}
//测试最短路径
void testCase0(std::istream &istream) {
	Graph graph(istream);//创建图
	graph.printSPathFloyd();
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
//测试邻接多重表
void testCase3(std::istream &istream) {
	 AdjMulist list(istream);
	 std::cout<<"Adjacency Multilist:"<<std::endl;
	 list.print();
	 int vertNo = 2;
	 std::cout<<"edge has vert: "<<list.getVertNames()[vertNo]<<std::endl;
	 list.printEdge(vertNo);
}
//测试图的遍历
void testCase4(std::istream &istream) {
	Graph graph(istream);//创建图
	std::cout<<"Depth First Search: \t";
	graph.DFSTraverse();
	std::cout<<"Breadth First Search: \t";
	graph.BFSTraverse();
}
//测试无向图中环检测
void testCase5(std::istream &istream) {
	Graph graph(istream);//创建图
	std::cout<<"is there cycle ?: \t";
	bool ret = graph.udgCycleDetect();
	if(!ret) std::cout<<"no!"<<std::endl;
}
//测试有向图中环检测
void testCase6(std::istream &istream) {
	Graph graph(istream);//创建图
	std::cout<<"is there cycle ?: \t";
	bool ret = graph.dgCycleDetect();
	if(!ret) std::cout<<"no!"<<std::endl;
}
//测试连通图中的关节点
void testCase7(std::istream &istream) {
	Graph graph(istream);//创建图
	graph.printArticulationPoint();
}
//测试最小生成树
void testCase8(std::istream &istream) {
	Graph graph(istream);//创建图
	std::cout<<"Prim mini spanning tree:"<<std::endl;
	graph.printMiniSpanTreePrim();
	std::cout<<"kruskal mini spanning tree:"<<std::endl;
	graph.printMiniSpanTreeKruskal();
	std::cout<<"Dijkstra mini spanning tree:"<<std::endl;
	graph.printMiniSpanTreeDijkstra();
}
//拓扑排序和逆拓扑排序
void testCase9(std::istream &istream) {
	Graph graph(istream);//创建图
	std::cout<<"Topological sort: "<<std::endl;
	bool ret = graph.topologicalSort();
	if(!ret)  std::cout<<"cycle detected!"<<std::endl;
	std::cout<<"Inverse Topological sort:"<<std::endl;
	ret = graph.inverseTopologicalSort();
	if(!ret) std::cout<<"cycle detected!"<<std::endl;
}
