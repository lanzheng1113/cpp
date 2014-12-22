/*
 * adjlist.h
 *  邻接表
 *  Created on: 2014年12月21日
 *      Author: wangdq
 */

#ifndef GRAPH_SRC_ADJLIST_H_
#define GRAPH_SRC_ADJLIST_H_

#include <string>
#include <list>
#include <vector>
#include <istream>

//表节点
class ArcNode {
public:
	ArcNode(int no,int val) {
		 vertNo = no;
		 data = val;
	}
	ArcNode(const ArcNode& node) {
		vertNo = node.vertNo;
		data = node.data;
	}
public:
	   int vertNo; //顶点序号
	   int  data;	// 该节点包含的数据，例如权值
};
//表头节点
class VNode {
public:
	VNode(std::string alias="") {
		name = alias;
	}
public:
	std::string name; // 名称
    std::list<ArcNode> arcList; // 边列表
};
/**
 * 邻接表
 * 图的一种链式存储结构
 */
class AdjList {

public:
	AdjList() {}
	AdjList(std::istream &stream);
	~AdjList();
	void print();
	int getVertNum() {
		return vertNum;
	}
	std::vector<std::string>& getVertNames() {
		  return vertNames;
	}
	void   getInvAdjList(AdjList& list);	// 构造逆邻接表
private:
	VNode * head;	// 表头节点
	int vertNum;
	std::vector<std::string> vertNames;	// 顶点名称列表
};



#endif /* GRAPH_SRC_ADJLIST_H_ */
