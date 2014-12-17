/*
 * trie.h
 *
 *  Created on: 2014年12月17日
 *      Author: wangdq
 */

#ifndef TRIE_H_
#define TRIE_H_
#include <string>

template<typename V>
class TrieNode {
public:
	TrieNode() {
		isFinal = false;
		childCount = 0;
		for(int i=0;i < ALPHABET_SIZE;i++)
			ptr[i] = 0;
	}
public:
	static const int ALPHABET_SIZE = 26;		// 26个字母大小
	TrieNode* ptr[ALPHABET_SIZE];
	V data;
	bool isFinal;
	int childCount;
};

template<typename V>
class TrieTree {
public:
	TrieTree() {
		root = new TrieNode<V>();
	}
	~TrieTree() {
		destory(root);
	}
    void insert(const std::string &key,const V& data);
    bool  search(const std::string &key,V&v);
    void remove(const std::string &key);
    void traverse();
private:
     void destory(TrieNode<V> *p);
     void traverse(TrieNode<V> *p);
private:
	TrieNode<V>* root;
};

#endif /* TRIE_H_ */
