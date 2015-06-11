/*
 * trie_array.cpp
 *
 *  Created on: 2015年5月25日
 *      Author: wangdq
 */
#include <algorithm>
#include <iostream>
#include "trie_array.h"
/**
 * 创建由charSet给定字符集的trie
 */
template<typename T>
TrieTree<T>::TrieTree(char *charSet, int size):ALPHABET_SIZE(size) {
		root = new TrieNode<T>();
		alphabet = new char[size];
		std::copy(charSet,charSet+size,alphabet);
}
/**
 *  默认创建包含26个小写字母的trie
 */
template<typename T>
TrieTree<T>::TrieTree():ALPHABET_SIZE(26) {
		root = new TrieNode<T>(ALPHABET_SIZE);
		alphabet = new char[26];
		for(int i=0;i < ALPHABET_SIZE;++i)
			alphabet[i] = 'a'+i;
}
/**
 *  存入键key,并绑定值value
 * case 1: 已经存在键key,则更新值
 * case 2: 存在键key的前缀，但未标记为final,则标记为final并设置值
 * case 3: 不存在key的前缀，则添加key中剩余部分为前缀，标记final并设置值
 */
template<typename T>
void TrieTree<T>::put(const std::string &key, T value) {
	std::string::const_iterator it = key.begin();
	TrieNode<T> *prev = root;
	int pos = 0;
	bool bret = search(key,it,prev,pos);
	if(!bret) {
		while(it != key.end()) {		//补上key的部分前缀
				pos = *it-alphabet[0];
				prev->childsPtr[pos] = new TrieNode<T>(ALPHABET_SIZE);
				prev->childsCount++;
				prev = prev->childsPtr[pos];
				++it;
		}
		prev->isFinal = true;
		prev->value = value;
	}else {
		prev->childsPtr[pos]->value = value;
	}
}
/**
 * 删除键key
 * 存在则返回true,否则返回false
 */
template<typename T>
bool TrieTree<T>::remove(const std::string &key) {
	std::string::const_iterator it = key.begin();
	TrieNode<T> *prev = root;
	int pos = 0;
	bool bret = search(key,it,prev,pos);
	if(!bret)
		return false;
	if(prev->childsPtr[pos]->childsCount == 0) {	 // 如果键key所在结点只有一个键则直接删除键本身
		delete prev->childsPtr[pos];
		prev->childsPtr[pos] = 0;
		prev->childsCount--;
	}
	else {
		prev->childsPtr[pos]->isFinal = false;	// 置为非final结点
	}
	return true;
}
/**
 * 搜索键key
 * 找到则返回true 同时value返回对应值
 * 否则返回false
 */
template<typename T>
bool TrieTree<T>::search(const std::string &key,T&value) {
	std::string::const_iterator it = key.begin();
	TrieNode<T> *prev = root;
	int pos = 0;
	bool bret = search(key,it,prev,pos);
	if(!bret)
		return false;
	value = prev->childsPtr[pos]->value;
	return true;
}
template<typename T>
void TrieTree<T>::traverse() {
	std::string empty;
	std::cout << "{";
	orderedTraverse(root,empty);
	std::cout << "}";
}
/**
 * 查找由字符串迭代器给出的键值key对应结点
 * case 1: 存在键key,则返回true，同时prev返回这个键值结点的父节点，pos指向其在父节点中索引
 * case 2: 不存在键key,则返回false
 *             当前没有key作为前缀的字符串，则prev指向待插入字符位置的父节点,pos指示其在父节点中索引
 *             否则prev为这个满足以key作为前缀的结点的父节点，pos指向其在父节点中索引
 */
template<typename T>
bool TrieTree<T>::search(const std::string &key,std::string::const_iterator &itBegin,TrieNode<T>* &prev,int &pos) {
	 TrieNode<T> *current = root;
	 for(pos = *itBegin-alphabet[0];itBegin !=key.end() && current->childsPtr[pos] != 0;) {
		     prev = current;
		     current = current->childsPtr[pos];
		     ++itBegin;
		     if(itBegin != key.end())
		    	 pos = *itBegin-alphabet[0];
	 }
	 if(itBegin == key.end() && current->isFinal)	// 存在键key
		 return true;
	 if(itBegin != key.end())
		 prev = current;
	return false;
}
/**
 * 有序遍历
 */
template<typename T>
void TrieTree<T>::orderedTraverse(TrieNode<T>*p,std::string pres) {
	if(p != 0) {
		    if(p->isFinal)
		    	std::cout << pres <<": " << p->value << "    ";
		    for(int i=0; i < ALPHABET_SIZE;++i)
		    	if(p->childsPtr[i] != 0)
		    		orderedTraverse(p->childsPtr[i], pres+alphabet[i]);
	}
}
/**
 * 递归释放结点p
 */
template<typename T>
void TrieTree<T>::clear(TrieNode<T>*p) {
	if(p != 0) {
		for(int i=0;i < ALPHABET_SIZE;++i )
			if(p->childsPtr[i] != 0)
				clear(p->childsPtr[i]);
		delete p;
	}
}
