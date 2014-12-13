/*
 * rbtree.h
 *
 *  Created on: 2014年12月13日
 *      Author: wangdq
 */

#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

enum RBTreeColor{Red,Black};

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
	}
	~RBTree() {
		destroy(root);
	}
	void insert(const K& k);
	void remove(const K&k);
	RBTreeNode<K> *search(const K&k);
	void inorder() ;
private:
	RBTreeNode<K> * leftRotate(RBTreeNode<K> *p);
	RBTreeNode<K> * rightRotate(RBTreeNode<K> *p);
	void insertFixup(RBTreeNode<K> *p);
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
public:
	RBTreeNode<K> *root;
};

#endif /* RED_BLACK_TREE_H_*/
