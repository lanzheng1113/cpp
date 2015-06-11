/*
 * splaytree.cpp
 *
 *  Created on: 2015年5月20日
 *      Author: wangdq
 */
#include "splaytree.h"

/**
 * 查找元素e
 * 如果存在包含e的结点  则返回包含e的节点指针，并且将该节点调为新的根节点
 * 否则返回0
 */
BSTNode* SplayTree::search(const int& e)  {
	BSTNode *prev = 0;
	BSTNode *current = BST::iterativeSearch(e,prev);
	if(current != 0) {
		toPng(std::string("search: ")+current->toString(),current);
		splay(current);
	}
	return current;
}
/**
 * 插入节点后调整动作
 * prev指向插入位置的父节点
 * 如果插入节点不是根节点，则调整至根节点
 */
void SplayTree::insertAdjust(BSTNode* prev,const int&e) {
	if(prev == 0)
		return;
	else if(e < prev->key)
		splay(prev->left);
	else
		splay(prev->right);
}
/**
 * 删除结点后调整动作
 * prev指向实际删除节点的父节点
 * 将prev节点调整至根节点
 */
void SplayTree::removeAdjust(BSTNode* prev,const int&e) {
	if(prev != 0)
		splay(prev);
}
/**
 * 对结点x进行伸展操作  也就是将x调整至根部作为新的根节点
 */
void SplayTree::splay(BSTNode* x) {
	if(x == 0) return;
	while(x->parent != 0) {
		if(x->parent == root) 	// x没有祖父节点
			zig(x);
		else if( (x == x->parent->left && x->parent == x->parent->parent->left )
				|| (x == x->parent->right && x->parent == x->parent->parent->right) ) 	// 同构配置
			zigZig(x);
		else		// 异构配置
			zigZag(x);
	}
}
/**
 * zig操作
 * 当x没有祖父节点时进行的旋转操作
 * x是左孩子: 右旋转
 * 	    p							x
 * 	  /   \						   /  \
 * 	 x    c		==>     	  a   p
 *    /  \								  /  \
 *   a   b  							 b    c
 *
 * x是右孩子: 左旋转
 * 		 p								x
 * 	   /  \  						  /   \
 *       c    x			==> 		 p    b
 *       	  /  \					    /  \
 *       	 a    b				    c   a
 */
void SplayTree::zig(BSTNode * x) {
	BSTNode * p = x->parent;
	if(x == p->left) 	 {	// 右旋转
		std::cout << "right rotate: "<<p->key<<std::endl;
		BST::rightRotate(p);
	}
	else {	// 左旋转
		std::cout << "left rotate: "<<p->key<<std::endl;
		BST::leftRotate(p);
	}
}
/**
 * zig-zig操作
 * 当x有祖父节点   x和其父节点是同构的(从祖父往下开始调整)
 * x是和x的父节点都是其对应应父节点的左孩子或右孩子
 * LL情况： 连续两次右旋转
 * 				g								 p										x
 * 			 /    \							   /   \								  /   \
 * 			p		d						  x     g								 a     p
 * 		  /  \				(g,p)==>	 / \    / \		(p,x)==>			  /   \
 * 		 x    c							a  b   c  d								 b    g
 * 	    /  \																				  /  \
 * 	   a    b																				 c    d
 *
 * RR情况：连续两次左旋转
 * 			g									  p                                x
 * 		  /  \									/    \							  /   \
 * 		 d   p			(g,p)==>       g      x     (p,x)==>      p    b
 * 		    /   \							   /  \   / \ 					   /  \
 * 		   c     x							  d   c  a  b				  g    a
 * 		        /  \														/   \
 * 		       a    b	   												   d   c
 */
void SplayTree::zigZig(BSTNode * x) {
		BSTNode *p = x->parent, *g = x->parent->parent;
		BSTNode *gg = g->parent;
		if(x == p->left && p == g->left) {		// LL
			std::cout << "right-then-right rotate: "<<g->key<<std::endl;
			BST::rightRotate(g);
			BST::rightRotate(p);
		}else {				// RR
			std::cout << "left-then-left rotate: "<<g->key<<std::endl;
			BST::leftRotate(g);
			BST::leftRotate(p);
		}
		if(gg == 0)
			root->height = calcHeight(root);
		else
			gg->height = calcHeight(gg);
}
/**
 * zig-zag操作
 * 当x有祖父结点  x与其父节点是异构的(从x往上开始调整)
 * case 1: x是父节点左孩子，而父节点是祖父节点的右孩子	RL
 * case 2: x是父节点右孩子，而父节点是祖父结点的左孩子   LR
 * LR情况: 先左旋转后右旋转
* 						 g												g											 x
* 					   /   \										  /   \										   /   \
* 					  p    d			(p,x) ==>			     x     d		(g,x)==> 				  p	 g
* 					 /  \										   /   \										 /  \	 / \
* 					a	 x										  p    c										a   b  c  d
* 						/  \									/   \
* 					   b    c								   a    b
*
* RL情况: 先右旋后左旋
* 					  g									g									   x
* 					 /  \							  /   \									/    \
* 					d   p       (p,x)==>		d      x         (g,x)==>		  g       p
* 					    /  \							  /   \							 /  \    /  \
* 					   x   a							 b    p						d   b  c   a
* 					  /  \									  /  \
* 					 b   c 					   			 c    a
  */
void SplayTree::zigZag(BSTNode * x) {
	BSTNode*  p = x->parent, *g = x->parent->parent;
	BSTNode* gg = g->parent;
	if(x == p->right) {		// LR
		std::cout << "left-then-right rotate: "<<g->key<<std::endl;
		BST::leftRotate(p);
		BST::rightRotate(g);
	}else {		// RL
		std::cout << "right-then-left rotate: "<<g->key<<std::endl;
		BST::rightRotate(p);
		BST::leftRotate(g);
	}
	if(gg == 0)
		root->height = calcHeight(root);
	else
		gg->height = calcHeight(gg);
}
