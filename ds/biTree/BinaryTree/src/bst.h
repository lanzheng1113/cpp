/*
 * bst.h
 *  binary search tree
 *  Created on: 2014年12月2日
 *      Author: wangdq
 */

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <iostream>
/**
 * binary search tree p
 */
template<typename T>
class BSTNode {
public:
	BSTNode() {
		left = right = 0;
	}
	BSTNode(const T& k,BSTNode* l=0,BSTNode *r=0){
		key = k;
		left = l;
		right = r;
	}
public:
	T key;
	BSTNode  *left,*right;
};
/**
 * binary tree class
 */
template<typename T>
class BST {
public:
	     BST() {
	    	 root = 0;
	     }
	     virtual ~BST() {
	    	 clear();
	     }
	     void clear() {
	    	 clear(root);root = 0;
	     }
	     bool isEmpty() const {
	    	 return root == 0;
	     }
	     void preorder() {
	    	  preorder(root);
	     }
	     void inorder() {
	    	 inorder(root);
	     }
	     void postorder() {
	    	 postorder(root);
	     }
	     T* search(const T& e) const {
	    	 return search(root,e);
	     }
	     /**
	      * bread first traverse
	      */
	     void breadthFirst();
	     /**
	      * Iterative  pre-order traverse
	      */
	     void iterativePreorder();
	     /**
	      * Iterative  in-order traverse
	      */
	     void iterativeInorder();
	     /**
	      * Iterative post-order traverse
	      */
	     void iterativePostorder();
	     /**
	      *
	      */
	     void MorrisInorder();
	     void insert(const T& e);
	     void deleteByMerging(BSTNode<T> *&p);
	     void findAndDeleteByMerging(const T& e);
	     void deleteByCopying(BSTNode<T>*&p);
	     void findAndDeleteByCopying(const T&e);
	     void balance(T*,int,int);
protected:
	     void clear(BSTNode<T>* p);
	     T* search(BSTNode<T>* p,const T& e) const;
	     void preorder(BSTNode<T>* p);
	     void inorder(BSTNode<T>* p);
	     void postorder(BSTNode<T>* p);
	     virtual void visit(BSTNode<T>* p) {
	    	 std::cout<<p->key<<"\t";
	     }
protected:
	   BSTNode<T> * root;
};

#endif /* BINARY_SEARCH_TREE_H_ */
