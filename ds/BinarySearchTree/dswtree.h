/*
 * dswtree.h
 *
 *  Created on: 2015年5月18日
 *      Author: wangdq
 */

#ifndef BINARYSEARCHTREE_DSWTREE_H_
#define BINARYSEARCHTREE_DSWTREE_H_

#include "bst.h"

/**
 * 使用DSW算法全局平衡的二叉搜索树
 */
class DSWTree: public BST {
public:
	void balance();
private:
	 int createBackbone();
	 void leftRotateTheSecond(int m);
};




#endif /* BINARYSEARCHTREE_DSWTREE_H_ */
