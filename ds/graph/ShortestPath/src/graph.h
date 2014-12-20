/*
 * graph.h
 *
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <istream>
#include <string>
#include <vector>

//邻接矩阵
class GraphMatrix {
public:
	GraphMatrix(int verNum,std::istream &stream);
	~GraphMatrix();
	int ** getMatrix();
public:
	static const int INF;
private:
	int vertexNum;
	int **matrix;
};
//图
class Graph {
public:
	Graph(int verNum,std::istream &stream):vertexNum(verNum),gMatrix(verNum,stream) {}
	void printShortestPath(int start);
    void shotestPathDij(int start,int** gMatrix,std::vector<std::string> &paths,std::vector<int> &distance) ;
	~Graph() {}
private:
	int vertexNum;
	GraphMatrix gMatrix;		// 使用邻接矩阵存储
};


#endif /* GRAPH_H_ */
