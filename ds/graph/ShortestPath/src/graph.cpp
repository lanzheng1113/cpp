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
void GraphMatrix::print() {
	for(int i=0;i<vertexNum;++i)
       		for(int j=0;j<vertexNum;++j)
       			if(matrix[i][j] != GraphMatrix::INF )
       				std::cout<<matrix[i][j]<<"\t";
       			else
       				std::cout<<"inf"<<"\t";
}
GraphMatrix::~GraphMatrix() {
	 for(int i=0;i< vertexNum ;++i)
		  delete [] matrix[i];
}
int ** GraphMatrix::getMatrix() {
    return matrix;
}
void Graph::prepareMatrix() {
    if(disMatrix == 0) {
    	disMatrix = new int*[vertexNum];
    	    for(int i=0;i< vertexNum ;++i)
    	    	   disMatrix[i] = new int[vertexNum];
    }
    if(pathMatrix == 0) {
    	pathMatrix = new std::string*[vertexNum];
    	    for(int i=0;i< vertexNum ;++i)
    	    	   pathMatrix[i] = new std::string[vertexNum];
    }
}
Graph::~Graph() {
	if(disMatrix != 0) {
		 for(int i=0;i< vertexNum ;++i)
		    	delete[] disMatrix[i];
	}
	if(pathMatrix != 0) {
		 for(int i=0;i< vertexNum ;++i)
			 delete[] disMatrix[i];
	}
}
/**
 * Dijkstra 求每一对定点间最短路径
 */
void Graph::printSPathDIJ() {
	prepareMatrix();
	// 调用Dijkstra算法n次
	for(int i=0;i < vertexNum;++i)
		shortestPathDIJ(i,gMatrix.getMatrix(),pathMatrix[i],disMatrix[i]);
	printPath();
}
/**
 *  Dijkstra 打印start到其余顶点的最短路径
 */
void Graph::printSPathDIJ(int start) {
	prepareMatrix();
    shortestPathDIJ(start,gMatrix.getMatrix(),pathMatrix[start],disMatrix[start]);
    std::cout<<"shortest distance"<<start<<"to others"<<std::endl;
    for(int i=0;i < vertexNum;++i) {
        	  if(disMatrix[start][i] != GraphMatrix::INF )
        		  std::cout<<disMatrix[start][i]<<"\t";
        	  else
        		  std::cout<<"inf"<<"\t";
     }
    std::cout<<std::endl<<"shortest path: "<<std::endl;
    for(int i=0;i < vertexNum;++i) {
    	 std::cout.width(2*vertexNum);
    	 std::cout<<std::left<<pathMatrix[start][i]<<"\t";
    }
    std::cout<<std::endl;
}
void Graph::printPath() {
	std::cout<<"shortest distance:"<<std::endl;
	for(int i=0;i < vertexNum;++i) {
		for(int j = 0;j < vertexNum;++j) {
			if(disMatrix[i][j] != GraphMatrix::INF )
				std::cout<<disMatrix[i][j]<<"\t";
			else
				std::cout<<"inf"<<"\t";
		}
		std::cout<<std::endl;
	}
	std::cout<<"shortest paths:"<<std::endl;
	for(int i=0;i < vertexNum;++i) {
		for(int j = 0;j < vertexNum;++j) {
			   std::cout.width(2*vertexNum);
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
	shortestPathFLOYD(gMatrix.getMatrix(),pathMatrix,disMatrix);
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
	for(int i=0;i < vertexNum;++i)
		for(int j=0;j < vertexNum;++j) {
			    disMatrix[i][j] = gMatrix[i][j];
			    pathMatrix[i][j] = "";
			    if(disMatrix[i][j] != GraphMatrix::INF) {
			    	  std::ostringstream s;
			    	  s<<i<<"-"<<j;
			    	  pathMatrix[i][j] = s.str();	// 初始路径 i-j
			    }
		}
   //迭代计算最短路径
	for(int k=0;k < vertexNum;++k)  {
		for(int i=0;i < vertexNum;++i)
						for(int j=0;j < vertexNum;++j) {
							if(disMatrix[i][k] == GraphMatrix::INF
									|| disMatrix[k][j]  == GraphMatrix::INF)
								continue;
							if(disMatrix[i][k]+disMatrix[k][j] < disMatrix[i][j]) {	// K为中间顶点
								disMatrix[i][j] = disMatrix[i][k]+disMatrix[k][j]; // 更新路径距离
								pathMatrix[i][j] = pathMatrix[i][k].substr(0,
										pathMatrix[i][k].length()-1)+pathMatrix[k][j]; // 更新路径 i-k-j
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
	    bool final[vertexNum];
        //初始化到达每个点的最短路径和距离
	   for(int i=0;i<vertexNum;++i) {
		      final[i] = false;	// 表示非终结点
		      distance[i] = gMatrix[start][i];
		      path[i] = "";	// 标记为无路径
		      //如果从start可到达i则标记路径
		      if(distance[i] < GraphMatrix::INF) {
		    	   std::ostringstream s;
		    	   s<<start<<"-"<<i;
		    	   path[i] = s.str();
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
        		     s<<path[min]<<"-"<<i;
        		     path[i] = s.str();
        	   }
           }
      }
}

