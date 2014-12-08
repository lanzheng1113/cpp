/*
 * splaytree.h
 *
 *  Created on: 2014年12月7日
 *      Author: wangdq
 */

#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

#include <iostream>

template<typename T,typename V>
class SplayTreeNode {
public:
	SplayTreeNode(const T& k,const V& v,SplayTreeNode<T,V> *p=0,SplayTreeNode<T,V> *l=0,SplayTreeNode<T,V> *r=0){
		 key = k;
		 value = v;
		 parent = p;//父节点指针赋值
		 left = l;//左孩子指针赋值
		 right = r;//右孩子指针赋值
	}
public:
	T key;
	V value;
	SplayTreeNode<T,V> *left,*right,*parent; //保持父节点引用
};

template<typename T,typename V>
class SplayTree {
public:
		SplayTree() {
			root = 0;
		}
		~SplayTree() {
			clear(root);
			root = 0;
		}
	   bool insert(const T&k,const V&v);
	   void preorder();
	   void inorder();
	   bool search(const T& k,V& v);
	   bool FindAndDelete(const T&k);
	   bool isEmpty() const{
		   return root == 0;
	   }
private:
	   void visit(SplayTreeNode<T,V>* p) {
	   		 std::cout<<p->key<<"\t";
	   	}
	   SplayTreeNode<T,V>* zig1(SplayTreeNode<T,V>*p);
	   SplayTreeNode<T,V>* zig2(SplayTreeNode<T,V>*p);
	   void splay(SplayTreeNode<T,V>* p);
	   void inoder(SplayTreeNode<T,V>* p);
	   void preorder(SplayTreeNode<T,V>* p);
	    void clear(SplayTreeNode<T,V>* p);
	    SplayTreeNode<T,V>* leftRotate(SplayTreeNode<T,V>* p);
	   	SplayTreeNode<T,V>* rightRotate(SplayTreeNode<T,V>* p);
	   	void deleteByCopying(SplayTreeNode<T,V>*&p);
private:
	SplayTreeNode<T,V> *root;
};



#endif /* SPLAY_TREE_H_ */
