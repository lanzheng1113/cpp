/*
 * adjmatrix.cpp
 *
 *  Created on: 2014年12月21日
 *      Author: wangdq
 */

#include <limits>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "adjmatrix.h"

#include "common.h"
/**
 * 从流读入邻接矩阵数据
 * 例如:
 * -------------------------------------------
 *  DN 3   (带权图  顶点数目)
 *  v0 v1 v2  (顶点名称)
 *	 0  4  11 (边0-4 权值为11)
 *  6  0  2
 * --------------------------------------------
 */
AdjMatrix::AdjMatrix(std::istream &stream) {
	   Util::skipStreamComment(stream); // 跳过注释
	   std::string kind;
	   stream >> kind;
	   setGraphKind(kind); // 设置图的类型
       stream>>vertNum; // 读入顶点数目
       //创建顶点名称表
       std::string name;
       matrix.resize(vertNum); // 动态调整向量大小
       for(int i=0 ;i < vertNum;++i) {
		   stream>>name;
		   vertNamesVec.push_back(name);
		   matrix[i].resize(vertNum,unavailable); // 默认顶点间不可到达
       }
       std::string src,dest;
       int srcNo,destNo,edge;
       while(stream >> src >> dest >> edge) {
    	   std::vector<std::string>::iterator iter = std::find(vertNamesVec.begin(),vertNamesVec.end(),src);
    	   srcNo = iter-vertNamesVec.begin();
    	   iter = std::find(vertNamesVec.begin(),vertNamesVec.end(),dest);
    	   destNo =iter-vertNamesVec.begin();
    	   matrix[srcNo][destNo] = edge;
    	   if(gkind == UDG || gkind == UDN)
    		   matrix[destNo][srcNo] = edge;  // 无向图中边保证i-j j-i相同
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

/**
 * 列出所有边
 */
void AdjMatrix::listAllEdges(std::vector<Edge>&edges) {
	for(int i=0;i<vertNum;++i)
				for(int j=0;j<vertNum;++j) {
					   if((gkind == UDG || gkind == UDN) && i > j )  // 对称的图只列出上三角形部分即可
						   	   	   continue;
					   if(matrix[i][j] != unavailable)
						   edges.push_back(Edge(i,j,matrix[i][j]));
				}
}
/**
 * 顶点i与j是否相连
 */
bool AdjMatrix::isAdj(int i,int j) {
	return matrix[i][j] != unavailable;
}
/**
 * 获取顶点的入度
 */
void AdjMatrix::getIndegrees(std::vector<int>  &indegrees) {
	  // 按列遍历
	  for(int i=0;i < vertNum;++i)
		  for(int j = 0;j < vertNum;++j)
			       if(matrix[j][i] != unavailable)
			    	   	   indegrees[i]++;
}
