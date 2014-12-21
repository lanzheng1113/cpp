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
#include "adjmatrix.h"

//图
class Graph {
public:
	Graph(std::istream &stream):adjMatrix(stream) {
		vertNum = adjMatrix.getVertexNum();
		vertNames = adjMatrix.getVertexName();
		pathMatrix = 0;
		disMatrix = 0;
	}
	void printSPathDIJ();
	void printSPathDIJ(int start);
	void printSPathFLOYD();
	~Graph();
private:
	void prepareMatrix();
	void printPath();
	void shortestPathFLOYD(int** gMatrix,std::string **pathMatrix,int **disMatrix);
	void shortestPathDIJ(int start,int** gMatrix,std::string *path,int *distance) ;
private:
	int vertNum;
	std::string **pathMatrix;
	int **disMatrix;
	std::vector<std::string> vertNames;
	AdjMatrix adjMatrix;		// 使用邻接矩阵存储
};


#endif /* GRAPH_H_ */
