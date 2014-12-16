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
		root = new RBTreeNode<K>(k,BLACK,0,NIL,NIL);
		return;
	}
	//找到插入位置
	RBTreeNode<K> *p = root,*parent,*node;
	while(p != NIL) {
		 if(k == p->key)
			 return;	// 已经存在则不再插入
		 parent = p;
		 if(k < p->key)
			 p = p->left;
		 else
			 p = p->right;
	}
	node = new RBTreeNode<K>(k,RED,parent,NIL,NIL);
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
		  p->color = BLACK;
		  return;
	  }else if(p->parent->color == BLACK) {				// case 2 p节点的父节点为黑色，直接返回
		   return;
	  }else {		// p节点必定存在祖父阶点grandparent
		  RBTreeNode<K> * parent=p->parent,*grandParent=parent->parent,* uncle = getUncle(p);
          if(uncle != NIL && uncle->color == RED) {											 // case 3 父节点和uncle都为红色
        	      parent->color = BLACK;
        	  	  uncle->color = BLACK;
        	  	  grandParent->color = RED;
        	  	  insertFixup(grandParent);	// 对祖父节点继续进行修复
          }else if( (p == parent->left && parent == grandParent->right )
        		  || ( p == parent->right && parent == grandParent->left) )  {  // case 4 RL & LR
        	  	  if(p == parent->left &&  parent == grandParent->right)
        	  		  rightRotate(parent);
        	  	  else
        	  		  leftRotate(parent);
        	  	  insertFixup(parent);	// 转换为LL/RR
          }else {																						// case 5 LL & RR
        	        parent->color = BLACK;
        	        grandParent->color = RED;
        	        if(p == parent->left && parent == grandParent->left )
        	        	rightRotate(grandParent);
        	        else
        	        	leftRotate(grandParent);
        	        return;
          }
	  }
}
template<typename K>
void  RBTree<K>::remove(const K&k) {
	RBTreeNode<K> * p = search(k);
	if(p == 0)
		 return;
	if(p->right == NIL) {
		removeOneChild(p);
	}
	else {
		  RBTreeNode<K> *suc = p->right;
		  while(suc->left != NIL)
			  suc = suc->left;
		  p->key = suc->key;		// 将后继节点suc键值到要删除的节点p
		  removeOneChild(suc);
	}
}
/**
 * 删除最多有一个非叶子孩子(non-leaf child)的节点p
 */
template<typename K>
void RBTree<K>::removeOneChild(RBTreeNode<K> *p) {
	RBTreeNode<K> *child = (p->left == NIL) ? p->right:p->left;
	//删除的是根节点且两个孩子均为叶子
	if(p->parent == 0 && p->left == NIL && p->right == NIL) {
		delete p;
		root = 0;
		return;
	}
	//删除的是根节点且有一个非叶子孩子节点
	if(p->parent == 0) {
		delete p;
		root = child;
		root->parent = 0;
		root->color = BLACK;
		return;
	}
    if(p == p->parent->left)
        	p->parent->left = child;
     else
        	p->parent->right = child;
    child->parent = p->parent;
    //case 1,p->color == red do nothing
    if(p->color == BLACK) {
    	  if(child->color == RED)
    		  child->color = BLACK;	//case 2
    	  else
    		  removeFixup(child);	// case 3
    }
    delete p;
}
/**
 * 删除修复
 * 注意sibling在节点旋转之后需要重新计算
 * n存在兄弟节点时，兄弟节点肯定不是叶子节点
 * 尽量减少尾部递归
 */
template<typename K>
void  RBTree<K>::removeFixup(RBTreeNode<K> *n) {
	 if(n->parent == 0) {		// case 31
		 n->color = BLACK;
		 return;
	 }
	 RBTreeNode<K> * s = getSibling(n),*p = n->parent;
	 if(s->color == RED) {		// case 32  处理完毕后继续进行4,5,6类别的修复
		   p->color = RED;
		   s->color = BLACK;
		   if(n == p->left)
			   leftRotate(p);
		   else
			   rightRotate(p);
		   s = getSibling(n);
	 }
	 if(p->color == BLACK && s->left->color == BLACK && s->right->color == BLACK) {			// case 33
					 s->color = RED;
					 removeFixup(p);	 //继续对parent修复
	 }else if(p->color == RED  && s->left->color == BLACK && s->right->color == BLACK) { 	// case 34 交换p,s颜色就完成
					p->color = BLACK;
					s->color = RED;
	}else {
		if(n == p->left && s->left->color == RED  && s->right->color == BLACK)   { 	// case 35 n == p->left  还要继续case6处理
			   s->left->color = BLACK;
			   s->color = RED;
			   rightRotate(s);
			   s = getSibling(n);
		}else if(n == n->right && s->left->color == BLACK  && s->right->color == RED)  { // case 35 n== n->right  还要继续case6处理
			  s->color = RED;
			  s->right->color = BLACK;
			  leftRotate(s);
			  s = getSibling(n);
		}
		 s->color = p->color;
		 p->color = BLACK;
		 if(n == p->left && s->right->color == RED) {		// case 36 n== p->left 处理完就OK
				s->right->color = BLACK;
				leftRotate(p);
		 }else if(n == p->right && s->left->color == RED) { // case 36 n== p->right 处理完就OK
				s->left->color = BLACK;
				rightRotate(p);
		 }
	}
}
/**
 * 查找键k,存在则返回该节点，否则返回0
 */
template<typename K>
RBTreeNode<K> * RBTree<K>::search(const K&k) {
	if(root == 0)
		   return 0;
	RBTreeNode<K>*p = root;
	while(p != NIL) {
		  if(k == p->key)
			   return p;
		  if( k < p->key)
			  p = p->left;
		  else
			  p = p->right;
	}
	return 0;
}
/**
 * p节点向左旋转
 * r为p父节点
 * q为调整后子树新根
 * 进行调整后，将会重新让r连接上q
 */
template<typename K>
void  RBTree<K>::leftRotate(RBTreeNode<K> *p) {
	RBTreeNode<K> *q = p->right,*r= p->parent;
	p->right = q->left;
	if(q->left != NIL)
		 q->left->parent = p;
	q->left = p;
	p->parent = q;
	//重新连接上子树新根q
	if(r == 0) {
		root = q;
		root->parent = 0;
	}else if(p == r->left) {
		  r->left = q;
		  q->parent = r;
	}else {
		r->right = q;
		q->parent = r;
	}
}
/**
 * p节点向右旋转
 * r为p父节点
 * q为调整后子树新根
 * 进行调整后，将会重新让r连接上q
 */
template<typename K>
void RBTree<K>::rightRotate(RBTreeNode<K> *p) {
	RBTreeNode<K> *q = p->left,*r=p->parent;
	p->left = q->right;
	if(q->right != NIL)
		q->right->parent = p;
    q->right = p;
    p->parent = q;
    //重新连接上子树新根q
    if(r == 0) {
    	  root = q;
    	  root->parent = 0;
    }else if(p == r->left) {
    	  r->left = q;
    	  q->parent = r;
    }else {
    	 r->right = q;
    	 q->parent = r;
    }
}
template<typename K>
void  RBTree<K>::inorder() {
	    if(root != 0)
	    	inorder(root);
		std::cout<<std::endl;
}
template<typename K>
void  RBTree<K>::inorder(RBTreeNode<K> *p) {
	  if(p != NIL) {
		  inorder(p->left);
		  visit(p);
		  inorder(p->right);
	  }
}
template<typename K>
void  RBTree<K>::destroy(RBTreeNode<K> *p) {
       if(p != NIL) {
    	   destroy(p->left);
    	   destroy(p->right);
    	   delete p;
       }
}
template<typename K>
void  RBTree<K>::visit(RBTreeNode<K> *p) {
     std::cout<<p->key<<"-"<<(p->color == RED ? "RED":"BLACK")<<"\t";
}



