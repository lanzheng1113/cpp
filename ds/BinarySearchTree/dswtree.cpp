/*
 * dswtree.cpp
 *
 *  Created on: 2015年5月18日
 *      Author: wangdq
 */
#include <math.h>       /* log2 floor */
#include "dswtree.h"

/**
 *  DSW算法 创建主链 并返回结点个数
 *  创建主链的过程就是将树形成无左孩子或者无右孩子树的过程
 *  这里创建 无左孩子树
 */
int DSWTree::createBackbone() {
	  BSTNode* tmp = root;
	  int nodeCount = 0;
	  while(tmp != 0) {
		    if(tmp->left != 0) {
		    	rightRotate(tmp);			// 向右旋转
		    	tmp = tmp->parent; 	// tmp指向每次旋转生成的子树的根结点
		    }else {
		    	tmp = tmp->right;
		    	nodeCount++;		// 无左孩子时计数加1
		    }
	  }
	  return nodeCount;
}
/**
 *  Day–Stout–Warren (DSW) 全局平衡算法
 *  背景:
 *  	已知主链结点数目为n，则理想的完全平衡二叉树结点数目为:   m = 2^floor(log2(n+1))-1
 *   	n-m称为多出的结点
 *   算法思想:
 *   1)创建树的主链 形成一个无左孩子的单支树，并得到节点数目n
 *   2)每次对主链中第二个结点，开始向左旋转，重复这个旋转动作n-m次
 *   3) 重复2中旋转动作m = m/2次，并令m=m/2
 *   4) 当m大于1时重复3
 */
void DSWTree::balance() {
		if(root == 0) return;
		int n = createBackbone();
		toPng(std::string("Back bone"));
		int m = ( 1<<(int)floor(log2(n+1)) )-1;
	    leftRotateTheSecond(n-m);// 左旋转n-m次
       while(m > 1) {
    	   m = m / 2;
    	   leftRotateTheSecond(m); // 左旋转m次
       }
}
/**
 * 左旋转主链 m次
 * 注意每次旋转都是从根结点开始找第二个结点旋转
 */
void DSWTree::leftRotateTheSecond(int m) {
	BSTNode *current=root,*prev=0;		// current保存每次待旋转的子树的根 prev 保存每次旋转后树的根
	while(m > 0) {
		leftRotate(current);
		if(prev == 0)
			prev = root;
		else
			prev = prev->right;
		current = prev->right;
		--m;
	}
}



