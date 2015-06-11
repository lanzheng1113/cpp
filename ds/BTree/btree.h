/*
 * btree.h
 *
 *  Created on: 2015年5月22日
 *      Author: wangdq
 */

#ifndef BTREE_H_
#define BTREE_H_
#include <iostream>
#include <string>
#include <sstream>

/**
 * M阶B-Tree结点
 * 每个节点包含M-1个键值和M个指针
 * 实际上每个结点多分配一个键值和指针用于辅助空间
 */
template<typename T,int M> class BTree;
template<typename T,int M=5>
class BTreeNode {
public:
		BTreeNode():parent(0),keynum(0),isLeaf(true) {
			for(int i=0;i < M+1;++i)
				childs[i] = 0;
		}
		BTreeNode(const T& k,BTreeNode *p=0) {
			keys[0]=k;
			parent = p;
			keynum = 1;
			isLeaf = true;
			for(int i=0;i < M+1;++i)
				 childs[i] = 0;
		}
		std::string toString() const{		// 用于调试
			std::stringstream ss;
			ss << keys[0];
			return ss.str();
		}
private:
		T keys[M];		// 键
		BTreeNode *childs[M+1];		// 孩子指针
		BTreeNode *parent;		// 父节点指针
		int keynum;		// 键数目
		bool isLeaf;		// 是否是叶子结点
		friend class BTree<T,M>;
		friend class BTreePrinter;	// 打印B-Tree为图片
};

/**
 * M 阶B-Tree
 */
template<typename T,int M=5>
class BTree {
public:
		BTree():root(0),MIN_KEY_NUM( (M+1)/2-1 ),MAX_KEY_NUM(M-1) {
		}
		~BTree();
		bool insert(const T&e);
		bool isEmpty() const {
			return root == 0;
		}
		const BTreeNode<T,M>* getRoot() const {
			return root;
		}
		bool remove(const T&e);
		void orderedTraverse(std::ostream& outstream=std::cout) const;
		BTreeNode<T,M> *  search(const T&e);
		void breadthFirstTraverse() const;	// 仅用于调试
private:
		int  searchInNode(BTreeNode<T,M> *node,const T&k);
		bool search(const T&e,BTreeNode<T,M> *&node,int &pos);
		void insert(BTreeNode<T,M>*p , int pos, const T&k, BTreeNode<T,M>* sright);
		void clear(BTreeNode<T,M>*p);
		void orderTraverse(const BTreeNode<T,M>*p,std::ostream& outstream) const;
		void splitNode(BTreeNode<T,M>*p, T&k,BTreeNode<T,M>*& sright); // 将p划分为两个节点
		void removeInleaf(BTreeNode<T,M>*leaf,int pos);	// 从叶子中删除pos处键
		void reallocKeys(BTreeNode<T,M> *parent, int curIndex, int sibIndex); // 在parent的cur和sib中重新分配键
		void mergeNode(BTreeNode<T,M>*parent,int curIndex,int sibIndex);	// 合并parent的cur和sib到cur
		void getProperSibling(BTreeNode<T,M>*current,int &curIndex, int &sibIndex);//获取cur的适当同级节点
		void copyElements(BTreeNode<T,M> *desp,int desIndex,BTreeNode<T,M>* srcp,int srcIndex);// 复制元素
		void leftShiftElements(BTreeNode<T,M> *p,int index,bool withLeftChild=true);	// 左移元素
		void rightShiftElements(BTreeNode<T,M> *p,int index,bool leftEmpty=true,int step=1);// 右移元素
private:
	   BTreeNode<T,M> *root;
	   const int MIN_KEY_NUM,MAX_KEY_NUM;	// 键值下限和上限
};

#endif /* BTREE_H_ */
