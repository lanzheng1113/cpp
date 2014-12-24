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
#include "common.h"
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
	typedef std::vector<std::vector<int> > vector2i;
	typedef std::vector<std::vector<std::string> > vector2s;
public:
	AdjMatrix(std::istream &stream);
	~AdjMatrix();
	void print();
	vector2i& getMatrix() {
		return matrix;
	}
	void printDistance(int i,int j);
	int getVertexNum() {
		return vertNum;
	}
	GraphKind getKind() {
		return gkind;
	}
	std::vector<std::string> & getVertexName() {
		return vertNamesVec;
	}
	int getUnavailable() {
		return unavailable;
	}
	int findAdjVertNo(int vertNo,int start=0);
	void listAllEdges(std::vector<Edge>&edges);
private:
	void setGraphKind(std::string &kind);
private:
	std::vector<std::string> vertNamesVec;
	int vertNum;
	vector2i matrix;
	GraphKind gkind;
	int  unavailable;
};
#endif /* GRAPH_SRC_ADJMATRIX_H_ */
