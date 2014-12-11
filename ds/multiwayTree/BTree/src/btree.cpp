/*
 * btree.cpp
 *
 *  Created on: 2014年12月9日
 *      Author: wangdq
 */

#include "btree.h"
#include <iostream>
#include <queue>          // std::queue

template<typename T,int M>
BTree<T,M>::~BTree() {
	clear(root);
}
/**
 *  插入元素e
 */
template<typename T,int M>
void BTree<T,M>::insert(const T& e) {
	  //获取插入位置
	  BTreeNode<T,M> * p ,* node1,*node2;
	  int index;
	  T k;
	  // 为空则直接加入
	  if(root == 0) {
		    root = new BTreeNode<T,M>(e);
		    return;
	  }
	  bool ret = getInsertPos(e,p,index);
	  if(!ret)
		  return;	//键已经存在则直接返回
       //插入p节点i所指位置
	  	for(int j = p->keynum-1; j >= index;j--)
	  		  p->keys[j+1] = p->keys[j];
	  	p->keys[index] = e;
	    p->keynum++;

      //判断是否需要分裂
	 while(p->keynum > MAX_KEY_NUM) {
		 	 k = p->keys[p->keynum / 2]; // 获取中间值
		 	 //分裂成两个节点
		 	 node1 = node2 = 0;
		     splitNode(p,node1,node2);
		     BTreeNode<T,M> * parent = p->parent;
             if(parent == 0) {		// p是根节点
            	     root = new BTreeNode<T,M>(k);
            	     root->ptr[0] = node1;
            	     node1->parent = root;
            	     root->ptr[1] = node2;
            	     node2->parent = root;
            	     return;
             }else {
            	     int i;
            	     //在父节点中找中间值的插入位置
            	     for( i = 0; i < parent->keynum && parent->keys[i] < k;++i);
            	    //移动父节点的元素和指针
            	 	for(int j = parent->keynum-1; j >= i;j--) {
            	 		parent->keys[j+1] = parent->keys[j];
            	 		parent->ptr[j+2] = parent->ptr[j+1];
            	 	}
            	 	parent->keys[i] = k;
            	 	parent->ptr[i+1] = node2;
            	 	node2->parent = parent;
            	 	parent->keynum++;
            	 	p = parent; // 父节点成为继续判断的节点
             }
	 }
}
/**
 * 获取键e插入节点和在该节点的插入位置索引
 * 如果键e已经存在则返回false
 * 否则返回true,并设置为需要插入的位置节点和索引
 */
template<typename T,int M>
bool BTree<T,M>::getInsertPos(const T&e,BTreeNode<T,M>*&p,int &index) {
	  BTreeNode<T,M> *pcur = root,*parent=root;
	  while( pcur != 0) {
			for(index=0;index < pcur->keynum && pcur->keys[index] < e;++index);

			if(index == pcur->keynum || pcur->keys[index] > e) {
					parent = pcur;
					pcur = pcur->ptr[index]; // 继续在下层查找
			}
			else {
				 return false; // 键已经存在
			}
	  }
	  p = parent; // 需要插入位置的节点
	  return true;
}
/**
 * 分割节点node为node1和node2
 */
template<typename T,int M>
void BTree<T,M>::splitNode(BTreeNode<T,M>*p,BTreeNode<T,M>*&node1,BTreeNode<T,M>*&node2) {
	int mid = p->keynum / 2;
	node1 = p;
	node2 = new BTreeNode<T,M>();
	//拷贝元素到node2
   for(int i = mid+1; i < p->keynum;i++) {
	     node2->keys[node2->keynum] = p->keys[i];
	     if(p->ptr[i] != 0)
	    	 p->ptr[i]->parent = node2;		//注意重新设置父节点指向
	     node2->ptr[node2->keynum] = p->ptr[i];
	     node2->keynum++;
   }
   node2->ptr[node2->keynum] = p->ptr[p->keynum];
   if(p->ptr[p->keynum] != 0)
	   p->ptr[p->keynum]->parent = node2;
   //node1中数据减半
   node1->keynum = mid;
}
template<typename T,int M>
void BTree<T,M>::remove(const T&e) {
	  BTreeNode<T,M>* p = search(root,e);
	  if(p == 0)
		  return;	// 不存在键e则直接返回
	  remove(p,e);
}
/**
 * 从节点p移除键e
 */
template<typename T,int M>
void BTree<T,M>::remove(BTreeNode<T,M>*p,const T&e) {
	    if(p == 0)
	    	 return;
	    int index =0;
	    for(;index < p->keynum && p->keys[index] < e;index++); // 键e在p中的索引
        if(p->ptr[0] != 0) {   // 非叶子节点删除
        	  //找出最大前驱
        	  BTreeNode<T,M>* q = p->ptr[index];
              while(q->ptr[q->keynum] != 0)
            	        q = q->ptr[q->keynum];
              T preMax = q->keys[q->keynum-1];
              p->keys[index] = preMax;
              remove(q,preMax);	// 转换为从叶子节点删除preMax键
        }else {
        	//先移除键e
        	for(int i= index+1;i < p->keynum;i++)
        		  p->keys[i-1] = p->keys[i];
            p->keynum--;
            while(p->parent != 0 && p->keynum < MIN_KEY_NUM) {  // 删除后键数目下溢
            	    BTreeNode<T,M>* left,*right,*parent = p->parent;
            		bool ret = getProperSibling(p,left,right);
            		if(ret) {		// 如果存在同级节点有足够多键
            			joinAndSplitNode(parent,left,right);
            			return;
            		}else if (parent->parent == 0){		// 父节点是根节点
                            if(parent->keynum == 1) {
                            	joinAndRemoveNode(parent,left,right);
                            	root = left;
                            	root->parent = 0;
                            }
                            else {
                            	joinAndRemoveNode(parent,left,right);
                            }
                            return;
            		}else {
            			joinAndRemoveNode(parent,left,right);
            			p = parent; // 继续进行判断
            		}
            }
        }
}
/**
 * 合并parent中中间值k，以及node1和node2然后再重新划分node1,k,node2
 */
template<typename T,int M>
void BTree<T,M>::joinAndSplitNode(BTreeNode<T,M>*parent,BTreeNode<T,M>*left,BTreeNode<T,M>*right) {
	int index=0;
    for(;index < parent->keynum && parent->keys[index] < left->keys[left->keynum-1] ;++index); // 找出parent中划分left,right的中间值
    if(left->keynum < right->keynum) {											// right向left输送
    	    left->keys[left->keynum] =  parent->keys[index]; 				// 将划分left,right的中间值放到left中
    	    left->keynum++;
    	    parent->keys[index] = right->keys[0]; 						// 将right中第一个值复制到父节点中
    	    left->ptr[left->keynum] = right->ptr[0];
    	    if(right->ptr[0] != 0) right->ptr[0]->parent = left;
    	    for(int j=1;j < right->keynum;j++) {							// 移动right中元素，重新排列
    	    	 right->keys[j-1] = right->keys[j];
    	    	 right->ptr[j-1] = right->ptr[j];
    	    }
    	    right->ptr[right->keynum-1] = right->ptr[right->keynum];
    	    right->keynum--;
    }else {			// left向right输送
           for(int j=0;j< right->keynum;++j) {
        	     right->keys[j+1] = right->keys[j];
        	     right->ptr[j+2] = right->ptr[j+1];
           }
           right->ptr[1] = right->ptr[0];
           right->keys[0] = parent->keys[index];
           right->ptr[0] = left->ptr[left->keynum];
           if(right->ptr[0] != 0) right->ptr[0]->parent = right;
           right->keynum++;
           T tmp = left->keys[left->keynum-1];
           parent->keys[index] = tmp;
           left->keynum--;
    }
}
/**
 * 合并parent中中间值k,以及node1和node2，然后合并成node1,删除node2
 */
template<typename T,int M>
void BTree<T,M>::joinAndRemoveNode(BTreeNode<T,M>*parent,BTreeNode<T,M>*left,BTreeNode<T,M>*right) {
		int index=0;
		for(;index < parent->keynum && parent->keys[index] < left->keys[left->keynum-1] ;++index); // 找出parent中划分left,right的中间值
		 left->keys[left->keynum] =  parent->keys[index]; // 将划分left,right的中间值放到left中
		 left->keynum++;
		for(int j=0;j < right->keynum;j++) {
			left->keys[left->keynum] = right->keys[j]; // 移动right中元素到left节点
			left->ptr[left->keynum] = right->ptr[j];	// 注意指针也要移动过来
			if(right->ptr[j] != 0)  right->ptr[j]->parent = left;
			left->keynum++;
	   }
	   left->ptr[left->keynum] = right->ptr[right->keynum];
	   if(right->ptr[right->keynum] != 0)  right->ptr[right->keynum]->parent = left;
	   //释放right节点
	   parent->ptr[index+1] = 0;
	   delete right;
       //调整parent节点的键和指针分布
	  for(int j=index+1;j < parent->keynum;++j) {
		      parent->keys[j-1] = parent->keys[j];
		      parent->ptr[j] = parent->ptr[j+1];
	  }
	  parent->keynum--;
}
/**
 * 获取p节点在内的两个同级节点
 * 同级节点以left,right形式返回
 * 如果键数目大于MIN_KEY_NUM的同级节点则返回true
 * 否则返回false
 */
template<typename T,int M>
bool BTree<T,M>::getProperSibling(BTreeNode<T,M>*p,BTreeNode<T,M>*&left,BTreeNode<T,M>*&right) {
	BTreeNode<T,M>* parent = p->parent;
	int i=0;
	left = p; //默认p节点为左边同级节点
	for(;i < parent->keynum+1 && parent->ptr[i] != p ;i++);  // 获取p在父节点中索引
	if( i == parent->keynum) {				// 最后一个孩子
		left = parent->ptr[parent->keynum-1];
		right = p;
	}else if(i == 0) {					// 第一个孩子
		 right = parent->ptr[1];
	}else {							// 中间孩子，可以选择左边或右边同级节点
		right = parent->ptr[i+1];
		if(parent->ptr[i+1]->keynum > MIN_KEY_NUM)
			right = parent->ptr[i+1];
		else if(parent->ptr[i-1] ->keynum > MIN_KEY_NUM) {
			left = parent->ptr[i-1];
			right = p;
		}
	}
    return left->keynum > MIN_KEY_NUM || right->keynum >MIN_KEY_NUM ;
}
template<typename T,int M>
void BTree<T,M>::orderedTraverse() {
	traverse(root);
	std::cout<<std::endl;
}
template<typename T,int M>
BTreeNode<T,M>* BTree<T,M>::search(const T&e) {
	return search(root,e);
}
template<typename T,int M>
BTreeNode<T,M>* BTree<T,M>::search(BTreeNode<T,M>*p,const T&e) {
	if( p == 0)
		 return 0;
	int i = 0;
	for(; i < p->keynum ;++i)
		  if(p->keys[i] >= e)
			    break;
	if(i == p->keynum || p->keys[i] > e)
		return search(p->ptr[i],e); // 继续在子节点上查找
	else
		return p;  // 查找成功
}
template<typename T,int M>
void BTree<T,M>::clear(BTreeNode<T,M>* p) {
	if(p != 0) {
		   for(int i= 0;i < p->keynum;++i)
			   clear(p->ptr[i]);						// 清除子节点
		   if(p->keynum > 0)
			   clear(p->ptr[p->keynum]); // 清除最后一个指针
		   delete p;	// 清除自身空间
	}
}

template<typename T,int M>
void  BTree<T,M>::traverse(BTreeNode<T,M>* p) {
	if(p != 0) {
		  for(int i=0;i < p->keynum;++i) {
			  traverse(p->ptr[i]);					// 先访问比键小的节点
              std::cout<<p->keys[i]<<"\t";				// 访问这个键
		  }
		  traverse(p->ptr[ p->keynum]); // 访问比最后一个大的节点
	}
}
template<typename T, int M>
void BTree<T,M>::breadFirstTraverse() {
	std::queue<BTreeNode<T,M>*> queue;
	if(root == 0)
		   return;
	queue.push(root);
	while(!queue.empty()) {
		BTreeNode<T,M>* p = queue.front();
		queue.pop();
		std::cout<<"[ ";
		for(int i=0;i< p->keynum;i++) {
			std::cout<<p->keys[i]<<" ";
			if(p->ptr[i] != 0)
					queue.push(p->ptr[i]);
		}
		std::cout<<" ]";
	    if(p->ptr[p->keynum] != 0)
	    	queue.push( p->ptr[p->keynum] );
	}
	std::cout<<std::endl;
}

