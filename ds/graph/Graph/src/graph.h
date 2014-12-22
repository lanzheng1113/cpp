/*
 * graph.h
 * 图  以邻接矩阵为存储结构的图操作
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */

#ifndef GRAPH_SRC_GRAPH_H_
#define GRAPH_SRC_GRAPH_H_

#include <istream>
#include <string>
#include "adjmatrix.h"

//图
class Graph {
public:
	Graph(std::istream &stream):adjMatrix(stream) {
		vertNum = adjMatrix.getVertexNum();
		vertNames = adjMatrix.getVertexName();
		pathMatrix = 0;
		disMatrix = 0;
		gkind = adjMatrix.getKind();
	}
	void printSPathDIJ();
	void printSPathDIJ(int start);
	void printSPathFLOYD();
	void DFSTraverse();
	void BFSTraverse();
	void printGraph();
	~Graph();
private:
	void DFS(int vertNo,int** gMatrix,bool* visited);
	void prepareMatrix();
	void visit(int vertNo);
	void printPath();
	void printDistance(int **disMatrix,int i,int j);
	void shortestPathFLOYD(int** gMatrix,std::string **pathMatrix,int **disMatrix);
	void shortestPathDIJ(int start,int** gMatrix,std::string *path,int *distance) ;
private:
	int vertNum;
	std::string **pathMatrix;
	int **disMatrix;
	std::vector<std::string> vertNames;
	GraphKind gkind;
	AdjMatrix adjMatrix;		// 使用邻接矩阵存储
};


#endif /* GRAPH_SRC_GRAPH_H_ */
