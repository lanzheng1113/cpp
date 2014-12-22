/*
 * orthlist.cpp
 *
 *  Created on: 2014年12月22日
 *      Author: wangdq
 */

#include <iostream>
#include "orthlist.h"
/**
 * 从输入流建立十字链表
 * 流文件例如:
 * -------------------------------------------
 * 4  (顶点数目)
 *v1 v2 v3 v4 (顶点名称)
 *0 1 2   (0-1边权值为2)
 *0 2 1
 *2 0 5
 *2 3 4
 *3 0 5
 *3 1 9
 *3 2 3
 *------------------------------------------------------
 */
OrthList::OrthList(std::istream & stream) {
         stream >> vertNum;
         head = new VexNode[vertNum];
         //读入顶点名称
         for(int i=0;i < vertNum; ++i) {
        	   stream >> head[i].name;
        	   vertNames.push_back(head[i].name);
         }
         //读入弧的信息 关键是如何设置插入结点的hlink和tlink指针域
         int tno,hno,data;
         while(stream >> tno >> hno >> data) {
        	     ArcBox *node = new ArcBox(tno,hno,data,head[hno].firstin,head[tno].firstout );
        	     head[tno].firstout = head[hno].firstin = node;
         }
}
OrthList::~OrthList() {
	 for(int i=0; i < vertNum;++i) {
		 ArcBox *node = head[i].firstout;
		 while(node != 0) {
			 ArcBox *tmp = node->tlink;
			 delete node;
			 node = tmp;
		 }
	 }
	 delete[] head;
}
/**
 * 打印边信息
 */
void OrthList::printArc(ArcBox* p) {
	std::cout<<vertNames[p->tailvex]<<"\t"<<vertNames[p->headvex]<<"\t"<<p->data<<"\n";
}
void OrthList::print() {
	for(int i=0; i < vertNum;++i) {
		 ArcBox *node = head[i].firstout;
		 while(node != 0) {
			 ArcBox *tmp = node->tlink;
			 printArc(node);
			 node = tmp;
		 }
	}
}
// 打印vertNo顶点的输入边
void OrthList::printVertIn(int vertNo) {
	ArcBox *node = head[vertNo].firstin;
	 while(node != 0) {
		 ArcBox *tmp = node->hlink;
		 printArc(node);
		 node = tmp;
	 }
}
// 打印vertNo顶点的输出边
void OrthList::printVertOut(int vertNo) {
	ArcBox *node = head[vertNo].firstout;
	 while(node != 0) {
		 ArcBox *tmp = node->tlink;
		 printArc(node);
		 node = tmp;
	 }
}

