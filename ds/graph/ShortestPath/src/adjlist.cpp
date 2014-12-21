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
	int verNum;
	stream >> verNum;
	vertNum = verNum;
	//创建邻接表头节点
	head = new ListHeadNode[vertNum];
	for(int i=0; i < vertNum;++i) {
		std::string name;
		stream >> name;
		head[i].name = name;
		vertNames.push_back(name);
	}
	//创建邻接边
	int tailNo,headNo,edge;
	while(stream >> tailNo >> headNo >> edge) {
           ListNode node(headNo,edge);
           head[tailNo].edgeList.push_back(node);
	}
}
/**
 * 构造逆邻接表
 */
void AdjList::getInvAdjList(AdjList& list) {
	list.vertNum = vertNum;
	list.vertNames = vertNames;
	list.head = new ListHeadNode[vertNum];
    for(int i=0; i < vertNum;++i) {
    	 list.head[i].name = vertNames[i];
    	  for(std::list<ListNode>::iterator it = head[i].edgeList.begin(); it != head[i].edgeList.end();++it) {
    		  	  	  int headNo = it->vertNo;
    		  	  	  ListNode node(i,it->data);	// 将i->headNo出度 转换为headNo-->i入度表达
    		  	  	  list.head[headNo].edgeList.push_back(node);
    	  }
    }
}
AdjList::~AdjList() {
	delete [] head;
}
void AdjList::print() {
      for(int i=0; i < vertNum;++i) {
    	      std::cout<<head[i].name<<"\t";
    	  	  std::copy(head[i].edgeList.begin(),head[i].edgeList.end(),std::ostream_iterator<ListNode>(std::cout,"\t"));
    	  	  std::cout<<std::endl;
      }
}
std::ostream& operator << (std::ostream& stream,const ListNode& node) {
	   stream <<node.vertNo;
	   return stream;
}


