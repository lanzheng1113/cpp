/*
 * bst.cpp
 *
 *  Created on: 2015年5月14日
 *   Author: wangdq
 */
#include <queue>   // for std::queue
#include <stack>    // for std::stack
#include <algorithm>    // std::max
#include <string>
#include "bst.h"
#include "treeprinter.h"
using std::queue;
using std::stack;

/**
 *  Joseph M. Morris 中序遍历算法
 *  遍历顺序LVR
 *  不使用递归和栈实现的遍历算法
 *  在遍历过程中修改和恢复树结构的方法
 *  算法思想：
 *  1) 如果树为空则返回，否则current = root,current表示当前结点
 *  2) 对于每个current
 *     如果current左孩子为空,则访问current,并将其右孩子赋给current
 *     否则:
 *            迭代取current的左孩子的最右边孩子tmp
 *            如果tmp是current的临时父节点，则访问current并解除临时父子关系，并将current右孩子赋给current
 *            否则将tmp置为current的临时父节点，并将current的左孩子赋给current
 * 3) 持续2过程直到current为空
 */
void BST::MorrisInorder() {
	if(root == 0) return;
	BSTNode* current = root,*tmp = 0;
	while(current != 0) {
		if(current->left == 0) {
			visit(current);
			current = current->right;
		}else {
			tmp = current->left;
			while(tmp->right !=0 && tmp->right != current)
				 tmp = tmp->right;
			if(tmp->right == 0) {  	// tmp结点将成为current的临时父节点
				tmp->right = current;
				current = current->left;
			}else {							// 解除tmp结点与current结点之间的临时父子关系
				visit(current);
				tmp->right = 0;
				current = current->right;
			}
		}
	}
}
/**
 * 宽度优先搜索
 * 遍历顺序为从上到下，从左到右
 * 借助队列实现
 */
void BST::breadthFirst() const{
	if(root == 0) return;
	queue<const BSTNode*> nodeQueue;// 指针队列
    nodeQueue.push(root);
    const BSTNode* current = 0;
    while(!nodeQueue.empty()) {
    	current = nodeQueue.front();
    	nodeQueue.pop();
    	visit(current);
    	if(current->left != 0)
    		nodeQueue.push(current->left);	// 非空左孩子入队列
    	if(current->right != 0)
    		nodeQueue.push(current->right);	// 非空右孩子入队列
    }
}
/**
 * 非递归实现的先序遍历
 * 遍历顺序为VLR
 * 借助栈实现
 * 算法思想：
 * 1) 树为空则退出，否则根节点入栈
 * 2) 访问栈顶元素v，出栈，元素v的右孩子入栈，元素v的左孩子入栈
 * 3) 持续2直到栈为空停止
 */
void BST::iterativePreorder() const{
	if(root == 0) return;
	stack<const BSTNode*> nodeStack;
	nodeStack.push(root);
	const BSTNode* current = 0;
	while(!nodeStack.empty()) {
		current = nodeStack.top();
		nodeStack.pop();
		visit(current);
		if(current->right != 0)
			nodeStack.push(current->right);	// 非空右孩子入栈
		if(current->left != 0)
			nodeStack.push(current->left);	  // 非空左孩子入栈
	}
}
/**
 * 非递归实现的中序遍历
 * 遍历顺序为LVR
 * 借助栈实现
 * 算法思想：
 * 1) 树为空则退出，否则current = root,其中current为待寻找最左边孩子的结点
 * 2) 循环查找current的最左孩子结点，直到左孩子为空，此过程中结点都入栈
 * 3) 取栈顶元素v,出栈，持续这个过程直到v存在右孩子时，将v的右孩子赋值给current,转到过程2
 * 4) 当current 不为空时，持续步骤2和3
 */
void BST::iterativeInorder() const{
	if(root == 0) return;
	stack<const BSTNode *> nodeStack;
	const BSTNode* current = root;
	const BSTNode* top = 0;
	while(current != 0) {
		// 寻找最左边孩子
		while(current != 0) {
			nodeStack.push(current);
			current = current->left;
		}
		// 访问栈顶并出栈 直至找到下一个待寻找最左边孩子的节点
		while(!nodeStack.empty() && current == 0) {
			top = nodeStack.top();
			nodeStack.pop();
			visit(top);
			current = top->right;
		}
	}
}
/**
 * 非递归实现的后续遍历
 * 遍历顺序为LRV
 * 借助栈实现
 * 算法思想:
 * 1) 树为空则退出，否则current = root,其中current为待寻找最左边孩子的结点
 * 2) 循环查找current的最左孩子结点，直到左孩子为空，此过程中结点都入栈
 * 3) 当栈不空并且current为空时,取栈顶元素v
 *     如果v没有右孩子或者v的右孩子刚刚访问过(用prev指针判断)
 *         	则将v出栈,访问v,用prev指针记录v结点,current赋值为空;
 *     否则  v的右孩子赋给current,转步骤2
 * 4) 当current不为空时，持续步骤2和3
 */
void BST::iterativePostorder() const{
	if(root == 0) return;
	stack<const BSTNode*> nodeStack;
    const BSTNode* current = root;
    const BSTNode* prev = 0,*top = 0;
    while(current != 0) {
    	// 寻找最左边孩子
    	while(current != 0) {
    		nodeStack.push(current);
    		current = current->left;
    	}
    	while(!nodeStack.empty() && current == 0) {
    		top = nodeStack.top();
    		if(top->right == 0 || top->right == prev) {	// 栈顶元素没有右孩子或者右孩子刚刚访问过
    			nodeStack.pop();
    			visit(top);
    			prev = top;	// 出栈结点用prev记录下来
    			current = 0;
    		}else {				// 右孩子为待寻找最左边孩子的结点
    			current = top->right;
    		}
    	}
    }
}
/**
 * 递归实现的先序遍历
 * 遍历顺序为VLR
 */
void BST::preorder(const BSTNode* p) const{
    if( p != 0) {
    	visit(p);
    	preorder(p->left);
    	preorder(p->right);
    }
}
/**
 * 递归实现的中序遍历
 * 遍历顺序为LVR
 */
void BST::inorder(const BSTNode* p) const{
	  if(p != 0) {
		  inorder(p->left);
		  visit(p);
		  inorder(p->right);
	  }
}
/**
 * 递归实现的后序遍历
 * 遍历顺序为LRV
 */
void BST::postorder(const BSTNode* p) const{
	if(p != 0) {
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}
/**
 * 插入元素
 * 迭代实现
 * 如果键值已经存在则返回false
 * 否则插入成功返回true,插入错误返回false
 * 算法：
 * 1)首先通过比较值的大小，查找插入位置
 * 2)在插入位置处添加新结点
 * 3)更新插入结点路径上的结点的高度值
 */
bool BST::insert(const int& e){
        BSTNode *prev = 0;		// prev 保存插入点的父节点
        BSTNode *current =iterativeSearch(e,prev);
		if(current != 0)
			return false;
		BSTNode* inserted = new BSTNode(e,prev);
        if(prev == 0)
        	root = inserted;
        else if(e < prev->key)
        	prev->left = inserted;
        else
        	prev->right = inserted;
        toPng(std::string("insert: ")+inserted->toString(),inserted);
        insertAdjust(prev,e);	// 自底向上调整结点的高度值
        return true;
}
/**
 * 插入结点后调整动作
 * 从节点current自底向上调整结点的高度
 * 直到一个节点在插入e前后其高度值不变 或者 直到更新完根节点停止
 */
void BST::insertAdjust(BSTNode* current,const int&e) {
	while(current != 0) {
		if(current->height == calcHeight(current))
				break;		// 插入e前后高度值没变，则上层结点无需调整
		current->height = calcHeight(current);
		current = current->parent;
	}
}
/**
 * 删除结点后调整动作
 * 从节点current自底向上调整结点的高度
 */
void BST::removeAdjust(BSTNode* current,const int&e) {
	insertAdjust(current,e);		// 默认删除后调整动作与插入后调整动作相同
}
/**
 * 获取结点p的高度
 * 比较p孩子节点高度，取两者最大者加1
 */
int BST::calcHeight(const BSTNode* p) const{
		if(p == 0) return 0;
		if(p->left == 0 && p->right == 0)
			return 1;
		else if(p->left == 0)
			return p->right->height+1;
		else if(p->right == 0)
			return p->left->height+1;
		else
			return std::max(p->left->height,p->right->height)+1;
}
/**
 * 合并删除指针p指向结点
 * 算法思想：
 * case 1:	对于没有孩子的结点，直接删除即可；
 * case 2: 对于只有一个孩子的结点，直接把孩子替换待删除结点即可
 * case3:	对于有两个孩子的结点，将右孩子挂在左孩子树上最右边孩子结点的右指针上
 * 最后释放结点,并调整结点的高度值
 * 注意 使用指针的引用进行修改
 */
void BST::removeByMerging(BSTNode*& p,const int&e){
	toPng(std::string("delete(By merging): ")+p->toString(),p);
	BSTNode *  tmp = p,*prev=p->parent; // tmp保存待释放内存地址 prev结点保存待调整的结点
	if(p->left == 0)		{ 			// 左子树为空
		if(p->right != 0)
			p->right->parent = p->parent;
		p = p->right;
	}
	else if(p->right == 0) {			// 右子树为空
		if(p->left != 0)
			p->left->parent = p->parent;
		p = p->left;
	}
	else {
		tmp = p->left;
		while(tmp->right != 0)	// tmp 临时指向p左孩子中最右边孩子
			 tmp = tmp->right;
		prev = tmp;
		tmp->right = p->right;
		p->right->parent = tmp;
		p->left->parent = p->parent;
		tmp = p;	// tmp 重新指向待释放结点
		p = p->left;
	}
	delete tmp;
	removeAdjust(prev,e);	// 自底向上更新结点的高度值
}
/**
 * 查找并使用合并删除方法删除键值为e的结点
 * 成功删除则返回true,键值不存在时无法删除则返回false
 */
bool BST::findAndRemoveByMerging(const int& e){
	BSTNode *prev = 0;
	BSTNode *current =iterativeSearch(e,prev);
	if(current == 0)
		return false;
	if(prev == 0) {	// 删除根节点
		removeByMerging(root,e);
		root->parent = 0;
	}else if(current == prev->left)
		removeByMerging(prev->left,e);
	else
		removeByMerging(prev->right,e);
	return true;
}
/**
 * 复制删除指针p指向结点
 * 算法思想：
 * case 1:	对于没有孩子的结点，直接删除即可
 * case 2:	对于只有一个孩子的结点，直接把孩子替换待删除结点即可
 * case 3:	对于两个孩子都不为空的结点
 *    首先找p左孩子的最右边结点tmp,tmp结点即为要复制的那个结点
 *    如果p的左孩子没有右孩子，将p的左孩子的左孩子链接到p的left上
 *    否则将tmp的左孩子链接到其父节点right上
 *    将tmp值复制到p中
 * 最后释放结点,并调整结点的高度值
 */
void BST::removeByCopying(BSTNode*& p,const int& e){
	toPng(std::string("delete(By copying): ")+p->toString(),p);
	BSTNode* tmp = p,*prev=p->parent;		// prev指针指向实际删除结点的父节点
	if(p->left == 0)		{ 			// 左子树为空
		if(p->right != 0)
			p->right->parent = p->parent;
		p = p->right;
	}
	else if(p->right == 0) {			// 右子树为空
		if(p->left != 0)
			p->left->parent = p->parent;
		p = p->left;
	}
	else {
		prev = p;		// prev初始为指向待删除结点
        tmp = p->left;
        while(tmp->right != 0) {
        	prev = tmp;
        	tmp = tmp->right;
        }
        if(prev == p) 			// p的左孩子没有右孩子
        	prev->left = tmp->left;
        else
        	prev->right = tmp->left;	// tmp有左孩子则连上，没有也用tmp->left将其父节点right置为空
        if(tmp->left != 0)
        	tmp->left->parent = prev;
        p->key = tmp->key;
	}
	delete tmp;
	removeAdjust(prev,e);	// 自底向上更新结点的高度值
}
/**
 * 复制删除键值为e的结点
 * 删除成功返回true,键值不存在时删除失败返回false
 */
bool BST::findAndRemoveByCopying(const int& e){
	BSTNode *prev = 0;
	BSTNode *current =iterativeSearch(e,prev);
	if(current == 0)
		return false;
	if(prev == 0)
		removeByCopying(root,e);
	else if(current == prev->left)
		removeByCopying(prev->left,e);
	else
		removeByCopying(prev->right,e);
	return true;
}
/**
 * 从有序数组data构造平衡二叉树
 * 递归实现 索引从0计数
 * 算法思想:
 * 1)如果first不大于last,计算first和last的中间值mid,并将mid元素插入树
 * 2)对[first,mid-1],[mid+1,last]两个区间内元素继续递归过程
 */
void BST::balanceTree(int *data,int first,int last){
	if(first <= last) {
		 int mid = (first+last) / 2;
		 insert(data[mid]);
		 balanceTree(data,first,mid-1);
		 balanceTree(data,mid+1,last);
	}
}
/**
 * 释放结点空间
 * 使用后序遍历释放LRV
 */
void BST::clear(BSTNode* p){
	if(p != 0) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
}
/**
 * 查找操作
 * 递归实现
 */
BSTNode* BST::recursiveSearch(BSTNode* p, const int& e) {
	    if(p == 0 || e == p->key)
	    	return p;
    	else if(e < p->key)
    		return recursiveSearch(p->left,e);
    	else
    		return recursiveSearch(p->right,e);
}
/**
 * 查找操作
 * 非递归实现
 * 找到则返回包含键的结点指针，prev键的父节点
 * 否则返回0,prev指向待插入位置的父节点
 */
BSTNode* BST::iterativeSearch(const int& e,BSTNode*&prev) {
	BSTNode* current = root;
	prev = 0;
	while(current != 0 && e != current->key) {
		prev = current;
		if(e < current->key)
			    current = current->left;
		else
			   current = current->right;
	}
	return current;
}
/**
 * 以p->right为支点 左旋转
 * 注意更新指针指向和结点的高度
 * 		p							q
 * 	   /  \ 					   /  \
 * 	  s   q			=> 	  p   qr
 * 	  	  /  \					/  \
 * 	  	 ql   qr			   s    ql
 */
void BST::leftRotate(BSTNode* p) {
	 toPng(std::string("left rotate: ")+p->toString(),p);
	 BSTNode	*q = p->right, *g=p->parent;
	 p->right = q->left;
	 if(q->left != 0)
		 q->left->parent = p;
	 q->left = p;
	 p->parent = q;
     q->parent = g;
     p->height = calcHeight(p);
     q->height = calcHeight(q);
     if(g == 0)
    	 root = q;		// 设置新的根节点
	 else if(p == g->left)
		 g->left = q;
	 else
		g->right = q;
}
/**
 * 以p->left为支点 右旋转
 * 注意更新指针指向和结点的高度
 * 		 p						q
 * 	   /  \					   /  \
 * 	  q    s		=>  	  ql   p
 * 	 /  \						   /  \
 * 	ql  qr  					  qr  s
 */
void BST::rightRotate(BSTNode* p) {
	toPng(std::string("right rotate: ")+p->toString(),p);
	BSTNode* q = p->left,*g=p->parent;
	p->left = q->right;
	if(q->right != 0)
		q->right->parent = p;
	q->right = p;
	p->parent = q;
	q->parent = g;
	p->height = calcHeight(p);
	q->height = calcHeight(q);
	if(g == 0)
		root = q;
	else if(p == g->left)
		g->left = q;
	else
		g->right = q;
}
/**
 * 转换为图片
 * desp为描述内容
 * pcur为当前结点指针
 */
void BST::toPng(const std::string &desp,const BSTNode* pcur) const{
	if(bwritePng) {
		BiTreePrinter::toPng(this,desp,pcur);
	}
}
