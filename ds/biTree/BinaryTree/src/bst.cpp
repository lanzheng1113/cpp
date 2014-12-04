/*
 * bst.cpp
 *
 *  Created on: 2014年12月2日
 *      Author: wangdq
 */

#include "bst.h"
#include <stack>

template<typename T>
void BST<T>::breadthFirst() {

}
//VLR
template<typename T>
void BST<T>::iterativePreorder() {
      if(root == 0)  return;
      std::stack<BSTNode<T>*> stack;
      stack.push(root);
      while(!stack.empty()) {
    	  BSTNode<T> * top = stack.top();
    	  visit(top);
    	  stack.pop();
    	  if(top->right != 0)
    		  stack.push(top->right);
    	  if(top->left != 0)
    		  stack.push(top->left);
      }
}
//LVR
template<typename T>
void BST<T>::iterativeInorder() {
	  if(root == 0) return;
      std::stack<BSTNode<T>*> stack;
      stack.push(root);
      while(!stack.empty()) {
    	   BSTNode<T> * top = stack.top();
    	   //push left until left is null
    	   while(top->left != 0) {
    		        top = top->left;
    		        stack.push(top);
    	   }
    	   visit(top);
           stack.pop();
           //pop until a node's right is not null or stack empty
           while(!stack.empty() && top->right == 0) {
        	       top = stack.top();
        	       visit(top);
        	       stack.pop();
           }
           //push the right child
           if(top->right != 0) {
        	   stack.push(top->right);
           }
      }
}
//LRV
template<typename T>
void BST<T>::iterativePostorder() {
   if(root == 0) return;
   std::stack<BSTNode<T>*> stack;
   stack.push(root);
   while(!stack.empty()) {
	       BSTNode<T>* top = stack.top();
	       //push left child until left is null
	       while(top->left != 0) {
	    	   top = top->left;
	    	   stack.push(top);
	       }
	       //if right child exist,push right child
	       if(top->right != 0) {
	    	   stack.push(top->right);
	       }else {
	    	   visit(top);
	    	   stack.pop();
	    	   while(!stack.empty()) {
	    		     // pop as right child or left child but parent's right is null
	    		     if(top == stack.top()->right  || stack.top()->right == 0) {
	    		    	  top = stack.top();
	    		    	  visit(top);
	    		    	  stack.pop();
	    		     }else {
	    		    	 stack.push(stack.top()->right);
	    		    	 break;
	    		     }
	    	   }
	       }
    }
}
/**
 * Morris Algorithm of inorder traverse tree
 * Modify and recover the tree structure when traversing
 */
template<typename T>
void BST<T>::MorrisInorder() {
       BSTNode<T> * tmp ,*p = root;
       while(p != 0) {
    	     //no left child,just visit current node,and set p to right child
    	     if(p->left == 0 ) {
    	    	   visit(p);
    	    	   p = p->right;
    	     }else {
    	    	     tmp = p->left;
    	    	     while(tmp->right != 0 && tmp->right != p) {
    	    	    	    tmp = tmp->right;
    	    	     }
    	    	     //get p's left child's right-most node,modify the tree
    	    	     if(tmp->right == 0) {
    	    	    	     tmp->right = p;
    	    	    	     p = p->left; // set p's left child as the new top
    	    	     }else if(tmp->right == p) {   // get the temporary parent of p,recover the tree
    	    	    	      visit(p);
    	    	    	      tmp->right = 0;
    	    	    	      p = p->right;
    	    	     }
    	     }
       }
}

template<typename T>
void BST<T>::insert(const T& e) {
         if (root == 0) {
        	 root = new BSTNode<T>(e);
         }else {
        	 BSTNode<T>* curNode = root;
        	 BSTNode<T>* parent = 0;
        	 while(curNode != 0) {
        		    parent = curNode;
        		    if (e == curNode->key)  {
        		    	  return ; // no duplicate element
        		    }else if (e < curNode->key) {
        		    	curNode = curNode->left;
        		    }else {
        		    	curNode = curNode->right;
        		    }
        	 }
        	 if(e < parent->key) {
        		 parent->left = new BSTNode<T>(e); // insert as left child
        	 }else {
        		 parent->right = new BSTNode<T>(e);// insert as right child
        	 }
         }
}
/**
 * Delete node p,using copying algorithm
 * note the pointer reference ,will reassign parent'filed
 */
template<typename T>
void BST<T>::deleteByCopying(BSTNode<T>*&p) {
       BSTNode<T> *tmp = p;
       if(p->left == 0) {
    	     p = p->right;
       }else if(p->right == 0) {
    	    p = p->left;
       }else { // has both child
    	   BSTNode<T>* leftMax=p->left,*previous = p;
    	   while(leftMax->right != 0)
    	   {
    		     previous = leftMax;
    		     leftMax = leftMax->right;
    	   }
    	   p->key = leftMax->key; // rewrite key field using the left-max key
    	   //p's left child has no right child
    	   if( previous == p) {
    		    p->left = leftMax->left;
    	   }else {
    		   previous->right = leftMax->left;
    	   }
    	   tmp = leftMax;
       }
       delete tmp;
}
/**
 * Delete node by value,using copying method
 */
template<typename T>
void BST<T>::findAndDeleteByCopying(const T&e){
	 if(root == 0)  return;
	      BSTNode<T>* p = root,*parent = root;
	      if(root->key == e) {
	    	  deleteByCopying(root); // delete root element
	    	  return;
	      }
	      //find if exists
	      while(p != 0) {
	    	     if (e == p->key) {
	    	    	 break;
	    	     }else if(e < p->key) {
	    	    	 parent = p;
	    	    	  p = p->left;
	    	     }else {
	    	    	 parent = p;
	    	    	 p = p->right;
	    	     }
	      }
	      //if find ,delete it
	      if(p != 0) {
	    	  if(e == parent->left->key)
	    		  deleteByCopying(parent->left); // delete left child
	    	    else
	    	       deleteByCopying(parent->right);// delete right child
	      }
}
/**
 * remove the current node
*  note the pointer reference, which will reassign value to replace the current node's parent filed
 */
template<typename T>
void BST<T>::deleteByMerging(BSTNode<T>*& p) {
	 BSTNode<T>* tmp = p;
      if(p->left == 0) {
    	      p = p->right;
      }else if(p->right == 0) {
    	      p = p->left;
      }else {
    	     BSTNode<T>  *leftMax =p->left;
    	     while(leftMax->right != 0) {
    	    	 leftMax = leftMax->right;
    	     }
    	     leftMax->right = p->right;
    	     p = p->left;
      }
      delete tmp;
}
/**
 * Delete specified element by value
 * keep the tree structure while deleting
 */
template<typename T>
void BST<T>::findAndDeleteByMerging(const T& e) {
      if(root == 0)  return;
      BSTNode<T>* p = root,*parent = root;
      if(root->key == e) {
    	  deleteByMerging(root); // delete root element
    	  return;
      }
      //find if exists
      while(p != 0) {
    	     if (e == p->key) {
    	    	 break;
    	     }else if(e < p->key) {
    	    	 parent = p;
    	    	  p = p->left;
    	     }else {
    	    	 parent = p;
    	    	 p = p->right;
    	     }
      }
      //if find ,delete it
      if(p != 0) {
    	  if(e == parent->left->key)
    	      	 deleteByMerging(parent->left); // delete left child
    	    else
    	      	  deleteByMerging(parent->right);// delete right child
      }
}

template<typename T>
void BST<T>::balance(T*,int,int) {

}

template<typename T>
void BST<T>::clear(BSTNode<T>* node) {
         if(node != 0) {
        	   clear(node->left);
        	   clear(node->right);
        	   delete node;
         }
}
/**
 * search specified element in binary search tree
 */
template<typename T>
 T* BST<T>::search(BSTNode<T>* node,const T& e) const {
      while( node != 0) {
    	    if (e == node->key) {
    	    	 return node;
    	    }else if (e > node->key) {
    	    	node = node->right; // match the right element
    	    }else {
    	    	node = node->left; // match the left element
    	    }
      }
      return 0; // failed matching
 }

template<typename T>
 void BST<T>::preorder(BSTNode<T>* node) {
        if ( node != 0) {
        	visit(node);
        	preorder(node->left);
        	preorder(node->right);
        }
 }
template<typename T>
 void BST<T>::inorder(BSTNode<T>* node) {
       if (node != 0) {
             inorder(node->left);
             visit(node);
             inorder(node->right);
       }
 }

template<typename T>
void BST<T>::postorder(BSTNode<T>* node) {
       if( node != 0) {
    	   postorder(node->left);
    	   postorder(node->right);
    	   visit(node);
       }
 }



