/*
 * avltree.cpp
 *
 *  Created on: 2015年5月18日
 *      Author: wangdq
 */
#include "avltree.h"
#include <cmath>        // std::abs
#include <algorithm>    // std::max
#include "treeprinter.h"
/**
 * AVL树插入结点后调整动作
 * 自底向上调整结点的高度 遇到离current最近的不平衡点需要做旋转调整
 * 注意: 对最近的不平衡点调整后 或者 节点的高度值没有变化时 上层节点便不需要更新
 *         调整次数不大于1
 */
void AVLTree::insertAdjust(BSTNode* current,const int&e) {
	while(current != 0) {
		if(isUnbalanced(current)) {
			rebalance(current);
			break; 		// 调整过，则上层节点高度不变，不需要再调整
		}
		if(current->height == calcHeight(current))
			break;				// 节点在插入e前后高度不变，则上层结点不需要再调整
		current->height = calcHeight(current);
		current = current->parent;
	}
}
/**
 * AVL树删除结点后调整动作
 * 自底向上调整结点的高度 遇到离current最近的不平衡点需要做旋转调整
 * 注意: 对最近的不平衡点调整后，其上层结点仍然可能需要调整
 *         调整次数可能不止一次
 */
void AVLTree::removeAdjust(BSTNode* current,const int&e) {
	while(current != 0) {
		if(isUnbalanced(current)) {
			BSTNode * tmp = current->parent;
			rebalance(current);
			current = tmp;
			continue;	// 上层节点仍需判断是否需要调整
		}
		if(current->height == calcHeight(current))
			break;		// 节点删除e前后高度值不变 则上层结点无需调整
		current->height = calcHeight(current);
		current = current->parent;
	}
}
/**
 * p 指向失去平衡子树的根结点
 * 插入或者删除节点后旋转p指向结点使其保持平衡
 * 注意 LL LR RL RR 四种情况
 * 例如LR情况:
 * 	   p									p						          r
 * 	 /  							        / 								/  \
 * 	q   		(q,r)==>               r			(p,r)==>       q   p
 * 	  \									  /
 *        r								  q
 */
void AVLTree::rebalance(BSTNode*p) {
	if(calcHeight(p->left) - calcHeight(p->right) > 1) {	// 	p 的平衡因子为+2
		if(calcHeight(p->left->right) > calcHeight(p->left->left)) {	// LR p->left平衡因子为-1
			std::cout<< "left-then-right rotate: "<< p->key<<std::endl;
			leftRotate(p->left);
			rightRotate(p);
		}else {		// LL  p->left平衡因子为+1或者0
			std::cout<< "right rotate: "<< p->key<<std::endl;
			rightRotate(p);
		}
	}else if(calcHeight(p->right) - calcHeight(p->left) > 1) {	// p的平衡因子为-2
		if(calcHeight(p->right->left) > calcHeight(p->right->right)) {	// RL  p->right平衡因子为+1
			std::cout<< "right-then-left rotate: "<< p->key<<std::endl;
			rightRotate(p->right);
			leftRotate(p);
		}else {		// RR  p->right平衡因子为0或者-1
			std::cout<< "left rotate: "<< p->key<<std::endl;
			leftRotate(p);
		}
	}
}
/**
 * 判断结点是否为平衡节点
 */
bool AVLTree::isUnbalanced(const BSTNode* p)  {
	if(std::abs( calcHeight(p->left)-calcHeight(p->right) )> 1)
		return true;
	return false;
}
