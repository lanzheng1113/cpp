/*
 * adjmulist.h
 * 无向图的邻接多重表存储结构
 *  Created on: 2014年12月22日
 *      Author: wangdq
 */

#ifndef ADJMULIST_H_
#define ADJMULIST_H_
#include <istream>
#include <string>
#include <vector>

//边结点
class EBox {
public:
	EBox(int i,int j,int val,EBox*pi=0,EBox*pj=0) {
		  ivex = i;
		  jvex = j;
		  ilink = pi;
		  jlink = pj;
		  data = val;
		  isVisited = false;
	}
public:
	bool isVisited; // 访问标记
	int ivex,jvex; // 依附于边的两个顶点序号i,j
	EBox *ilink,*jlink; // 指向下一条依附于顶点i,j的边
	int data;	// 边包含的数据
};

//顶点结点
class VexBox {
public:
	VexBox(std::string alias ="") {
		  name = alias;
		  firstEdge = 0;
	}
public:
	std::string name;
	EBox *firstEdge;
};

/**
 * Adjacency Multilist
 * 邻接多重表
 */
class AdjMulist {
public:
	AdjMulist(std::istream & stream);
	~AdjMulist();
	void print();
	void printEdge(int vertNo); // 打印依附于顶点vertNo的边
	std::vector<std::string>& getVertNames() {
		return vertNames;
	}
	int getVertNum() {
		return vertNum;
	}
private:
	EBox *getNextEdge(EBox*p,int vertNo);
	void printEdge(EBox*p,int vertNo) ;
private:
	std::vector<std::string> vertNames;
	int vertNum;
	VexBox *head;
};
#endif /* ADJMULIST_H_ */
