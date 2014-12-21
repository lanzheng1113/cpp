/*
 * graph.cpp
 *
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */
#include "graph.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void Graph::prepareMatrix() {
    if(disMatrix == 0) {
    	disMatrix = new int*[vertNum];
    	    for(int i=0;i< vertNum ;++i)
    	    	   disMatrix[i] = new int[vertNum];
    }
    if(pathMatrix == 0) {
    	pathMatrix = new std::string*[vertNum];
    	    for(int i=0;i< vertNum ;++i)
    	    	   pathMatrix[i] = new std::string[vertNum];
    }
}
Graph::~Graph() {
	if(disMatrix != 0) {
		 for(int i=0;i< vertNum ;++i)
		    	delete[] disMatrix[i];
	}
	if(pathMatrix != 0) {
		 for(int i=0;i< vertNum ;++i)
			 delete[] disMatrix[i];
	}
}
/**
 * Dijkstra 求每一对定点间最短路径
 */
void Graph::printSPathDIJ() {
	prepareMatrix();
	// 调用Dijkstra算法n次
	for(int i=0;i < vertNum;++i)
		shortestPathDIJ(i,adjMatrix.getMatrix(),pathMatrix[i],disMatrix[i]);
	printPath();
}
/**
 *  Dijkstra 打印start到其余顶点的最短路径
 */
void Graph::printSPathDIJ(int start) {
	prepareMatrix();
    shortestPathDIJ(start,adjMatrix.getMatrix(),pathMatrix[start],disMatrix[start]);
    std::cout<<"shortest distance"<<start<<"to others"<<std::endl;
    for(int i=0;i < vertNum;++i) {
        	  if(disMatrix[start][i] != AdjMatrix::INF )
        		  std::cout<<disMatrix[start][i]<<"\t";
        	  else
        		  std::cout<<"inf"<<"\t";
     }
    std::cout<<std::endl<<"shortest path: "<<std::endl;
    for(int i=0;i < vertNum;++i) {
    	 std::cout.width(2*vertNum);
    	 std::cout<<std::left<<pathMatrix[start][i]<<"\t";
    }
    std::cout<<std::endl;
}
void Graph::printPath() {
	std::cout<<"shortest distance:"<<std::endl;
	for(int i=0;i < vertNum;++i) {
		for(int j = 0;j < vertNum;++j) {
			if(disMatrix[i][j] != AdjMatrix::INF )
				std::cout<<disMatrix[i][j]<<"\t";
			else
				std::cout<<"inf"<<"\t";
		}
		std::cout<<std::endl;
	}
	std::cout<<"shortest paths:"<<std::endl;
	for(int i=0;i < vertNum;++i) {
		for(int j = 0;j < vertNum;++j) {
			    std::cout.width(3*vertNum);
			    if(pathMatrix[i][j].empty())
			    	std::cout<< std::left<<"not"<<"\t";
			    else
			    	std::cout<< std::left<<pathMatrix[i][j]<<"\t";
		}
		std::cout<<std::endl;
	}
}
void Graph::printSPathFLOYD() {
	prepareMatrix();
	shortestPathFLOYD(adjMatrix.getMatrix(),pathMatrix,disMatrix);
	printPath();
}
/**
 * Floyd算法  求每一对定点间最短路径
 * 输入gMatrix表示图的邻接矩阵
 *
 * 输出pathMatrix表示最短路径矩阵
 * 输出disMatrix表示最短路径距离
 */
void Graph::shortestPathFLOYD(int** gMatrix,std::string **pathMatrix,int **disMatrix) {
	//初始化距离矩阵和路径矩阵
	for(int i=0;i < vertNum;++i)
		for(int j=0;j < vertNum;++j) {
			    disMatrix[i][j] = gMatrix[i][j];
			    pathMatrix[i][j] = "";
			    if(disMatrix[i][j] != AdjMatrix::INF)
			    	  pathMatrix[i][j] = vertNames[i]+"-"+vertNames[j];	// 初始路径 i-j
		}
   //迭代计算最短路径
	for(int k=0;k < vertNum;++k)  {
		for(int i=0;i < vertNum;++i)
						for(int j=0;j < vertNum;++j) {
							if(disMatrix[i][k] == AdjMatrix::INF
									|| disMatrix[k][j]  == AdjMatrix::INF)
								continue;
							if(disMatrix[i][k]+disMatrix[k][j] < disMatrix[i][j]) {	// K为中间顶点
								disMatrix[i][j] = disMatrix[i][k]+disMatrix[k][j]; // 更新路径距离
								std::string tmp = pathMatrix[i][k].substr(0,
										pathMatrix[i][k].find_last_of("-")+1);
								pathMatrix[i][j] = tmp+pathMatrix[k][j]; // 更新路径 i-k-j
							}
						}
		/*
		std::cout<<k<<": shortest distance:"<<std::endl;
		for(int m=0;m < vertexNum;++m) {
				for(int n = 0;n < vertexNum;++n) {
					if(disMatrix[m][n] != GraphMatrix::INF )
						std::cout<<disMatrix[m][n]<<"\t";
					else
						std::cout<<"inf"<<"\t";
				}
				std::cout<<std::endl;
			}*/
	}
}
/**
 * 最短路径Dijkstra算法
 *
 * 输入邻接矩阵gMatrix表示图
 * 输入start表示起点序号
 *
 * 输出paths  表示最短路径
 * 输出distance   表示最短路径距离
 */
void Graph::shortestPathDIJ(int start,int** gMatrix,std::string *path,int *distance) {
	    bool final[vertNum];
        //初始化到达每个点的最短路径和距离
	   for(int i=0;i<vertNum;++i) {
		      final[i] = false;	// 表示非终结点
		      distance[i] = gMatrix[start][i];
		      path[i] = "";	// 标记为无路径
		      //如果从start可到达i则标记路径
		      if(distance[i] < AdjMatrix::INF)
		    	   path[i] = vertNames[start]+"-"+vertNames[i];
	   }
	   distance[start] = 0;
	   final[start] = true;
	   //n-1次迭代求出依次求出最短路径
      for(int i=0;i<vertNum;++i) {
    	    int minDis=AdjMatrix::INF,min=-1;
    	    //选取距离最小者
           for(int j=0;j < vertNum;++j) {
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
           for(int i=0;i < vertNum;++i) {
        	   if(final[i]  ||  gMatrix[min][i] == AdjMatrix::INF ) continue;
        	   if(minDis+gMatrix[min][i] < distance[i])  {
        		     distance[i] = minDis+gMatrix[min][i]; // 更新最短路径距离
        		     // 标记路径为从start-min-i
        		     path[i] = path[min]+"-"+vertNames[i];
        	   }
           }
      }
}

