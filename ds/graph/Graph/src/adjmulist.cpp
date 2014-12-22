/*
 * adjmulist.cpp
 *
 *  Created on: 2014年12月22日
 *      Author: wangdq
 */
#include <iostream>
#include "adjmulist.h"
/**
 * 从输入流构造邻接多重表
 * 例如文件:
 * -----------------------------------------------
 * 5   (顶点个数)
 * v1 v2 v3 v4 v5  (顶点名称)
 * 0 1 3   (边0-1 权值为3)
 * 0 3 5
 * 2 1 4
 * 2 3 7
 * 4 1 9
 * 2 4 8
 * -----------------------------------------------
 */
AdjMulist::AdjMulist(std::istream & stream) {
	 stream >> vertNum;
	 head = new VexBox[vertNum];
	 //读入顶点名称
	 for(int i=0;i < vertNum;++i) {
		 stream >> head[i].name;
		 vertNames.push_back(head[i].name);
	 }
	 //读入边信息 关键在于设置边结点的指针域
	 int i,j,data;
	 while(stream >> i >> j >> data) {
		   EBox * node = new EBox(i,j,data,head[i].firstEdge,head[j].firstEdge);
		   head[i].firstEdge = head[j].firstEdge = node;
	 }
}
/**
 * 释放邻接多重表空间
 * 注意:同一条边被两个顶点链表引用 不要重复释放
 * 使用isVisited标记 第一次要释放时标记为true
 * 第二次访问时正式释放该节点
 */
AdjMulist::~AdjMulist() {
	//循环释放与i相关联的边
	for(int i=0; i < vertNum;++i) {
		EBox * prev = 0,*node = head[i].firstEdge;
		while(node != 0) {
			EBox * nextNode = getNextEdge(node,i);
			if(!node->isVisited) {		 // 标记为true等待第二次访问
				node->isVisited = true;
			}
			else {  		// 链接上下一条与i相关的边,释放结点空间
				  if(prev ==0)
					  	  head[i].firstEdge = nextNode;
				  else if(prev->ivex == i)
					      prev->ilink = nextNode;
				  else
					      prev->jlink = nextNode;
				  //调试语句
				  std::cout<<"remove: ";
				  printEdge(node,i);
                  delete node;
			}
			node = nextNode;
		}
	}
	delete[] head;
}
/**
 * 获取p指向的依附于vertxNo的的当前边另一个顶点编号和下一条依附于vertxNo的边
 * 注意依附于顶点i的边  不保证i一定在边结点的ivex域
 * 例如顶点4依附于边 4-1  2-4 都是可以的
 */
EBox *AdjMulist::getNextEdge(EBox*p,int vertNo) {
	  if(p == 0)
		  return 0;
	  if(p->ivex == vertNo)
		  return p->ilink;
	  else
		  return p->jlink;
}
/**
 * 以vertNo在前面形式打印边
 */
void AdjMulist::printEdge(EBox*p,int vertNo)  {
	int otherNo;
	if(p->ivex == vertNo)
		otherNo = p->jvex;
	else
		otherNo = p->ivex;
	std::cout<<vertNames[vertNo]<<"\t"<<vertNames[otherNo]<<"\t"<<p->data<<"\n";
}
void AdjMulist::print() {
	for(int i=0; i < vertNum;++i) {
		EBox * node = head[i].firstEdge;
			while(node != 0) {
				EBox * nextNode = getNextEdge(node,i);
				if(!node->isVisited) {
					printEdge(node,i);
					node->isVisited = true;
				}else {
					node->isVisited = false;
				}
				node = nextNode;
			}
	}
}
/**
 * 打印依附于顶点vertNo的边
 */
void AdjMulist::printEdge(int vertNo) {
	EBox * node = head[vertNo].firstEdge;
	while(node != 0) {
		EBox * nextNode = getNextEdge(node,vertNo);
		printEdge(node,vertNo);
		node = nextNode;
	}
}


