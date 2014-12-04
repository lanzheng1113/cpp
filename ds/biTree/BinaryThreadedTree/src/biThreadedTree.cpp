/*
 * biThreadTree.cpp
 *
 *  Created on: 2014年12月3日
 *      Author: wangdq
 */

#include "biThreadedTree.h"
/**
 * insert element in-order threaded tree
 */
template<typename T>
void BiThreadedTree<T>::insert(const T &e){
	BiThreadedNode<T>* newNode = new BiThreadedNode<T>(e);
	 BiThreadedNode<T>*p = root,*parent;
     if(root == 0) {
    	 root = newNode;
    	 return;
     }
     while(p != 0) {
    	    parent = p;
    	    if(e == p->key) {
    	    	  return; // no duplicate key
    	    }else if (e < p->key) {
    	    	p = p->left;
    	    }else if(p->successor == 0) {
    	    	p = p->right;
    	    }else {
    	    	break; // right child pointer is a thread,should break
    	    }
     }
     if(e < parent->key) {
    	     parent->left = newNode;
    	     parent->left->right = parent;
    	     parent->left->successor = true; // marked as thread
     }else if(parent->successor == 1) {
    	 	  newNode->successor = true; // marked as thread
    	 	  newNode->right = parent->right;
    	      parent->successor = false; // cancel parent's thread
    	      parent->right = newNode;
     }else {
    	 parent ->right = newNode;// parent is the right-most node
     }
}
template<typename T>
void BiThreadedTree<T>::inorder(){
       BiThreadedNode<T> *p = root;
       while(p != 0) {
    	       while(p->left != 0 )
    	    	     p = p->left;
    	       visit(p);
    	       while( p->successor == 1) {
    	    	   visit(p->right);
    	    	   p = p->right;
    	       }
    	       //goto right only if the node has right child
               p = p->right;
       }
}
/**
 * release tree memory using normal LRV traverse
 */
template<typename T>
void BiThreadedTree<T>::clear(BiThreadedNode<T>* p){
        if(p != 0) {
        	clear(p->left);
        	if(p->successor == 0) {
        		clear(p->right);
        	}
        	std::cout<<"release: "<<p->key<<std::endl;
        	delete p;
        }
}


