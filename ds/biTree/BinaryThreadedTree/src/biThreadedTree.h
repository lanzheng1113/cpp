/*
 * biThreadedTree.h
 *
 *  Created on: 2014年12月3日
 *      Author: wangdq
 */

#ifndef BITHREADEDTREE_H_
#define BITHREADEDTREE_H_
#include <iostream>

template<typename T>
class BiThreadedNode {
public:
	BiThreadedNode(T k,BiThreadedNode<T>*l=0,BiThreadedNode* r=0) {
		 key = k;
		 left = l;
		 right = r;
		 successor = 0; // 0 represents not thread ,but link
	}
public:
	T key;
	bool successor;
	BiThreadedNode<T> *left,*right;
};

template<typename T>
class BiThreadedTree {
public:
	BiThreadedTree() {
		root = 0;
	}
	virtual ~BiThreadedTree()  {
		clear(root);
		root = 0;
	}
	void insert(const T &e);
	void inorder();
protected:
	void clear(BiThreadedNode<T>* p);
	BiThreadedNode<T> *root;
	virtual void visit(BiThreadedNode<T>* p) {
		   std::cout<<p->key<<" ";
	}
};

#endif /* BITHREADEDTREE_H_ */
