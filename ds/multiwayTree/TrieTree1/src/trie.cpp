/*
 * trie.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: wangdq
 */

#include "trie.h"
#include <iostream>
/**
 * 插入键值key,并且绑定数据data
 */
template<typename V>
void TrieTree<V>::insert(const std::string &key,const V& data) {
        TrieNode<V>* p = root;
        for(std::string::size_type i = 0; i < key.length();i++) {
        	   int index = key[i]-'a';
        	   if(p->ptr[index] == 0) {
        		   p->ptr[index] = new TrieNode<V>();
        		   p->childCount++;
        	   }
        	   p = p->ptr[index];
        }
        p->isFinal = true;
        p->data = data;
}
template<typename V>
bool  TrieTree<V>::search(const std::string &key,V&v) {
	 TrieNode<V>* p = root;
	  for(std::string::size_type i = 0; i < key.length();i++) {
		  int index = key[i]-'a';
		  if(p->ptr[index] == 0)
			  return false;
		  p = p->ptr[index];
	  }
	  if(p->isFinal) {
		  v = p->data;
	  }
	  return p->isFinal;
}
template<typename V>
void TrieTree<V>::remove(const std::string &key) {
	TrieNode<V>* p = root,*parent;
	for(std::string::size_type i = 0; i < key.length();i++) {
		 int index = key[i]-'a';
		 if(p->ptr[index] == 0)
			  return;
		 parent = p;
		 p = p->ptr[index];
	}
	if(p->isFinal) {
		  p->isFinal = false;
		  //如果是仅有一个键，则删除整个节点
		  if(p->childCount == 0) {
			   int last = key[key.length()-1]-'a';
			   delete p;
			   parent->ptr[last] = 0;
			   parent->childCount--;
		  }
	}
}
template<typename V>
void TrieTree<V>::traverse() {
	traverse(root);
	std::cout<<std::endl;
}
template<typename V>
void TrieTree<V>::traverse(TrieNode<V> *p) {
	   if(p != 0) {
		     if(p->isFinal)
		    	 	 std::cout<<p->data<<"\t";
		     for(int i = 0;i < TrieNode<V>::ALPHABET_SIZE ;i++)
		    	     if(p->ptr[i] != 0) traverse(p->ptr[i]);
	   }
}
template<typename V>
void TrieTree<V>::destory(TrieNode<V> *p) {
        if(p != 0) {
        	 for(int i = 0;i < TrieNode<V>::ALPHABET_SIZE && p->ptr[i] != 0;i++)
        		     	 	 destory(p->ptr[i]);
        	 delete p;
        }
}

