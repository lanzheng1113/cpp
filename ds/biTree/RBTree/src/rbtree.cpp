/*
 * rbtree.cpp
 *
 *  Created on: 2014年12月13日
 *      Author: wangdq
 */
#include "rbtree.h"
#include <iostream>
/**
 * 插入键值k
 */
template<typename K>
void RBTree<K>::insert(const K& k) {
	//空树插入
	if(root == 0 ) {
		root = new RBTreeNode<K>(k,Black,0);
		return;
	}
	//找到插入位置
	RBTreeNode<K> *p = root,*parent,*node;
	while(p != 0) {
		 if(k == p->key)
			 return;	// 已经存在则不再插入
		 parent = p;
		 if(k < p->key)
			 p = p->left;
		 else
			 p = p->right;
	}
	node = new RBTreeNode<K>(k,Red,parent);
	if( k < parent->key)
		parent->left = node;
	else
		parent->right = node;

	insertFixup(node);	// 开始修复node
}
/**
 * 修复插入后p节点
 */
template<typename K>
void  RBTree<K>::insertFixup(RBTreeNode<K> *p) {
	  if(p->parent == 0)  {										// case 1 根节点则调整为黑色
		  p->color = Black;
		  return;
	  }else if(p->parent->color == Black) {				// case 2 p节点的父节点为黑色，直接返回
		   return;
	  }else {		// p节点必定存在祖父阶点grandparent
		  RBTreeNode<K> * parent=p->parent,*grandParent=p->parent->parent;
		  RBTreeNode<K> * uncle = getUncle(p),*tmpRoot,*topParent=grandParent->parent;
          if(uncle != 0 && uncle->color == Red) {											 // case 3 父节点和uncle都为红色
        	      parent->color = Black;
        	  	  uncle->color = Black;
        	  	  grandParent->color = Red;
        	  	  insertFixup(grandParent);	// 对祖父节点继续进行修复
          }else if( (p == parent->left && parent == grandParent->right )
        		  || ( p == parent->right && parent == grandParent->left) )  {  // case 4 RL & LR
        	  	  if(p == parent->left &&  parent == grandParent->right)
        	  		  grandParent->right = rightRotate(parent);
        	  	  else
        	  		  grandParent->left = leftRotate(parent);
        	  	  insertFixup(parent);	// 转换为LL/RR
          }else {																						// case 5 LL & RR
        	        parent->color = Black;
        	        grandParent->color = Red;
        	        if(p == parent->left && parent == grandParent->left )
        	        	tmpRoot = rightRotate(grandParent);
        	        else
        	        	tmpRoot = leftRotate(grandParent);
        	        //将返回的根节点重新链接上
        	        if(topParent == 0)
        	        	 root = tmpRoot;
        	        else if(grandParent == topParent->left)
        	        	topParent->left = tmpRoot;
        	        else
        	        	topParent->right = tmpRoot;
        	        return;
          }
	  }
}
template<typename K>
void  RBTree<K>::remove(const K&k) {

}
template<typename K>
void  RBTree<K>::removeFixup(RBTreeNode<K> *p) {

}
template<typename K>
RBTreeNode<K> * RBTree<K>::search(const K&k) {

}
/**
 * 以p为根进行左旋转
 */
template<typename K>
RBTreeNode<K> *  RBTree<K>::leftRotate(RBTreeNode<K> *p) {
	RBTreeNode<K> *q = p->right;
	p->right = q->left;
	if(q->left != 0) q->left->parent = p;
	q->left = p;
	q->parent = p->parent;
	p->parent = q;

	return q;
}
template<typename K>
RBTreeNode<K> *  RBTree<K>::rightRotate(RBTreeNode<K> *p) {
      RBTreeNode<K>* q = p->left;
      p->left = q->right;
      if(q->right != 0)  q->right->parent = p;
      q->right = p;
      q->parent = p->parent;
      p->parent = q;

      return q;
}
template<typename K>
void  RBTree<K>::inorder() {
		inorder(root);
		std::cout<<std::endl;
}
template<typename K>
void  RBTree<K>::inorder(RBTreeNode<K> *p) {
	  if(p != 0) {
		  inorder(p->left);
		  visit(p);
		  inorder(p->right);
	  }
}
template<typename K>
void  RBTree<K>::destroy(RBTreeNode<K> *p) {
       if(p != 0) {
    	   destroy(p->left);
    	   destroy(p->right);
    	   delete p;
       }
}
template<typename K>
void  RBTree<K>::visit(RBTreeNode<K> *p) {
     std::cout<<p->key<<"-"<<(p->color == Red ? "Red":"Black")<<"\t";
}



