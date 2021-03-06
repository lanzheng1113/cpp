/*
 * graph.h
 * 图  以邻接矩阵为存储结构的图操作
 * 使用 2d vector 还是2d array 没有统一认识 不在此深究
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */

#ifndef GRAPH_SRC_GRAPH_H_
#define GRAPH_SRC_GRAPH_H_

#include <istream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include "adjmatrix.h"
enum VertColor {WHITE,GRAY,BLACK};
//图
class Graph {
public:
	typedef std::vector<std::vector<int> > vector2i;
	typedef std::vector<std::vector<std::string> > vector2s;
public:
	Graph(std::istream &stream);
	void printSPathDijkstra();
	void printSPathDijkstra(int start);
	void printSPathFloyd();
	void DFSTraverse();
	void BFSTraverse();
	void printGraph();
	bool udgCycleDetect();
	bool dgCycleDetect();
	void printMiniSpanTreePrim();
	void printMiniSpanTreeKruskal();
	void printMiniSpanTreeDijkstra();
	void printArticulationPoint();
	void unionTest();
	bool topologicalSort();
	bool inverseTopologicalSort();
	bool criticalPath();
	~Graph();
private:
	void printCriticalPath(std::vector<int> &earliestTime,std::vector<int> &latestTime,int vertNo,std::vector<int> &verts);
	void printUnionData(std::vector<int> &root,std::vector<int> &next,std::vector<int> &length);
	void DFS(int vertNo,std::vector<bool> &visited);
	bool topoCriticalPath(std::vector<int> &earliestTime,std::stack<int> &invTopoStack);
	bool topoDFS(int vertNo,int &vcount,int &tcount,std::vector<int> &visited,std::vector<int> &topoNum);
    bool udgCycleDetectDFS(int vertNo,std::vector<int> &visited,int &count,std::vector<std::string> &edges);
    bool dgCycleDetectDFS(int vertNo,int &count,std::vector<int> &visited,std::vector<VertColor> &color);
    void articulationDFS(int vertNo,int &count,std::vector<int> &visitedNum,std::vector<int> &low);
    bool unionEdge(std::vector<int> &root,std::vector<int> &next,std::vector<int> &length,int u,int v);
    void  getCycleMaxEdge(std::vector<int> &root,std::vector<int> &next,std::vector<int> &length,Edge &edgeMax);
	void visit(int vertNo);
	void printPath(vector2i & disMatrix,vector2s &pathMatrix);
	void printMiniSpanningTree(std::list<Edge> &edges);
	void printDistance(vector2i& disMatrix,int i,int j);
	void shortestPathFloyd(vector2s &pathMatrix,vector2i &disMatrix);
	void shortestPathDijkstra(int start,std::vector<std::string> &path,std::vector<int> &distance) ;
private:
	int vertNum;
	std::vector<std::string> vertNames;
	GraphKind gkind;
	vector2i gMatrix;
	AdjMatrix adjMatrix;		// 使用邻接矩阵存储
};
#endif /* GRAPH_SRC_GRAPH_H_ */
