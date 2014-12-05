/*
 * AVLTree.h
 *
 *  Created on: 2014年12月4日
 *      Author: wangdq
 */

#ifndef AVLTREE_SRC_AVLTREE_H_
#define AVLTREE_SRC_AVLTREE_H_
#include <iostream>

template<typename T,typename V>
class AVLNode{
public:
	AVLNode(const T& k,const T&v, AVLNode<T,V>*l=0, AVLNode<T,V>*r=0) {
		key = k;
		value = v;
		left = l;
		right = r;
		height = 1;
	}
public:
       T key;
       V value;
       AVLNode<T,V> *left,*right;
       int height;
};

template<typename T,typename V>
class AVLTree {
public:
	AVLTree() {
		root = 0;
	}
	~AVLTree() {
		clear(root);
		root = 0;
	}
	void inorderTraverse();
	void insert(const T & e,const V& v);
	bool FindAndDelete(const T&e);
	bool isEmpty();
	int  height();
private:
	void visit(AVLNode<T,V>* p) {
		 std::cout<<p->key<<"\t";
	}
	void clear(AVLNode<T,V>* p);
	void leftRotate(AVLNode<T,V>* &p);
	void rightRotate(AVLNode<T,V>* &p);
	bool insert(AVLNode<T,V> *&p,const T & e,const V& v,bool &adjusted);
	bool deleteByCopying(AVLNode<T,V>*&p,const T& e);
	int height(AVLNode<T,V> *p);
	void inorder(AVLNode<T,V>* p);
	AVLNode<T,V>* root;
};



#endif /* AVLTREE_SRC_AVLTREE_H_ */
