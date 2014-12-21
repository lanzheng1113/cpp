/*
 * adjlist.h
 *  邻接表
 *  Created on: 2014年12月21日
 *      Author: wangdq
 */

#ifndef ADJLIST_H_
#define ADJLIST_H_

#include <string>
#include <list>
#include <vector>
#include <istream>

//表节点
class ListNode {
public:
	ListNode(int no,int val) {
		 vertNo = no;
		 data = val;
	}
	ListNode(const ListNode& node) {
		vertNo = node.vertNo;
		data = node.data;
	}
public:
	   int vertNo; //顶点序号
	   int  data;	// 该节点包含的数据，例如权值
};
//表头节点
class ListHeadNode {
public:
	ListHeadNode(std::string alias="") {
		name = alias;
	}
public:
	std::string name; // 名称
    std::list<ListNode> edgeList; // 边列表
};
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
	ListHeadNode * head;	// 表头节点
	int vertNum;
	std::vector<std::string> vertNames;	// 顶点名称列表
};



#endif /* ADJLIST_H_ */
