/*
 * graph.cpp
 *
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */
#include "graph.h"
#include <iostream>
#include <sstream>
#include <limits>

const int GraphMatrix::INF = std::numeric_limits<int>::max();

GraphMatrix::GraphMatrix(int verNum,std::istream &stream) {
       vertexNum = verNum;
       //创建邻接矩阵
       matrix = new int*[verNum];
       for(int i=0;i< verNum ;++i)
       		matrix[i] = new int[verNum];
       //初始化邻接矩阵
       	for(int i=0;i<verNum;++i)
       		for(int j=0;j<verNum;++j) {
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
GraphMatrix::~GraphMatrix() {
	 for(int i=0;i< vertexNum ;++i)
		  delete [] matrix[i];
}
int ** GraphMatrix::getMatrix() {
    return matrix;
}
void Graph::printShortestPath(int start) {
	std::vector<int> distance(vertexNum,0);
	std::vector<std::string> paths(vertexNum,"");
	shotestPathDij(start,gMatrix.getMatrix(),paths,distance);
    for(int i=0;i < vertexNum;++i) {
    	  if(i == start) continue;
    	  std::cout<<"distance "<<start<<" to "<<i<<" : ";
    	  if(distance[i] != GraphMatrix::INF ) {
    		  std::cout<<distance[i]<<std::endl;
    		  std::cout<<"path: "<<paths[i]<<std::endl;
    	  }
    	  else {
    		  std::cout<<"inf"<<std::endl;
    	  }
    }
}
/**
 * 最短路径Dijkstra算法
 *
 * 输入邻接矩阵gMatrix表示图
 * 输入start表示起点序号
 *
 * 输出paths  表示最短路径
 * 输出distance   表示最短路径的距离
 */
void Graph::shotestPathDij(int start,int** gMatrix,std::vector<std::string> &paths,std::vector<int> &distance) {
	    bool final[vertexNum];
        //初始化到达每个点的最短路径和距离
	   for(int i=0;i<vertexNum;++i) {
		      final[i] = false;	// 表示非终结点
		      distance[i] = gMatrix[start][i];
		      //如果从start可到达i则标记路径
		      if(distance[i] < GraphMatrix::INF) {
		    	   std::ostringstream s;
		    	   s<<start<<"-"<<i;
		    	   paths[i] = s.str();
		      }
	   }
	   distance[start] = 0;
	   final[start] = true;
	   //n-1次迭代求出依次求出最短路径
      for(int i=0;i<vertexNum;++i) {
    	    int minDis=GraphMatrix::INF,min=-1;
    	    //选取距离最小者
           for(int j=0;j < vertexNum;++j) {
        	    if(final[j]) continue;
        	    if(distance[j] < minDis) {
        	    	minDis = distance[j];
        	    	min = j;
        	    }
           }
           if(min == -1)
        	    break;  // 剩下的点均不可到达则退出
            final[min] = true;
           //更新剩余的顶点的最短距离
           for(int i=0;i < vertexNum;++i) {
        	   if(final[i]  ||  gMatrix[min][i] == GraphMatrix::INF ) continue;
        	   if(minDis+gMatrix[min][i] < distance[i])  {
        		     distance[i] = minDis+gMatrix[min][i]; // 更新最短路径距离
        		     // 标记路径为从start-min-i
        		     std::ostringstream s;
        		     s<<paths[min]<<"-"<<i;
        		     paths[i] = s.str();
        	   }
           }
      }
}

