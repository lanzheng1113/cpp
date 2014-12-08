/*
 * biheap.h
 *
 *  Created on: 2014年12月8日
 *      Author: wangdq
 */

#ifndef BIHEAP_H_
#define BIHEAP_H_

template<typename K,typename V>
class BiHeapNode {
public:
	BiHeapNode(const K&k,const V&v) {
		key = k;
		value = v;
	}
	BiHeapNode(const BiHeapNode<K,V> & node) {
		key = node.key;
		value = node.value;
	}
	/**
	 * 重载小于号操作符，比较键的大小
	 */
	bool operator < (const BiHeapNode<K,V> & node){
		     return key < node.key;
	}
	bool operator > (const BiHeapNode<K,V> & node){
			 return  key > node.key;
	}
	BiHeapNode(){};
public:
	 K key;
	 V value;
};

template<typename K,typename V,int initCapacity = 32>
class BiHeap {
public:
	BiHeap();
	BiHeap(BiHeapNode<K,V> *pbegin,BiHeapNode<K,V> *pend);
	~BiHeap();
	void insert(const K&k,const V&v);
	bool search(const K&k,V&v);
	bool removeTop(BiHeapNode<K,V> &node);
	void traverse();
	bool isEmpty() {
		 return size == 0;
	}
private:
	void buildFromArrayTop(BiHeapNode<K,V> *pbegin,BiHeapNode<K,V> *pend);
	void buildFromArrayBottom(BiHeapNode<K,V> *pbegin,BiHeapNode<K,V> *pend);
	void visit(BiHeapNode<K,V>* p);
	void moveDown(int index);
	void moveUp(int index);
	int size;	// 指示当前实际存贮元素个数
	int capacity;	// 指示当前容量
	BiHeapNode<K,V>* data;	// 存储数据的数组指针
};



#endif /* BIHEAP_H_ */
