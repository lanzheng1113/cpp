/*
 * AVLTree.cpp
 *
 *  Created on: 2014年12月4日
 *      Author: wangdq
 */

#include "AVLTree.h"
#include <algorithm>

template<typename T,typename V>
void  AVLTree<T,V>::clear(AVLNode<T,V>* p){
     if(p != 0) {
    	 clear(p->left);
    	 clear(p->right);
    	 delete p;
     }
}

template<typename T,typename V>
void AVLTree<T,V>::inorderTraverse(){
	 inorder(root);
}
template<typename T,typename V>
void AVLTree<T,V>::inorder(AVLNode<T,V>* p) {
	 if ( p != 0) {
		 inorder(p->left);
		 visit(p);
		 inorder(p->right);
	 }
}
/**
 * 递归删除节点e
 * 返回false,代表插入失败
 * 返回true,代表插入成功
 *
 * 这里删除节点情况有3种:
 * 1)节点没有孩子时，直接删除
 * 2)节点仅有一个孩子，删除该节点，病把孩子节点接上
 * 3)节点有两个孩子时，总是从左孩子节点选取最大元素值拷贝到删除节点,然后从左子树继续删除
 *
 *  删除节点后，先自行调整；然后递归回到上层节点处，由上层节点接着调整
 */
template<typename T,typename V>
bool AVLTree<T,V>::deleteByCopying(AVLNode<T,V>*&p,const T& e) {
	  AVLNode<T,V>* tmp = p;
      if(p == 0) {
    	  return false; //删除失败
      }
      if(e == p->key) {  //删除节点
    	   if(p->left == 0) {
    		    p = p->right;
    		    delete tmp;
    	   }else if(p->right == 0) {
    		   p = p->left;
    		   delete tmp;
    	   }else {
                  AVLNode<T,V> *leftMax = p->left;
                  while(leftMax->right != 0) {
                	    leftMax = leftMax->right;
                  }
                  p->key = leftMax->key;
                  p->value = leftMax->value;
                  /*
                   * 注意,这里不立即修改指针和删除leftMax节点
                   * 而是让递归继续，在p的左子树上继续删除e
                   * 这样做的好处就是不用我们手动的从previous节点到p节点来调整许多不平衡点
                   * 而是在函数递归返回的时候，让其统一调整
                   *  初始 previous = p
                   *
                  if(previous == p) {
                	    p->left = leftMax->left;
                  }else {
                	   previous->right = leftMax->left;
                  }
                  delete leftMax;
                  */
                  deleteByCopying(p->left,leftMax->key); // 再次调用该函数，删除leftMax节点
    	   }
      }else if (e < p->key) {
    	     bool ret = deleteByCopying(p->left,e); // 尝试从左边删除
    	     if(!ret) return false; // 如果删除失败，则不进行任何调整
             if(height(p->right)-height(p->left) == 2) {
            	   if(height(p->right->left) > height(p->right->right) ) {  // RL
            		       rightRotate(p->right);
            		       leftRotate(p);
            	   }else {  // RR
            		   leftRotate(p);
            	   }
             }
      }else if(e > p->key) {
    	  bool ret = deleteByCopying(p->right,e);// 尝试从右边删除
    	  if(!ret)  return false; // 如果删除失败，则不进行任何调整
          if(height(p->left)-height(p->right) == 2) {
        	         if(height(p->left->left) > height(p->left->right) ){   // LL
        	        	     rightRotate(p);
        	         }else {  // LR
        	        	     leftRotate(p->left);
        	        	     rightRotate(p);
        	         }
          }
      }
      return true;
}
template<typename T,typename V>
void AVLTree<T,V>::insert(const T & e,const V& v){
	bool adjusted = false;
	insert(root,e,v,adjusted);
}
/**
 * 递归插入元素e
 * 每次利用递归求解树的高度(不保存树高度,总是实时计算)
 * adjusted为调整标志,初始为false,每次都是调整离插入节点最近的失去平衡的树
 * 调整一次后adjusted = true，上方的父节点不再需要调整
 *
 */
template<typename T,typename V>
bool AVLTree<T,V>::insert(AVLNode<T,V>* &p,const T & e,const V& v,bool &adjusted){
       if(p == 0) {
    	       p = new AVLNode<T,V>(e,v);  //找到插入位置，则直接插入
    	       adjusted = false;
    	       return true;
       }else if(e == p->key) {
    	     return false; // 不重复插入
       }else if(e < p->key) {
    	   bool ret = insert(p->left,e,v,adjusted);  //尝试从左边插入
    	   if(!ret)  return ret;
    	   if(!adjusted && height(p->left)-height(p->right) == 2) {
    		    if(e < p->left->key)   {  //LL
                          rightRotate(p);
    		    }else {   //LR
                         leftRotate(p->left);
                         rightRotate(p);
    		    }
    		    adjusted = true;
    	   }
       }else {
    	   bool ret = insert(p->right,e,v,adjusted); //尝试从右边插入
    	   if(!ret)  return ret;
    	   if(!adjusted && height(p->right)-height(p->left) == 2) {
    		     if(e < p->right->key)  {  // RL
    		    	   rightRotate(p->right);
    		    	   leftRotate(p);
    		     }else {   // RR
    		    	 leftRotate(p);
    		     }
    		     adjusted = true;
    	   }
       }
       return true;
}

template<typename T,typename V>
bool AVLTree<T,V>::FindAndDelete(const T&e){
	 return deleteByCopying(root,e);
}
template<typename T,typename V>
int  AVLTree<T,V>::height() {
	return height(root);
}

template<typename T,typename V>
int AVLTree<T,V>::height(AVLNode<T,V> *p) {
	 if (p == 0) {
		  return 0;
	 }
     return 1+ std::max(height(p->left),height(p->right));
}
/**
 * 对p为根的节点进行右旋处理,处理完毕p指向新的树根
 */
template<typename T,typename V>
void AVLTree<T,V>::leftRotate(AVLNode<T,V>* &p) {
       AVLNode<T,V>* rc = p->right;
       p->right = rc->left;
       rc->left = p;
       p = rc;
}
/**
 * 对p为根的节点进行左旋处理,处理完毕p指向新的树根
 */
template<typename T,typename V>
void AVLTree<T,V>::rightRotate(AVLNode<T,V>* &p) {
	AVLNode<T,V>* lc = p->left;
	p->left = lc->right ;
	lc->right = p;
	p = lc;
}

template<typename T,typename V>
bool AVLTree<T,V>::isEmpty() {
	  return root == 0;
}
