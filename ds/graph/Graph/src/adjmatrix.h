/*
 * adjmatrix.h
 *
 *  Created on: 2014年12月21日
 *      Author: wangdq
 */

#ifndef GRAPH_SRC_ADJMATRIX_H_
#define GRAPH_SRC_ADJMATRIX_H_

#include <istream>
#include <string>
#include <vector>

/***
 * 邻接矩阵
 * 图的数组存储方式
 */
class AdjMatrix {
public:
	AdjMatrix(std::istream &stream);
	~AdjMatrix();
	int ** getMatrix();
	void print();
	int getVertexNum() {
		return vertexNum;
	}
	std::vector<std::string> & getVertexName() {
		return vertexNameVec;
	}
public:
	static const int INF;
private:
	std::vector<std::string> vertexNameVec;
	int vertexNum;
	int **matrix;
};
#endif /* GRAPH_SRC_ADJMATRIX_H_ */
