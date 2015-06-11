/*
 * avltree.h
 *
 *  Created on: 2015年5月18日
 *      Author: wangdq
 */

#ifndef BINARYSEARCHTREE_AVLTREE_H_
#define BINARYSEARCHTREE_AVLTREE_H_

#include "bst.h"

/**
 * 平衡二叉搜索树
 * AVL Tree
 */
class AVLTree : public BST {
private:
	void insertAdjust(BSTNode* p,const int&e);
    void removeAdjust(BSTNode* p,const int&e);
	void rebalance(BSTNode*p);
	inline bool isUnbalanced(const BSTNode* p) ;
};
#endif /* BINARYSEARCHTREE_AVLTREE_H_ */
