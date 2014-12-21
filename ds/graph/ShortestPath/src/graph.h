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

//邻接矩阵
class GraphMatrix {
public:
	GraphMatrix(int verNum,std::istream &stream);
	~GraphMatrix();
	int ** getMatrix();
	void print();
public:
	static const int INF;
private:
	int vertexNum;
	int **matrix;
};
//图
class Graph {
public:
	Graph(int verNum,std::istream &stream):vertexNum(verNum),gMatrix(verNum,stream) {
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
	int vertexNum;
	std::string **pathMatrix;
	int **disMatrix;
	GraphMatrix gMatrix;		// 使用邻接矩阵存储
};


#endif /* GRAPH_H_ */
