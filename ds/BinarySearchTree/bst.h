/*
 * bst.h
 *
 *  Created on: 2015年5月14日
 *   Author: wangdq
 */

#ifndef BINARYSEARCHTREE_BST_H_
#define BINARYSEARCHTREE_BST_H_

#include <iostream>
#include <string>
#include <sstream>

// 前向声明
class BST;
class AVLTree;
class DSWTree;
class SplayTree;
class BiTreePrinter;
/**
 * 二叉树搜索树结点类BSTNode
 *  暂时处理整型数据
 */
class BSTNode {
public:
	      BSTNode(const int& e,BSTNode*p ,BSTNode *l=0,BSTNode *r=0):key(e),height(1) ,parent(p),
	    		  left(l),right(r){
	      }
	      std::string toString() const{	// 用于调试
				std::ostringstream oss;
				oss << key;
				return oss.str();
	      }
private:
	      int key;
	      int height;		// 以这个结点为根的树的高度
	      BSTNode *parent,*left,*right;
	      friend class BST;			// 二叉搜索树
	      friend class AVLTree;    // 平衡二叉树
	      friend class DSWTree;	// DSW算法实现的
	      friend class SplayTree; // 伸展树
	      friend class BiTreePrinter;	// 将BST转换为图片的类
};

/**
 * 二叉搜索树类BST
 */
class BST {
public:
	BST():bwritePng(true),bshowVisitInfo(true),root(0){
	}
	virtual ~BST() {
		clear();
	}
	bool isEmpty() const {
		return root == 0;
	}
	void preorder() const{
		preorder(root);
	}
	void inorder() const{
		inorder(root);
	}
	void postorder() const{
		postorder(root);
	}
	void iterativePreorder() const;
	void iterativeInorder() const;
	void iterativePostorder() const;
	void MorrisInorder();
	void breadthFirst() const;
	virtual BSTNode* search(const int& e) {		// 虚函数  子类按需实现
		BSTNode* prev = 0;
    	return iterativeSearch(e,prev);
    }
	bool insert(const int& e);
	BSTNode* iterativeSearch(const int& e,BSTNode*&prev) ;
    bool findAndRemoveByMerging(const int& e);
    bool findAndRemoveByCopying(const int& e);
    void balanceTree(int *data,int first,int last);
    /**
     * 返回节点的高度
     */
    int getHeight(const BSTNode* p) const{
    	if(p == 0) return 0;
    	else return p->height;
    }
    int getBF( const BSTNode* p) const {
    	 return calcHeight(p->left) - calcHeight(p->right);
    }
    const BSTNode* getRoot() const{
    	return root;
    }
    void toPng(const std::string &desp=std::string(),const BSTNode* pcur=0) const;	// 仅用于调试
    bool bwritePng;// 仅用于调试
    bool bshowVisitInfo;// 仅用于调试
protected:
	 BSTNode *root;
	 int calcHeight(const BSTNode* p)  const;
	 void leftRotate(BSTNode* p);
	 void rightRotate(BSTNode* p);
	 BSTNode* recursiveSearch(BSTNode* p, const int& e);
	 void preorder(const BSTNode* p) const;
	 void inorder(const BSTNode* p) const;
	 void postorder(const BSTNode* p) const;
	 void removeByMerging(BSTNode*& p,const int& e);
	 void removeByCopying(BSTNode*& p,const int& e);
	 virtual void insertAdjust(BSTNode* p,const int&e);		// 虚函数 子类按需实现
	 virtual void removeAdjust(BSTNode* p,const int&e);		// 虚函数 子类按需实现
	 virtual void visit(const BSTNode *p) const{			// 虚函数 子类按需实现
		 if(bshowVisitInfo)
			 std::cout << p->key << "(height=" << p->height << ")\t";
		 this->toPng(std::string("visiting: ")+p->toString(),p);
	 }
private:
	 void clear() {
		clear(root);
		root = 0;
	 }
	 void clear(BSTNode* p);
};

#endif /* BINARYSEARCHTREE_BST_H_ */
