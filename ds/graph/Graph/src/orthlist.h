/*
 * orthlist.h
 *  有向图的十字链表存储结构
 *  Created on: 2014年12月22日
 *      Author: wangdq
 */

#ifndef ORTHLIST_H_
#define ORTHLIST_H_

#include <string>
#include <vector>
#include <istream>

//代表弧结点
class ArcBox {
public:
	ArcBox(int tv,int hv,int val,ArcBox* h=0,ArcBox*t=0) {
		tailvex = tv;
		headvex = hv;
		hlink = h;
		tlink = t;
		data = val;
	}
public:
	int tailvex,headvex;	// 该弧的尾和头顶点的位置
	ArcBox *hlink,*tlink;	// 分别为弧头相同和弧尾相同的弧的链域
	int data;	// 与弧相关的数据
};
//代表顶点结点
class VexNode {
public:
	VexNode(std::string alias="") {
		name = alias;
		firstin = firstout = 0;
	}
public:
	std::string name;
	ArcBox *firstin,*firstout;	// 分别指向该顶点第一条入弧和出弧
};
/**
 * orthogonal list 有向图的十字链表存储
 */
class OrthList {
public:
	OrthList(std::istream & stream);
	~OrthList();
	void print();
	void printVertIn(int vertNo); // 打印vertNo顶点的输入边
	void printVertOut(int vertNo); // 打印vertNo顶点的输出边
	int getVertNum() {
		return vertNum;
	}
	std::vector<std::string>& getVertNames() {
		return vertNames;
	}
private:
	void printArc(ArcBox* p);
private:
	int vertNum;
	std::vector<std::string> vertNames;
	VexNode *head;
};


#endif /* ORTHLIST_H_ */
