/*
 * biheap.h
 *
 *  Created on: 2015年5月21日
 *      Author: wangdq
 */

#ifndef BIHEAP_H_
#define BIHEAP_H_
/**
 * 二叉堆-大顶堆
 * Binary Heap
 * 约定根节点编号为0,后续结点依次增加
 */
template<typename T,int initCapacity = 32>
class BiHeap {
public:
	BiHeap(const T* pbegin,const T* pend, bool topDown=false);
	BiHeap();
	~BiHeap();
	bool push(const T& e);
	bool pop(T& e);
	void traverse();
	bool isEmpty() const{
			 return size == 0;
	}
	int getSize() const{
		return size;
	}
	static void  sort(T* pbegin,T* pend);
private:
	static void moveUp(T* data,int curIndex);
	static void moveDown(T*data, int curIndex, int endIndex);
	void buildTopDown(const T* pbegin,const T* pend);
	void buildBottomUp(const T* pbegin,const T* pend);
private:
	T * base;	// 存储数据的数组指针
	int size;	// 实际元素个数
	int capacity;	// 已经分配的容量
};
#endif /* BIHEAP_H_ */
