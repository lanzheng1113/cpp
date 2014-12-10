/*
 * btree.h
 *
 *  Created on: 2014年12月9日
 *      Author: wangdq
 */

#ifndef BTREE_H_
#define BTREE_H_
/**
 * M阶B-Tree
 * 每个节点包含M-1个键值和M个子节点指针
 * 实际中每个节点多分配一个键值和子节点指针作为辅助空间
 */
template<typename T,int M=5>
class BTreeNode {
public:
	BTreeNode() {
		keynum = 0;
		parent = 0;
		for(int i = 0; i < M+1;++i)
			ptr[i] = 0;
	}
	BTreeNode(const T& e) {
			parent = 0;
			keys[0] = e;
			keynum = 1;
			for(int i = 0; i < M+1;++i)
				ptr[i] = 0;
	}
public:
	int keynum;
	T keys[M];
	BTreeNode<T,M> *parent;
	BTreeNode<T,M> *ptr[M+1];
};

template<typename T,int M=5>
class BTree {
public:
	BTree():MinKeyNum((M-1)/2+1),MaxKeyNum(M-1) {
		root = 0;
	}
	~BTree();
	void insert(const T& e);
	void remove(const T&e);
	void orderedTraverse();
	void breadFirstTraverse();
	BTreeNode<T,M>* search(const T&e);
private:
	void traverse(BTreeNode<T,M>* p);
	void clear(BTreeNode<T,M>* p);
	bool getInsertPos(const T&e,BTreeNode<T,M>*&p,int &index);
	BTreeNode<T,M>* search(BTreeNode<T,M>*p,const T&e);
	void splitNode(BTreeNode<T,M>*p,BTreeNode<T,M>*&node1,BTreeNode<T,M>*&node2);
private:
	BTreeNode<T,M> *root;
	const int MinKeyNum,MaxKeyNum;
};

#endif /* BTREE_H_ */
