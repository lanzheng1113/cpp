/*
 * splaytree.h
 *
 *  Created on: 2015年5月20日
 *      Author: wangdq
 */

#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include "bst.h"

/**
 * 伸展树
 * Splay tree
 */
class SplayTree : public BST {
public:
	BSTNode* search(const int& e);
private:
	void insertAdjust(BSTNode* p,const int&e);
	void removeAdjust(BSTNode* p,const int&e);
	void splay(BSTNode* p);
	void zig(BSTNode * x);
	void zigZig(BSTNode * x);
	void zigZag(BSTNode * x);
};

#endif /* SPLAYTREE_H_ */
