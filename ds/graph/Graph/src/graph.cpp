/*
 * graph.cpp
 *
 *  Created on: 2014年12月20日
 *      Author: wangdq
 */
#include "graph.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <queue>
Graph::Graph(std::istream &stream):adjMatrix(stream) {
	vertNum = adjMatrix.getVertexNum();
	vertNames = adjMatrix.getVertexName();
	gMatrix = adjMatrix.getMatrix();
	gkind = adjMatrix.getKind();
}
Graph::~Graph() {

}
/**
 * Dijkstra 求每一对定点间最短路径
 */
void Graph::printSPathDijkstra() {
	vector2s pathMatrix(vertNum,std::vector<std::string>(vertNum));
	vector2i disMatrix(vertNum,std::vector<int>(vertNum));
	// 调用Dijkstra算法n次
	for(int i=0;i < vertNum;++i)
		shortestPathDijkstra(i,pathMatrix[i],disMatrix[i]);
	printPath(disMatrix,pathMatrix);
}
/**
 *  Dijkstra 打印start到其余顶点的最短路径
 */
void Graph::printSPathDijkstra(int start) {
	vector2s pathMatrix(vertNum,std::vector<std::string>(vertNum));
	vector2i disMatrix(vertNum,std::vector<int>(vertNum));
    shortestPathDijkstra(start,pathMatrix[start],disMatrix[start]);
    std::cout<<"shortest distance"<<start<<"to others"<<std::endl;
    for(int i=0;i < vertNum;++i)
    	  printDistance(disMatrix,start,i);
    std::cout<<std::endl<<"shortest path: "<<std::endl;
    for(int i=0;i < vertNum;++i) {
    	 std::cout.width(2*vertNum);
    	 std::cout<<std::left<<pathMatrix[start][i]<<"\t";
    }
    std::cout<<std::endl;
}
void Graph::printPath(vector2i & disMatrix,vector2s &pathMatrix) {
	std::cout<<"shortest distance:"<<std::endl;
	for(int i=0;i < vertNum;++i) {
		for(int j = 0;j < vertNum;++j)
			printDistance(disMatrix,i,j);
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
void Graph::printSPathFloyd() {
	vector2s pathMatrix(vertNum,std::vector<std::string>(vertNum));
	vector2i disMatrix(vertNum,std::vector<int>(vertNum));
	shortestPathFloyd(pathMatrix,disMatrix);
	printPath(disMatrix,pathMatrix);
}
/**
 * 打印图的邻接矩阵
 */
void  Graph::printGraph() {
	adjMatrix.print();
}
/**
 * 打印距离矩阵中i,j距离
 */
void Graph::printDistance(vector2i& disMatrix,int i,int j) {
	 if( (gkind ==DN || gkind == UDN) &&
			 disMatrix[i][j]== adjMatrix.getUnavailable() )
		  std::cout<<"inf"<<"\t";
	else
		 std::cout<<disMatrix[i][j]<<"\t";
}
/**
 * Floyd算法  求每一对定点间最短路径
 * 输入gMatrix表示图的邻接矩阵
 *
 * 输出pathMatrix表示最短路径矩阵
 * 输出disMatrix表示最短路径距离
 */
void Graph::shortestPathFloyd(vector2s &pathMatrix,vector2i &disMatrix) {
	//初始化距离矩阵和路径矩阵
	for(int i=0;i < vertNum;++i)
		for(int j=0;j < vertNum;++j) {
			    disMatrix[i][j] = gMatrix[i][j];
			    pathMatrix[i][j] = "";
			    if(disMatrix[i][j] != adjMatrix.getUnavailable())
			    	  pathMatrix[i][j] = vertNames[i]+"-"+vertNames[j];	// 初始路径 i-j
		}
   //迭代计算最短路径
	for(int k=0;k < vertNum;++k)  {
		for(int i=0;i < vertNum;++i)
						for(int j=0;j < vertNum;++j) {
							if(disMatrix[i][k] == adjMatrix.getUnavailable()
									|| disMatrix[k][j]  == adjMatrix.getUnavailable())
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
void Graph::shortestPathDijkstra(int start,std::vector<std::string> &path,std::vector<int> &distance) {
	    bool final[vertNum];
        //初始化到达每个点的最短路径和距离
	   for(int i=0;i<vertNum;++i) {
		      final[i] = false;	// 表示非终结点
		      distance[i] = gMatrix[start][i];
		      path[i] = "";	// 标记为无路径
		      //如果从start可到达i则标记路径
		      if(distance[i] < adjMatrix.getUnavailable())
		    	   path[i] = vertNames[start]+"-"+vertNames[i];
	   }
	   distance[start] = 0;
	   final[start] = true;
	   //n-1次迭代求出依次求出最短路径
      for(int i=0;i<vertNum;++i) {
    	    int minDis=adjMatrix.getUnavailable(),min=-1;
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
        	   if(final[i]  ||  gMatrix[min][i] == adjMatrix.getUnavailable() ) continue;
        	   if(minDis+gMatrix[min][i] < distance[i])  {
        		     distance[i] = minDis+gMatrix[min][i]; // 更新最短路径距离
        		     // 标记路径为从start-min-i
        		     path[i] = path[min]+"-"+vertNames[i];
        	   }
           }
      }
}
/**
 * 深度优先遍历
 * 递归实现
 */
void Graph::DFSTraverse() {
	std::vector<bool> visited(vertNum,false);
    for(int i=0;i < vertNum;++i) {
    	  if(!visited[i])
    		  DFS(i,visited); // 对每个没有访问的结点进行深度优先遍历
    }
    std::cout<<std::endl;
}
/**
 * 深度优先遍历顶点vertNo
 */
void Graph::DFS(int vertNo,std::vector<bool> & visited) {
	visit(vertNo); // 访问自身
	visited[vertNo] = true; // 标记为已经访问
	int next = 0,adjVertNo = -1;
	//对自己的临近结点 继续深度优先遍历
	while( next < vertNum && (adjVertNo = adjMatrix.findAdjVertNo(vertNo,next) ) != -1) {
		   if(!visited[adjVertNo])
			   DFS(adjVertNo,visited);
		   next = next +1;
	}
}
/**
 * 广度优先遍历
 * 利用队列实现
 */
void Graph::BFSTraverse() {
	 std::queue<int> queue;
	 std::vector<bool> visited(vertNum,false);
	 for(int i=0 ; i < vertNum;++i) {
		  if(visited[i]) continue;
		  queue.push(i);
		  visit(i);// 注意进入队列还未出队列时 即访问该顶点
		  visited[i] = true;
		  while(!queue.empty()) {
			   int curVertNo = queue.front();
			   queue.pop();
			   //顶点curVertNo的邻接顶点进入队列
			   int next = 0,adjVertNo= -1;
			   	while( next < vertNum && (adjVertNo = adjMatrix.findAdjVertNo(curVertNo,next) ) != -1) {
			   		   if(!visited[adjVertNo]) {
			   			   queue.push(adjVertNo);
			   			   visit(adjVertNo);
			   			   visited[adjVertNo] = true;
			   		   }
			   		   next = next +1;
			   	}
		  }
	 }
	 std::cout<<std::endl;
}
/**
 * 访问顶点vertNo
 */
void Graph::visit(int vertNo) {
     std::cout<<vertNames[vertNo]<<"\t";
}
/***
 * 无向图环检测
 */
bool Graph::udgCycleDetect() {
	std::vector<int> visitedNum(vertNum,0);
	std::vector<std::string> edges;
	int count = 0;
	for(int i=0;i < vertNum;++i) {
		if(visitedNum[i] == 0 &&
				udgCycleDetectDFS(i,visitedNum,count,edges))
			return true;
	}
	return false;
}
/**
 * 无向图利用深度优先遍历检测环
 * 检测到环 返回true 否则返回false
 */
bool Graph::udgCycleDetectDFS(int vertNo,std::vector<int> &visited,int &count,std::vector<std::string> &edges) {
	visited[vertNo] = ++count;
	int start = 0,adjNo = -1;
	//访问邻近顶点
	while(start < vertNum && (adjNo = adjMatrix.findAdjVertNo(vertNo,start) ) != -1) {
	   std::string edge = std::to_string(vertNo)+std::to_string(adjNo);
	   if(vertNo > adjNo)
			 edge = std::to_string(adjNo)+std::to_string(vertNo); // 保证1-2 2-1只用一个形式1-2存储
	   if(visited[adjNo] == 0) {
		   edges.push_back(edge); // 加入边
		   if(udgCycleDetectDFS(adjNo,visited,count,edges))
			   return true;
	   }else {
			 // 如果边vertNo-adjNo 没有包含到edges则存在环
			 if( std::find(edges.begin(),edges.end(),edge) == edges.end() ) {
				 std::cout << "cycle detected : "<<vertNames[vertNo] << " to "<<vertNames[adjNo]<<std::endl;
				 return true;
			 }
	   }
	   start = adjNo+1;
	}
	return false;
}

/**
 * 有向图环检测
 * 利用颜色标记法
 * 初始所有顶点颜色都为白色  第一次访问后置为灰色  所有顶点都访问后置为黑色
 */
bool Graph::dgCycleDetect() {
    std::vector<VertColor> color(vertNum,WHITE);
    std::vector<int> visitedNum(vertNum,0);
    int count = 0;
    for(int i = 0;i < vertNum;++i) {
    	if(visitedNum[i] == 0 && dgCycleDetectDFS(i,count,visitedNum,color))
    		return true;
    }
    return false;
}
/**
 * 有向图利用深度优先遍历检测环
 * 检测到环 返回true 否则返回false
 * 当前顶点遇到灰色邻接点即存在环
 */
bool Graph::dgCycleDetectDFS(int vertNo,int& count,std::vector<int>& visited,std::vector<VertColor> &color) {
	color[vertNo] = GRAY; // 首次访问置为灰色
	visited[vertNo] = ++count;
	int start = 0,adjNo = -1;
	//访问邻近顶点
	while(start < vertNum && (adjNo = adjMatrix.findAdjVertNo(vertNo,start) ) != -1)  {
		   if(visited[adjNo] == 0 && dgCycleDetectDFS(adjNo,count,visited,color) ) {
			   return true;
		   }
		   else if(color[adjNo] == GRAY) {
			   std::cout << "cycle detected : "<<vertNames[vertNo] << " to "<<vertNames[adjNo]<<std::endl;
			   return true;
		   }
		   start = adjNo+1;
	}
	color[vertNo] = BLACK ; // 所有邻接点访问完毕后置为黑色
	return false;
}
/**
 * 联合查找 union-find   所有顶点从0,1,...编号
 *
 * root,next模拟静态循环链表
 * root表示顶点所在集合循环链表的根节点
 * next表示顶点所在集合循环链表中下一个顶点
 * length表示当前顶点所在集合的长度
 *
 * 如果边的两个顶点u,v已经在同一个集合 则不执行合并，返回false
 * 否则合并两个集合  返回true
 */
bool Graph::unionEdge(std::vector<int>& root,std::vector<int>& next,std::vector<int>& length,int u,int v) {
         if(root[u] == root[v])
        	    return false;	 // 在同一个集合中则不加入  返回false
         if(length[root[v]] <= length[root[u]])
        	 std::swap(u,v); // 让u所在链表长度始终较小
         int rts = root[u],rtb = root[v];
         length[rtb] += length[rts]; // 较大者的根更新长度
         //更新较小者中所有顶点的根为长者所在链表的根
         root[rts] = rtb;
         for(int i= next[rts];i != rts ; i = next[i])
        	    root[i] = rtb;
          // 最后交换两者的next指针域
         std::swap(next[rts],next[rtb]);
         return true;
}
/**
 * Prim 最小生成树算法
 * 依次规定顶点集合u到未归并顶点集合v中最小边
 *
 */
void Graph::printMiniSpanTreePrim() {
     std::vector<Edge> closedges;
     std::vector<Edge> orderedEdges;
     //初始化closedges为顶点0的边
     for(int i=0;i < vertNum;++i) {
    	 Edge edge(0,i,gMatrix[0][i]);
    	 closedges.push_back(edge);
     }
     //选取n-1条边构成最小生成树
    for(int i=1;i < vertNum;++i) {
    	 int min = -1;
    	 for(std::vector<Edge>::size_type j = 1; j < closedges.size();++j) {
    		    if(closedges[j].edgeVal == 0 )
    		    	continue;
    		    if(min == -1)
    		    	  min = j;
    		    else if(closedges[j].edgeVal < closedges[min].edgeVal)
    		    	  min = j;
    	 }
    	 orderedEdges.push_back(closedges[min]);
    	 closedges[min].edgeVal = 0 ; // 选取后这条边长度置为0相当于并入了集合u
    	 //更新closedge中边
    	 for(int k=0 ;k < vertNum;++k) {
    		   if(gMatrix[min][k] < closedges[k].edgeVal) {
    			   closedges[k].src = min;
    			   closedges[k].edgeVal = gMatrix[min][k];
    		   }
    	 }
    }
    printMiniSpanningTree(orderedEdges);
}
/**
 * Kruskal 最小生成树算法
 * 依次加入落在T中不同连通分量中的(不构成回路)的最小边
 */
void Graph::printMiniSpanTreeKruskal() {
	 std::vector<Edge> edges;
	 std::vector<Edge> orderedEdges;
	 std::vector<int>  root;
	 std::vector<int>  next;
	 std::vector<int>  length(vertNum,1);
	 //初始化 找出所有边并按大小排序
	 adjMatrix.listAllEdges(edges);
	 std::sort(edges.begin(),edges.end());
	 //初始化union-find 辅助数组
	 for(int i=0;i < vertNum;++i) {
		 root.push_back(i);
		 next.push_back(i);
	 }
	 //逐个加入不构成环的边
	 int i = 1;
	 for(std::vector<Edge>::iterator it = edges.begin(); i < vertNum && it != edges.end();++it) {
		 	 bool ret = unionEdge(root,next,length,it->src,it->dest);
		 	 if(ret) {
		 		orderedEdges.push_back(*it); // 加入边集合
		 		++i;
		 	 }
	 }
	 printMiniSpanningTree(orderedEdges);
}
void Graph::printMiniSpanningTree(std::vector<Edge> &edges) {
	int sum = 0;
	for(std::vector<Edge>::iterator it = edges.begin();it != edges.end();++it) {
		std::cout<<vertNames[it->src]<<"-"<<vertNames[it->dest]<<" "<<it->edgeVal<<std::endl;
		sum += it->edgeVal;
	}
	std::cout << "mini cost: "<<sum<<std::endl;
}
/**
 * Dijlkstra 最小生成树算法
 * 逐个加入边到树中 如果检测到环则删除环中权值最大的边
 */
void Graph::printMiniSpanTreeDijkstra() {

}
/**
 * 寻找连通图中关节点
 */
void Graph::printArticulationPoint() {
	std::vector<int> visitedNum(vertNum,0),low(vertNum,0);
    int count = 1;
    visitedNum[0] = 1;
    //以0为根开始深度优先寻找
    int firstAdj = adjMatrix.findAdjVertNo(0,0);
    articulationDFS(firstAdj,count,visitedNum,low);
    if(count < vertNum) {     // 根节点有两个孩子则也为关节点
    	   std::cout << "articulation point: "<<vertNames[0]<<std::endl;
    	   int start = firstAdj+1,adjNo = -1;
    	   // 继续后续顶点寻找
    	   while(start < vertNum && ( adjNo = adjMatrix.findAdjVertNo(0,start)) != -1) {
    		       if(visitedNum[adjNo] == 0)
    		    	   articulationDFS(adjNo,count,visitedNum,low);
    		   	   start = adjNo+1;
    	   }
    }
}
/**
 * 深度优先搜索寻找关节点
 * low[v] = min {visited[v],low[w],visited[k] }  w is child vertex,k is parent vertex
 */
void Graph::articulationDFS(int vertNo,int &count,std::vector<int>& visited,std::vector<int>& low) {
		visited[vertNo] = ++count;
		int min = visited[vertNo];
		int start =0,adjNo = -1;
		while(start < vertNum && ( adjNo = adjMatrix.findAdjVertNo(vertNo,start)) != -1)  {
			 if(visited[adjNo] == 0) {  // 访问孩子节点  如果其low值比min小则更新
				 articulationDFS(adjNo,count,visited,low);
				 if(low[adjNo] < min)
					 min = low[adjNo];
				 if(low[adjNo] >= visited[vertNo])  // 必定为关节点
					 std::cout << "articulation point: "<<vertNames[vertNo]<<std::endl;
			 }else if(visited[adjNo] < min){   // 指向已经访问过的顶点(包括回边和指向父节点的树边)
				  min = visited[adjNo]; // 注意这里还是要做出判断  先前访问过的回边可能有多条
			 }
			 start = adjNo+1;
		}
		low[vertNo] = min; // 所有邻接顶点访问完毕后设置自己的low值
}
