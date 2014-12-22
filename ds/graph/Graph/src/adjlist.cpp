/*
 * adjlist.cpp
 *
 *  Created on: 2014年12月21日
 *      Author: wangdq
 */
#include "adjlist.h"
#include <iterator>
#include <iostream>
#include <algorithm>

/**
 * 从输入流构造邻接表
 * 例如
 * ---------------------------------------
 * 4
 * v1 v2 v3 v4
 * 0 2 0   (尾结点序号-头节点序号--边长度)
 * 0 1 0
 * 2 3 0
 * 3 0 0
 * ---------------------------------------
 */
AdjList::AdjList(std::istream &stream) {
	stream >> vertNum;
	//创建邻接表头节点
	head = new VNode[vertNum];
	for(int i=0; i < vertNum;++i) {
		stream >> head[i].name;
		vertNames.push_back(head[i].name);
	}
	//创建邻接边
	int tailNo,headNo,edge;
	while(stream >> tailNo >> headNo >> edge) {
           ArcNode node(headNo,edge);
           head[tailNo].arcList.push_back(node);
	}
}
/**
 * 构造逆邻接表
 */
void AdjList::getInvAdjList(AdjList& list) {
	list.vertNum = vertNum;
	list.vertNames = vertNames;
	list.head = new VNode[vertNum];
    for(int i=0; i < vertNum;++i) {
    	 list.head[i].name = vertNames[i];
    	  for(std::list<ArcNode>::iterator it = head[i].arcList.begin(); it != head[i].arcList.end();++it) {
    		  	  	  int headNo = it->vertNo;
    		  	  	  ArcNode node(i,it->data);	// 将i->headNo出度 转换为headNo-->i入度表达
    		  	  	  list.head[headNo].arcList.push_back(node);
    	  }
    }
}
AdjList::~AdjList() {
	delete [] head;
}
void AdjList::print() {
      for(int i=0; i < vertNum;++i) {
    	      std::cout<<head[i].name<<"\t";
    	  	  std::copy(head[i].arcList.begin(),head[i].arcList.end(),std::ostream_iterator<ArcNode>(std::cout,"\t"));
    	  	  std::cout<<std::endl;
      }
}
std::ostream& operator << (std::ostream& stream,const ArcNode& node) {
	   stream <<node.vertNo;
	   return stream;
}


