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
#include <algorithm>

/**
 * 从流读入邻接矩阵数据
 * 例如:
 * -------------------------------------------
 *  1 3   (带权图  顶点数目)
 *  v0 v1 v2  (顶点名称)
 *	 0  4  11
 *  6  0  2
 *  3  inf  0
 * --------------------------------------------
 */
AdjMatrix::AdjMatrix(std::istream &stream) {
	   std::string kind;
	   stream >> kind;
	   setGraphKind(kind); // 设置图的类型
       stream>>vertNum; // 读入顶点数目
       //创建顶点名称表
       std::string name;
       for(int i=0 ;i < vertNum;++i) {
		   stream>>name;
		   vertexNameVec.push_back(name);
       }
       //创建邻接矩阵
       matrix = new int*[vertNum];
       for(int i=0;i< vertNum ;++i)
       		matrix[i] = new int[vertNum];
       //初始化邻接矩阵
       	for(int i=0;i<vertNum;++i)
       		for(int j=0;j<vertNum;++j) {
       			 std::string val;
       			 stream>>val;
       			 if( (gkind == DN || gkind == UDN ) && (val == "inf" || val == "INF"))
       				 	 matrix[i][j] = unavailable;
       			 else {
       				 	 std::istringstream ss(val);
       				 	 ss >> matrix[i][j];
       			 }
       		}
}
void AdjMatrix::setGraphKind(std::string &kind) {
	  std::transform(kind.begin(), kind.end(),kind.begin(), ::toupper);
	  if (kind == "DG")
		  gkind = DG;
	  else if(kind == "UDG")
		  gkind = UDG;
	  else if(kind == "DN")
		  gkind = DN;
	  else
		  gkind = UDN;
	   if(gkind == DG || gkind == UDG)  {
		   unavailable = 0 ; // 有向图和无向图中不可达用表示为0
	   }else {
		   unavailable = std::numeric_limits<int>::max(); // 网中不可达表示为infinite
	   }
}
void AdjMatrix::print() {
	for(int i=0;i<vertNum;++i) {
		for(int j=0;j<vertNum;++j)
		       			printDistance(i,j);
		std::cout<<std::endl;
	}
}
void AdjMatrix::printDistance(int i,int j) {
	if( (gkind == DN || gkind == UDN ) && matrix[i][j] == unavailable )
	       	std::cout<<"inf"<<"\t";
	else
		    std::cout<<matrix[i][j]<<"\t";
}
AdjMatrix::~AdjMatrix() {
	 for(int i=0;i< vertNum ;++i)
		  delete [] matrix[i];
}
/**
 * 获取顶点vertNo的从start开始计算的第一个相邻顶点
 * 默认获取第一个相邻的顶点
 * 如果找到则返回顶点索引 否则返回-1
 */
int  AdjMatrix::findAdjVertNo(int vertNo,int start) {
	  int i=start;
	  for(;i < vertNum;++i) {
		  if(i == vertNo || matrix[vertNo][i] == unavailable)
			  continue;
		  else
			  break;
	  }
	  if(i < vertNum)
		  return i;
	  else
		  return -1;
}
int ** AdjMatrix::getMatrix() {
    return matrix;
}


