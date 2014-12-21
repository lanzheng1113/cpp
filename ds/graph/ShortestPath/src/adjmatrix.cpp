/*
 * adjmatrix.cpp
 *
 *  Created on: 2014年12月21日
 *      Author: wangdq
 */
#include "adjmatrix.h"
#include <limits>
#include <sstream>
#include <iostream>

const int AdjMatrix::INF = std::numeric_limits<int>::max();
/**
 * 从流读入邻接矩阵数据
 * 例如:
 * -------------------------------------------
 *  3
 *  v0 v1 v2
 *	 0  4  11
 *  6  0  2
 *  3  inf  0
 * --------------------------------------------
 */
AdjMatrix::AdjMatrix(std::istream &stream) {
	   int verNum;
       stream>>verNum; // 读入顶点数目
       vertexNum = verNum;
       //创建顶点名称表
       std::string name;
       for(int i=0 ;i < vertexNum;++i) {
		   stream>>name;
		  vertexNameVec.push_back(name);
       }
       //创建邻接矩阵
       matrix = new int*[vertexNum];
       for(int i=0;i< vertexNum ;++i)
       		matrix[i] = new int[vertexNum];
       //初始化邻接矩阵
       	for(int i=0;i<vertexNum;++i)
       		for(int j=0;j<vertexNum;++j) {
       			 std::string val;
       			 stream>>val;
       			 if(val == "inf" || val == "INF")
       			    matrix[i][j] = INF;
       			 else {
       				std::istringstream ss(val);
       				ss >> matrix[i][j];
       			 }
       		}
}
void AdjMatrix::print() {
	for(int i=0;i<vertexNum;++i)
       		for(int j=0;j<vertexNum;++j)
       			if(matrix[i][j] != AdjMatrix::INF )
       				std::cout<<matrix[i][j]<<"\t";
       			else
       				std::cout<<"inf"<<"\t";
}
AdjMatrix::~AdjMatrix() {
	 for(int i=0;i< vertexNum ;++i)
		  delete [] matrix[i];
}
int ** AdjMatrix::getMatrix() {
    return matrix;
}


