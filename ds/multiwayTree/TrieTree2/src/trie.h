/*
 * trie.h
 *
 *  Created on: 2014年12月17日
 *      Author: wangdq
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <vector>

template<typename V>
class TrieNode {
public:
	TrieNode(char c,TrieNode<V>*p=0,TrieNode<V>*prev=0,TrieNode<V>*next=0,TrieNode<V>*ch=0)  {
		k = c;
		isFinal = false;
		parent = p;
		prevSib = prev;
		nextSib = next;
		child = ch;
	}
public:
	bool isFinal;
	V data;
	char k;
	TrieNode *nextSib,*prevSib;		// 实现为双向链表，便于插入和删除
	TrieNode *child,*parent;			// 找到孩子和父亲节点
};

template<typename V>
class TrieTree {
public:
	TrieTree() {
		root = 0;
	}
	~TrieTree() {
		destory(root);
	}
    void insert(const std::string &key,const V& data);
	bool search(const std::string &key,V&v);
	void remove(const std::string &key);
	void traverse();
	void findSimilar(const std::string key,std::vector<std::string> &strVec);
private:
	 TrieNode<V> *search(const std::string &key);
	 void destory(TrieNode<V> *p);
	 void traverse(TrieNode<V> *p);
	 void getString(TrieNode<V> *p,std::vector<std::string> &strvec);
private:
	TrieNode<V> *root;
};


#endif /* TRIE_H_ */
