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
/**
 * 图的类别
 * 包括 有向图 有向网  无向图 无向网
 */
enum GraphKind {DG,DN,UDG,UDN};
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
	void printDistance(int i,int j);
	int getVertexNum() {
		return vertNum;
	}
	GraphKind getKind() {
		return gkind;
	}
	std::vector<std::string> & getVertexName() {
		return vertexNameVec;
	}
	int getUnavailable() {
		return unavailable;
	}
	int findAdjVertNo(int vertNo,int start=0);
private:
	void setGraphKind(std::string &kind);
private:
	std::vector<std::string> vertexNameVec;
	int vertNum;
	int **matrix;
	GraphKind gkind;
	int  unavailable;
};
#endif /* GRAPH_SRC_ADJMATRIX_H_ */
