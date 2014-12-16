/*
 * rbtree.h
 *  参考自: http://zh.wikipedia.org/wiki/红黑树
 *  Created on: 2014年12月13日
 *      Author: wangdq
 */

#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

enum RBTreeColor{RED,BLACK};

template<typename K>
class RBTreeNode {
public:
	RBTreeNode(const K&k,RBTreeColor c,RBTreeNode<K>*p,RBTreeNode<K>*l=0,RBTreeNode<K>*r=0) {
		key = k;
		color = c;
		parent = p;
		left = l;
		right = r;
	}
	RBTreeNode(RBTreeColor c) {
		color = c;
		parent = 0;
		left =0;
		right = 0;
	}
public:
	RBTreeColor color;
	K key;
	RBTreeNode<K>* parent,*left,*right;
};

template<typename K>
class RBTree {
public:
	RBTree() {
		root = 0;
		NIL = new RBTreeNode<K>(BLACK);
	}
	~RBTree() {
		if(root != 0)
			destroy(root);
		delete NIL;
	}
	void insert(const K& k);
	void remove(const K&k);
	RBTreeNode<K> *search(const K&k);
	void inorder() ;
private:
	void leftRotate(RBTreeNode<K> *p);
	void rightRotate(RBTreeNode<K> *p);
	void insertFixup(RBTreeNode<K> *p);
	void removeOneChild(RBTreeNode<K> *p);
	void removeFixup(RBTreeNode<K> *p);
	void inorder(RBTreeNode<K> *p);
	void destroy(RBTreeNode<K> *p);
	void visit(RBTreeNode<K> *p);
	inline RBTreeNode<K> * getUncle(RBTreeNode<K> *p) {
		RBTreeNode<K> * grandParent = p->parent->parent;
		if( p->parent == grandParent->left)
			return grandParent->right;
		else
			return grandParent->left;
	}
	inline RBTreeNode<K>* getSibling(RBTreeNode<K>*p) {
		    if(p == p->parent->left)
		    	 return p->parent->right;
		    else
		    	return p->parent->left;
	}
public:
	RBTreeNode<K> *root,*NIL;	// NIL为所有节点共享的
};

#endif /* RED_BLACK_TREE_H_*/
