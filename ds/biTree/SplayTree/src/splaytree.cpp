/*
 * splaytree.cpp
 *
 *  Created on: 2014年12月7日
 *      Author: wangdq
 */
#include "splaytree.h"

template<typename T,typename V>
bool SplayTree<T,V>::insert(const T&k,const V&v) {
	 SplayTreeNode<T,V>* p = root,*parent = root;
	 if(root == 0) {
		 root = new SplayTreeNode<T,V>(k,v);
		 return true;// 树为空，则直接添加 ，返回true
	 }
	 while(p != 0) {
		   if(k == p->key)
			     return false; //重复添加，则直接返回false
		  parent = p;
		  if( k < p->key) {
			    p = p->left;
		   }else {
			   p = p->right;
		   }
	 }
     if(k < parent->key)
        parent->left = new SplayTreeNode<T,V>(k,v,parent);//左边插入
     else
    	parent->right = new SplayTreeNode<T,V>(k,v,parent);
     return true;
}
template<typename T,typename V>
void SplayTree<T,V>::inorder() {
	inoder(root);
	std::cout<<std::endl;
}
template<typename T,typename V>
void SplayTree<T,V>::preorder() {
	preorder(root);
	std::cout<<std::endl;
}

template<typename T,typename V>
void SplayTree<T,V>::inoder(SplayTreeNode<T,V>* p) {
      if(p != 0) {
    	  inoder(p->left);
    	  visit(p);
    	  inoder(p->right);
      }
}
template<typename T,typename V>
void SplayTree<T,V>::preorder(SplayTreeNode<T,V>* p) {
      if(p != 0) {
    	  visit(p);
    	  preorder(p->left);
    	  preorder(p->right);
      }
}
/**
 * 查找指定键的元素
 * 找到则将v设置为所查找元素的值，并展开该节点，返回true
 * 否则展开所查找节点的父节点,返回false
 */
template<typename T,typename V>
bool SplayTree<T,V>::search(const T& k,V& v) {
	SplayTreeNode<T,V>* p = root,*parent=root;
	while(p != 0) {
		   parent = p;
		   if(k == p->key) {
			     v = p->value;
			     splay(p); //搜索如果找到节点则展开该节点
			     return true;
		   }else if( k < p->key) {
			   p = p->left;
		   }else {
			   p = p->right;
		   }
	}
	splay(parent);//搜索不到则展开所查找节点的父节点
	return false;
}
/**
 * 展开树节点
 */
template<typename T,typename V>
void SplayTree<T,V>::splay(SplayTreeNode<T,V>* p) {
       while( p != root) {
    	       if( p->parent == root) {   // p节点父节点即为根节点，执行zig操作
    	    	    p = zig1(p); // 更新p为在中的新位置
    	       }else {
    	    	   p = zig2(p);
    	       }
       }
}
/**
 * p节点父节点即为root,执行zig操作
 */
template<typename T,typename V>
SplayTreeNode<T,V>* SplayTree<T,V>::zig1(SplayTreeNode<T,V>*p) {
    if(p == p->parent->left) { // L型
    	root = rightRotate(root);
    }else {
    	root = leftRotate(root); // R型
    }
    return root;
}
/**
 * p节点父节点不是root,p--parent-grandParent进行调整
 * topParent保存的是grandParent的父节点
 * tmpRoot保存调整后新子树的根
 */
template<typename T,typename V>
SplayTreeNode<T,V>* SplayTree<T,V>::zig2(SplayTreeNode<T,V>* p){
	 SplayTreeNode<T,V>* parent = p->parent,*grandParent = p->parent->parent;
	 SplayTreeNode<T,V> *tmpRoot,*topParent=grandParent->parent;
	if( p == parent->left &&  parent == grandParent->left)  { // LL型 zig-zig操作
		   tmpRoot = rightRotate(grandParent);
		   tmpRoot = rightRotate(tmpRoot);
	}else if(p == parent->right &&  parent == grandParent->right) { // RR型zig-zig操作
			tmpRoot = leftRotate(grandParent);
			tmpRoot = leftRotate(tmpRoot);
	}else if (p == parent->left && parent == grandParent->right) { // RL型 zig-zag操作
			grandParent->right = rightRotate(grandParent->right);
			tmpRoot = leftRotate(grandParent);
    }else  { // LR型zig-zag操作
    		grandParent->left = leftRotate(grandParent->left);
    		tmpRoot = rightRotate(grandParent);
    }
	//这里还需要再次将tmpRoot节点与其父节点连接上
	if(topParent == 0) {
        root = tmpRoot;								// 新子树根成为根节点
	}else if(grandParent == topParent->left) {
		topParent->left = tmpRoot;				// 新子树成为上层父节点的左孩子
	}else {
		topParent->right = tmpRoot;			// 新子树成为上层父节点的右孩子
	}
	return tmpRoot;
}

template<typename T,typename V>
bool SplayTree<T,V>::FindAndDelete(const T&k) {
	 SplayTreeNode<T,V>* p = root,*parent = root;
	  while(p != 0) {
			 if (k == p->key) {
				 break;
			 }else if(k < p->key) {
				  parent = p;
				  p = p->left;
			 }else {
				 parent = p;
				 p = p->right;
			 }
	  }
	  //如果找到则删除它，并返回true
	  if(p != 0) {
		  if(p == root) {
			  deleteByCopying(root);
			  if(root != 0) root->parent = 0;
		  }else if(p == parent->left) { //左边找到，则删除左孩子
			  deleteByCopying(parent->left);
			  if(parent->left != 0 ) parent->left->parent = parent;
		  }else {   // 右边找到，则删除右孩子
			  deleteByCopying(parent->right);
			  if(parent->right != 0) parent->right->parent = parent;
		  }
		  return true;
	  }
	  return false;
}
/**
 * 复制删除节点p
 * 利用指针引用，修改原引用为新的应该连接上的子树
 */
template<typename T,typename V>
void SplayTree<T,V>::deleteByCopying(SplayTreeNode<T,V>*& p) {
	   SplayTreeNode<T,V> *tmp = p;
	   if(p->left == 0) {
		    p = p->right;
	   }else if(p->right == 0) {
		    p = p->left;
	   }else {  //两个孩子节点都不为空
		   SplayTreeNode<T,V>* leftMax=p->left,*previous = p;
		   while(leftMax->right != 0){
				 previous = leftMax;
				 leftMax = leftMax->right;
		   }
		   p->key = leftMax->key;
		   p->value = leftMax->value;
		   //如果要删除的p节点的左孩子没有右孩子(p的左孩子此时即为前驱)
		   if( previous == p) {
				p->left = leftMax->left;
		   }else {
			   previous->right = leftMax->left;
		   }
		   if(leftMax->left != 0)  leftMax->left->parent = previous;
		   tmp = leftMax;
	   }
	   delete tmp;
}

template<typename T,typename V>
void SplayTree<T,V>::clear(SplayTreeNode<T,V>* p) {
        if(p != 0) {
        	 clear(p->left);
        	 clear(p->right);
        	 delete p;
        }
}
/**
 * 以q为中心向左旋转p,返回新的子树根节点q
 * 注意维护parent指针
 */
template<typename T,typename V>
SplayTreeNode<T,V>* SplayTree<T,V>::leftRotate(SplayTreeNode<T,V>* p) {
	SplayTreeNode<T,V>* q = p->right;
	p->right = q->left;				// q节点左孩子添加到p的右节点
	if(p->right != 0)
		p->right->parent = p;	// p新添加的右孩子指向其自身
	q->left = p;						// p成为q的左孩子
	q->parent = p->parent;		// q父节点指针指向原来p的父节点
	p->parent = q;					// q成为p新的父节点
	return q;
}
/**
 * 以q为中心向右旋转p
 * 注意维护parent指针
 */
template<typename T,typename V>
SplayTreeNode<T,V>* SplayTree<T,V>::rightRotate(SplayTreeNode<T,V>* p) {
	SplayTreeNode<T,V>* q = p->left;
	p->left = q->right;					// q的右孩子成为p的左孩子
	if(p->left != 0)
		p->left->parent = p;			// p新的左孩子父节点指向其自身
	q->right = p;							// p成为q的右孩子
	q->parent = p->parent;			// q的父节点指针指向原来p的父节点
	p->parent = q;						// q成为p的新父节点
	return q;
}

