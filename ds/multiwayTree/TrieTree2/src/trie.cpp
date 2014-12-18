/*
 * trie.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: wangdq
 */
#include "trie.h"
#include <string>
#include <iostream>
#include <iterator>

template<typename V>
void TrieTree<V>::insert(const std::string &key,const V& data) {
	TrieNode<V>* p = root,*parent = 0,*prev;
	for(std::string::size_type i = 0; i < key.length();i++)  {
		 // 如果当前层没有节点，则创建节点
		 if(p == 0) {
			  p = new TrieNode<V>(key[i],parent);
			  if(parent != 0) parent->child = p;
			  if(root == 0)
				  root = p;
		 }else {
			 //存在节点则搜索字符key[i]
			 parent = p->parent;
			 prev = 0;
			  while(p != 0 && p->k < key[i]) {
				  prev = p;
				  p = p->nextSib;
			  }
			  if(p == 0 || p->k > key[i] ) {		//没有找到key[i]对应字符
				  if(prev == 0) {		// 头部插入
					  p = new TrieNode<V>(key[i],parent,prev,p);
					  p->nextSib->prevSib = p;
					  if(parent != 0)
						  parent->child = p;
					  else
						  root = p;
				  }else if(p == 0){	// 尾部插入
					  p = new TrieNode<V>(key[i],parent,prev);
					  prev->nextSib = p;
				  }else {    // 中间插入
					  p = new TrieNode<V>(key[i],parent,prev,prev->nextSib);
					  prev->nextSib = p;
					  p->nextSib->prevSib = p;
				  }
			  }
		 }
		 parent = p;
		 p = p->child;
	}
	parent->isFinal = true;
	parent->data = data;
}
template<typename V>
TrieNode<V> * TrieTree<V>::search(const std::string &key) {
   TrieNode<V>* p = root,*parent = 0;
	for(std::string::size_type i = 0; i < key.length();i++)  {
			 if(p == 0)
				   return 0;
			 while(p != 0 && p->k < key[i])
					  p = p->nextSib;
			if(p != 0 && p->k == key[i]) {
				parent = p;
				p = p->child;
			}
			else {
				return 0;
			}
	 }
	 return parent;
}
template<typename V>
bool TrieTree<V>::search(const std::string &key,V&v) {
	TrieNode<V>* p  = search(key);
	 if(p != 0 && p->isFinal) {
		 v = p->data;
		 return true;
	 }
     return false;
}
template<typename V>
void TrieTree<V>::remove(const std::string &key) {
	TrieNode<V>* p  = search(key);
	if(p == 0)
		return;
	p->isFinal = false;
	if(p->child == 0) {	// 该节点没有孩子，则删除这个包含key的节点
		 if(p->prevSib == 0) {
			 p->parent->child = p->nextSib;
		 }else {
			 p->prevSib->nextSib = p->nextSib;
		 }
	}
}
template<typename V>
void TrieTree<V>::traverse() {
	traverse(root);
	std::cout<<std::endl;
}
/**
 * 销毁树
 */
template<typename V>
void TrieTree<V>::destory(TrieNode<V> *p) {
	  if(p != 0) {
		   if(p->child != 0)
			   destory(p->child);	// 先释放孩子节点空间
		   if(p->nextSib != 0)
		   		destory(p->nextSib); // 在释放后续兄弟节点空间
		   delete p;	// 最后释放自己空间
	  }
}
template<typename V>
void TrieTree<V>::traverse(TrieNode<V> *p) {
		if(p != 0) {
			   if(p->isFinal)
				   std::cout<<p->data<<"\t";
			   if(p->child != 0) traverse(p->child);
			   if(p->nextSib != 0) traverse(p->nextSib);
		}
}
template<typename V>
void TrieTree<V>::findSimilar(const std::string key,std::vector<std::string> &strVec) {
	TrieNode<V>* p  = search(key);
	if(p == 0)
			 return;
	if(p->isFinal)
		strVec.push_back(key);
	getString(p->child,strVec);
	std::vector<std::string>::iterator it = strVec.begin();
	if(p->isFinal)
		 ++it;
	for(;it != strVec.end();++it)
		*it = key+*it;
}
template<typename V>
void TrieTree<V>::getString(TrieNode<V> *p,std::vector<std::string> &strvec) {
         while(p != 0) {
        	 std::vector<std::string> substrVec;
        	 if(p->isFinal)
        		 strvec.push_back(std::string(1,p->k));	// 当前是总结节点则加入
        	 getString(p->child,substrVec);	// 获取孩子节点获取的关键值字符串
        	 for(std::vector<std::string>::iterator it = substrVec.begin();it != substrVec.end();++it)
        		 	 strvec.push_back(p->k+*it);
        	 p = p->nextSib;
         }
}
