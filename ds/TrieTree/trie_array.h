/*
 * trie_array.h
 *
 *  Created on: 2015年5月25日
 *      Author: wangdq
 */

#ifndef TRIE_ARRAY_H_
#define TRIE_ARRAY_H_

#include <string>

template<typename T> class TrieTree;
/**
 * 数组实现的trie结点
 * 每个结点包含alphabetSize个孩子指针
 */
template<typename T>
class TrieNode {
public:
	TrieNode(int alphabetSize):isFinal(false), childsCount(0) {
		childsPtr = new TrieNode *[alphabetSize];
		for(int i=0; i < alphabetSize ;++i)
			childsPtr[i] = 0;
	}
	~TrieNode() {
		delete[] childsPtr;
	}
private:
	bool isFinal;	// 是否为一个键
	T		value;	// 绑定的值
	int  childsCount;	// 孩子个数
	TrieNode **childsPtr;
	friend class TrieTree<T>;
};

/**
 * Trie 数组实现
 */
template<typename T>
class TrieTree {
public:
	TrieTree(char *charSet, int size);
	TrieTree();
	~TrieTree() {
		clear(root);
		delete[] alphabet;
	}
	void put(const std::string &key, T value);
	bool remove(const std::string &key);
	bool search(const std::string &key,T&value);
	void traverse();
private:
	const int ALPHABET_SIZE; // 字母表大小
	TrieNode<T> *root;
	char *alphabet;	// 字母表
private:
	bool search(const std::string &key,std::string::const_iterator &itBegin,TrieNode<T>* &prev, int &pos);
	void orderedTraverse(TrieNode<T>*p,std::string pres);
	void clear(TrieNode<T>*p);
};
#endif /* TRIE_ARRAY_H_ */
