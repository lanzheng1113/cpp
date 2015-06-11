/*
 * btree.cpp
 *
 *  Created on: 2015年5月22日
 *      Author: wangdq
 */
#include <iostream>
#include <queue>
#include "btree.h"
/**
 * 插入键e
 * 插入成功返回true,已经存在则插入失败返回false
 * 算法思想:
 * 1)树为空，则插入e为根节点并返回true,其他情况则继续
 * 2)找到要插入的结点node和位置pos,如果已经包含键e则插入失败，返回false
 * 3)在插入结点node中插入e,并检测插入位置键数量是否上溢(overflow)
 *     如果没有上溢则返回
 * 	否则，分解当前节点，并将中间值k和分解的右分支sright,继续插入到父节点中去(为根节点则创建新的根)
 * 4)重复3的过程直到node结点为根或者不在上溢为止
 */
template<typename T,int M>
bool BTree<T,M>::insert(const T&e) {
	if(root == 0) {
		root = new BTreeNode<T,M>(e,0);
		return true;
	}
	BTreeNode<T,M>* sright=0,* p = root;
	int pos = -1;
	T k = e;
	bool ret = search(e,p,pos);
	if(ret)
		return false;	// 已经存在键e则返回
	while(p != 0) {
		    insert(p,pos,k,sright);
		    if(p->keynum <= MAX_KEY_NUM)
		    	break;
		    else {	// 插入键k后上溢
		    		splitNode(p,k,sright);	// 切分结点p
		    	    if(p->parent == 0) {		// 重构根节点
		    	    	root = new BTreeNode<T,M>(k,0);
		    	    	root->childs[0] = p;
		    	    	p->parent = root;
		    	    	root->childs[1] = sright;
		    	    	sright->parent = root;
		    	    	root->isLeaf = false;
		    	    	break;
		    	    }else {
		    	    	 p = p->parent;
		    	    	 pos = searchInNode(p,k);
		    	    }
		    }
	}
	return true;
}
/**
 * 在结点p中位置i处插入键k，并且键k右侧链接sright
 */
template<typename T,int M>
void BTree<T,M>::insert(BTreeNode<T,M>*p , int pos, const T&k, BTreeNode<T,M>* sright) {
	rightShiftElements(p,pos,false);
	if(sright != 0)
		sright->parent = p;
	p->keys[pos] = k;
	p->childs[pos+1] = sright;
	p->keynum++;
}
/**
 * 将结点p划分为两个节点
 * k保存结点p的中间值
 * sright保存新生成的结点
 */
template<typename T,int M>
void BTree<T,M>::splitNode(BTreeNode<T,M>*p, T&k,BTreeNode<T,M>*& sright) {
	int midPos = p->keynum / 2;
	k = p->keys[midPos];
	sright = new BTreeNode<T,M>();
	copyElements(sright,0,p,midPos+1);		// 复制到新建节点中
	sright->keynum = p->keynum-midPos-1;
	p->keynum = midPos;		// 复制完毕后设置p的键数目
	if(!p->isLeaf)
		sright->isLeaf = false;	// 非叶子节点划分  两个孩子都为非叶子结点
}
/**
 * 删除键e
 * 删除成功则返回true,不包含键e则删除失败返回false
 * 算法思想:
 * 1)找到要包含键e的节点node,找不到则返回false
 * 2)case 0 : node是非叶节点，则使用复制删除，node的前驱当做叶子处理
 *    删除叶子节点中键e
 *    case 1: node是根节点作为叶子节点删除时，则退出(当根节点键数目为0时，根设为空)
 * 3)case 2: node键数大于等于下限 则退出
*     case 3: node键数等于下限,同级节点键数大于下限,则重新分配键值,退出
*     case 4: node键数等于下限,同级节点键数等于下限,则合并键值到node
*    			  如果父节点为根节点，退出(当父节点键值为1个，则重建根节点)
* 				  否则将父节点作为node，重复3
 */
template<typename T,int M>
bool BTree<T,M>::remove(const T&e) {
	BTreeNode<T,M>* p = 0;
	int pos = -1;
	bool ret = search(e,p,pos);
	if(!ret)
		return false;
	if(!p->isLeaf)		{	// case 0  寻找前驱 复制删除
		BTreeNode<T,M> * pred = p->childs[pos];
		while(pred->childs[pred->keynum] != 0)
				 pred = pred->childs[pred->keynum];
		p->keys[pos] = pred->keys[pred->keynum-1];	// 前驱键值复制到待删除键位置
		p = pred;
		pos = p->keynum-1;
	 }
	 removeInleaf(p,pos);	// 叶子中删除
	 if(p == root) {		// case 1 如果根节点作为叶子删除
	 	if(root->keynum == 0) {
			 delete root;
			 root = 0;
	 	}
	 	return true;
	 }
	 bool bfinished = false;
	 int curIndex = 0,sibIndex=0;
	 while(!bfinished) {
		 if(p->keynum >= MIN_KEY_NUM)	 	// case 2
			 	 break;
		 getProperSibling(p,curIndex,sibIndex);	// 获取合适的同级节点
		 if(p->parent->childs[sibIndex]->keynum > MIN_KEY_NUM) {	// case 3
			 reallocKeys(p->parent,curIndex,sibIndex);
			 bfinished = true;
		 }else {
			 mergeNode(p->parent,curIndex,sibIndex);		// case 4
			 if(p->parent == root)  {
				 bfinished = true;
				 if(root->keynum == 0) {
					 delete root;
					 root = p;	// 重建根结点
					 root->parent = 0;
				 }
			 }else
				 p = p->parent;
		}
	 }
	 return true;
}
/**
 * 获取current结点合适的兄弟节点
 * 优先获取键值数目多的右兄弟节点
 */
template<typename T,int M>
void BTree<T,M>::getProperSibling(BTreeNode<T,M>*current,int &curIndex, int &sibIndex) {
	BTreeNode<T,M>* parent = current->parent;
	for(curIndex = 0; curIndex<= parent->keynum;++curIndex)
		if(parent->childs[curIndex] == current)
			break;
	if(curIndex == parent->keynum)		//  最后一个孩子
		sibIndex = curIndex-1;
	else if(curIndex == 0)		// 第一个孩子
		sibIndex = curIndex+1;
	else if(parent->childs[curIndex+1]->keynum  >=  parent->childs[curIndex-1]->keynum)
			sibIndex = curIndex+1;
	else
		sibIndex = curIndex-1;
}
/**
 * 合并parent节点的sibIndex所指孩子到curIndex所指孩子中
 * parent中划分两个孩子的键也合并到curIndex所指孩子中
 * 合并节点时优先选择右兄弟合并 因为若是左兄弟则当前节点移动元素次数过多
 */
template<typename T,int M>
void BTree<T,M>::mergeNode(BTreeNode<T,M>*parent,int curIndex,int sibIndex) {
	BTreeNode<T,M> *cur = parent->childs[curIndex], *sib = parent->childs[sibIndex];
	if(curIndex < sibIndex) {	// sibIndex为右兄弟	优先选择右兄弟合并
		cur->keys[cur->keynum] = parent->keys[curIndex];
		cur->keynum++;
		copyElements(cur,cur->keynum,sib,0);	// sib键值和孩子指针复制到cur中
		if(curIndex+1 < parent->keynum)
			leftShiftElements(parent,curIndex+1,false);	// parent键值和孩子指针左移
		parent->keynum--;
	}else {		// sibIndex为左兄弟  合并时优先右兄弟  则cur为parent最后一个孩子
		rightShiftElements(cur,0,true,MAX_KEY_NUM-cur->keynum);// cur中结点后移
		cur->keys[MAX_KEY_NUM-cur->keynum-1] = parent->keys[sibIndex];
		cur->keynum++;
		parent->keynum--;
		copyElements(cur,0,sib,0);
		if(parent->keynum > 0)
			parent->childs[parent->keynum] = cur;	// cur成为parent最后一个孩子
	}
	cur->keynum = MAX_KEY_NUM;
	delete sib;	// 释放同级节点
}
/**
 * 在节点parent的两个索引所指向的孩子之间重新分配键值
 * 注意维护孩子指针
 */
template<typename T,int M>
void BTree<T,M>::reallocKeys(BTreeNode<T,M> *parent, int curIndex, int sibIndex) {
	BTreeNode<T,M> *cur = parent->childs[curIndex], *sib = parent->childs[sibIndex];
	if(curIndex < sibIndex) {	// sibIndex为右兄弟
		cur->keys[cur->keynum] = parent->keys[curIndex];		// 下放父节点中划分两个孩子的中间键
		cur->keynum++;
		cur->childs[cur->keynum] = sib->childs[0];	// 同级节点的第一个孩子作为cur的最后一个孩子
		if(sib->childs[0] != 0)
			sib->childs[0]->parent = cur;
		parent->keys[curIndex] = sib->keys[0];
		leftShiftElements(sib,1,true);	// 右边兄弟的键和指针左移一个单位
		sib->keynum--;
	}else {	// sibIndex为左兄弟
		rightShiftElements(cur,0,true);		// 当前节点键和孩子指针右移
		cur->keys[0] = parent->keys[sibIndex];		// 父节点划分的中间值下放到cur中
		cur->keynum++;
		cur->childs[0] = sib->childs[sib->keynum];	// 同级节点最后一个孩子连接到cur作为第一个孩子
		if(sib->childs[sib->keynum] !=0 )
			sib->childs[sib->keynum]->parent = cur;
		parent->keys[sibIndex] = sib->keys[sib->keynum-1];	// sib中选取最大值作为中间值放到父节点
		sib->keynum--;
	}
}
/**
 * 从叶子节点leaf中删除pos位置键
 */
template<typename T,int M>
void BTree<T,M>::removeInleaf(BTreeNode<T,M>*leaf,int pos) {
	for(int i=pos+1; i< leaf->keynum;++i)
		 leaf->keys[i-1] = leaf->keys[i];		// 移动元素
	--leaf->keynum;
}
/**
 * 有序遍历
 */
template<typename T,int M>
void BTree<T,M>::orderedTraverse(std::ostream&outstream) const{
	if(root == 0) {
		outstream.setstate(std::ostream::eofbit | std::ostream::failbit);		// 读取结束
		return;
	}
	orderTraverse(root,outstream);
	outstream << std::endl;
}
/*
 * 广度优先遍历
 * 仅用于调试
 */
template<typename T,int M>
void BTree<T,M>::breadthFirstTraverse() const{
	if(root == 0) {
		std::cout << "Empty Tree" << std::endl;
		return;
	}
	std::queue<BTreeNode<T,M>*> nodeQueue;
	nodeQueue.push(root);
	while(!nodeQueue.empty()) {
		BTreeNode<T,M>* current = nodeQueue.front();
		nodeQueue.pop();
		if(current != 0) {
			std::cout <<"( ";
			for(int i=0;i < current->keynum;++i) {
				std::cout << current->keys[i] << "\t";
				if(!current->isLeaf)	nodeQueue.push(current->childs[i]);
			}
			if(!current->isLeaf) nodeQueue.push(current->childs[current->keynum]);
			std::cout <<")" << std::endl;
		}
	}
}
/**
 * 搜索键e
 * 如果找到包含e的结点，则返回包含e的结点
 * 否则返回0
 */
template<typename T,int M>
BTreeNode<T,M> *  BTree<T,M>::search(const T&e) {
	BTreeNode<T,M>* p = 0;
	int pos = -1;
	bool ret = search(e,p,pos);
	if(ret)
		return p;
	else
		return 0;
}
/**
 * 搜索键值e
 * 搜索成功返回true,失败返回false
 * 搜索成功时node返回包含键值的节点和位置
 * 搜索失败时返回e应该插入的节点和位置
 */
template<typename T,int M>
bool BTree<T,M>::search(const T&e,BTreeNode<T,M> *&node,int &pos) {
	node = root;
	bool found = false;
	while( node != 0 && !found) {
		   pos = searchInNode(node,e);
		   if(node->keys[pos] == e )		// 找到
			   found = true;
		   else if(node->childs[pos] != 0)	// 继续找
			   node = node->childs[pos];
		   else
			   break;		// 未找到
	}
	return found;
}
/**
 * 在结点node中搜索键值k
 * 返回第一个大于等于k的索引
 * 如果不存在大于等于k的索引则返回node结点的数目
 */
template<typename T,int M>
int  BTree<T,M>::searchInNode(BTreeNode<T,M> *node,const T&k) {
	int i = 0;
	for(; i < node->keynum && node->keys[i] < k;++i);
	return i;
}
/**
 * 析构函数
 * 释放节点空间
 */
template<typename T,int M>
BTree<T,M>::~BTree() {
	clear(root);
}
/**
 * 递归释放空间
 */
template<typename T,int M>
void BTree<T,M>::clear(BTreeNode<T,M>*p) {
	if(p != 0) {
		for(int i=0; i< p->keynum ;++i)
			clear(p->childs[i]);
		delete  p;
	}
}
/**
 * 有序递归遍历
 */
template<typename T,int M>
void BTree<T,M>::orderTraverse(const BTreeNode<T,M>*p,std::ostream& outstream) const {
	if(p != 0) {
		for(int i=0; i < p->keynum;++i) {
			orderTraverse(p->childs[i],outstream);
			outstream << p->keys[i] << "\t";
		}
		orderTraverse(p->childs[p->keynum],outstream);
	}
}
/**
 * 将srcNode节点中srcIndex开始到末尾的键和孩子指针复制到desNode中desIndex开始的位置
 * 从srcIndex开始从左往右复制
 */
template<typename T,int M>
void BTree<T,M>::copyElements(BTreeNode<T,M> *desp,int desIndex,BTreeNode<T,M>* srcp,int srcIndex) {
	  for(; srcIndex < srcp->keynum ;++srcIndex,++desIndex) {
			      desp->keys[desIndex] = srcp->keys[srcIndex];
			      desp->childs[desIndex] = srcp->childs[srcIndex];
			      if(desp->childs[desIndex] != 0)
			    	  desp->childs[desIndex]->parent = desp;
		}
	   desp->childs[desIndex] = srcp->childs[srcp->keynum];
		if(desp->childs[desIndex] != 0)
			 desp->childs[desIndex] ->parent = desp;
}
/**
 * 将 p中从index到末尾的键和孩子指针向左移动一个单位
 * withIndexLeftChild为真则index左侧指针也移动
 */
template<typename T,int M>
void BTree<T,M>::leftShiftElements(BTreeNode<T,M> *p,int index,bool withIndexLeftChild) {
	   if(index >= p->keynum)
		   return;
	   if(withIndexLeftChild) {	// 从index左侧指针开始复制
		   for(;index < p->keynum;++index) {
		   		     p->keys[index-1] = p->keys[index];
		   		     p->childs[index-1] = p->childs[index];
		   	}
		   	p->childs[p->keynum-1] = p->childs[p->keynum];
	   }else {		// 从index右侧指针开始复制
		   for(;index < p->keynum;++index) {
					 p->keys[index-1] = p->keys[index];
					 p->childs[index] = p->childs[index+1];
		   	}
	   }
}
/**
 *  将p中从index到末尾的键值和孩子指针向右移动step个单元 默认移动一个单元
 *  空出index号键
 *  withIndexLeftChild为true则index左侧孩子指针也移动
 */
template<typename T,int M>
void BTree<T,M>::rightShiftElements(BTreeNode<T,M> *p,int index,bool withIndexLeftChild,int step) {
	 for(int i = p->keynum-1; i >=index; --i) {
		  p->keys[i+step] = p->keys[i];
		  p->childs[i+1+step] = p->childs[i+1];
	 }
     if(withIndexLeftChild)
    	 p->childs[index+step] = p->childs[index];
}
