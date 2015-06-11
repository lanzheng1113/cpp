/*
 * biheap.cpp
 *
 *  Created on: 2015年5月21日
 *      Author: wangdq
 */
#include <iostream>
#include <algorithm>
#include "biheap.h"
/**
 * 由范围指针构造二叉堆
 * topDown指示使用哪种构建方式  这里是为了便于学习
 */
template<typename T,int initCapacity>
BiHeap<T,initCapacity>::BiHeap(const T* pbegin,const T* pend,bool topDown) {
	capacity = size = 0;
	if(!topDown)
		buildBottomUp(pbegin,pend);		//从底到顶构建
	else
		buildTopDown(pbegin,pend);		//从顶到底构建
}
template<typename T,int initCapacity>
BiHeap<T,initCapacity>::BiHeap() {
		capacity = initCapacity;
		size = 0;
		base = new T[capacity];
}
template<typename T,int initCapacity>
BiHeap<T,initCapacity>::~BiHeap() {
	delete[] base;
	base = 0;
}
/**
 * 插入元素e
 * 插入失败返回false,成功返回true
 */
template<typename T,int initCapacity>
bool BiHeap<T,initCapacity>::push(const T& e) {
	if(size ==  capacity) {		// 重新分配内存 并拷贝内容
		capacity += capacity / 2;
		T* tmp = new T[capacity];	// 分配新的空间
		if(base == 0) {
			std::cerr<<"insert error: out of memory"<<std::endl;
			return false;
		}
		//std::cout << "realloc memory success." << std::endl;
		std::copy(base, base+size,tmp);	// 拷贝元素
		delete[] base;	// 释放原空间
		base = tmp;
	}
	base[size] = e;
	moveUp(base,size);
	++size;
	return true;
}
/**
 * 取出顶元素
 * 算法思想:
 * 1)如果堆中没有元素，则返回false
 * 2)如果堆中只有一个元素，则将e设置为根元素，堆大小置为0,返回true
 * 3)否则,将最后叶子节点赋值给根，并删除叶子节点
 *    然后自顶向下调整根元素直到不违反堆性质,返回true
 */
template<typename T,int initCapacity>
bool BiHeap<T,initCapacity>::pop(T& e) {
		if(size == 0)
			return false;
		e = base[0];
		if(size == 1)
			size = 0;
		else {
			base[0] = base[--size];
			moveDown(base,0,size);
		}
		return true;
}
template<typename T,int initCapacity>
void BiHeap<T,initCapacity>::traverse() {
	T * pbegin = base;
	while(pbegin != base+size)
		 std::cout << *pbegin++ << "\t";
}
/**
 * 自底向上调整curIndex所指元素 直到不违反堆的性质或者curIndex已经为根结点为止
 */
template<typename T,int initCapacity>
void BiHeap<T,initCapacity>::moveUp(T* data,int curIndex){
	int pIndex = ( curIndex-1) / 2;
	while ( curIndex != 0 && data[curIndex] > data[pIndex]) {
		std::cout<<"up swap: "<<data[curIndex]<<" "<<data[pIndex]<<std::endl;
		std::swap(data[curIndex], data[pIndex]);
		curIndex = pIndex;
		pIndex = (curIndex-1) / 2;
	}
}
/**
 * 自顶向下调整curIndex所指元素  直到不违反堆的性质或者curIndex已经为叶子节点时停止
 * curIndex为当前节点索引
 * endIndex为超出末端索引
 */
template<typename T,int initCapacity>
void BiHeap<T,initCapacity>::moveDown(T*data, int curIndex, int endIndex){
	int left = 2*curIndex+1;
    int right = 2*curIndex+2;
    int maxIndex = curIndex;
	while( left < endIndex) {
		    if(data[left] > data[maxIndex])
		    	maxIndex = left;
		    if(right < endIndex && data[right] > data[maxIndex])
				maxIndex = right;
		    if(maxIndex == curIndex)			// 不需要再继续交换结点
		    	break;
		    //std::cout<<"down swap: "<<data[curIndex]<<" "<<data[maxIndex]<<std::endl;
		    std::swap(data[maxIndex],data[curIndex]);
		    curIndex = maxIndex;
			left = 2*curIndex+1;
			right = 2*curIndex+2;
	}
}
/**
 * 从顶到底的插入范围指针内的元素，构造一个大顶堆
 * John Williams 算法
 * 算法思想:
 * 逐个加入范围指针内的元素
 * 每个新加入的元素都按照insert方法类似的从叶子调整至根的方法调整
 */
template<typename T,int initCapacity>
void BiHeap<T,initCapacity>::buildTopDown(const T* pbegin,const T* pend){
	if(pbegin == pend)  return;
	capacity = (pend-pbegin)+initCapacity;
	base = new T[capacity];
	while(pbegin != pend)
			push(*pbegin++);
}
/**
 *  从底到顶的方法将指针范围内的元素转换为大顶堆
 *  Robert Floyd 算法
 *  算法思想:
 *  1)将指针范围内元素复制到data内
 *  2)从第一个非叶子节点 data[size/2 -1]开始按照pop方法类似的自顶向下的方法调整
 *  3)重复2直到根节点调整完毕为止
 */
template<typename T,int initCapacity>
void BiHeap<T,initCapacity>::buildBottomUp(const T* pbegin,const T* pend) {
	if(pbegin == pend)  return;
	capacity = (pend-pbegin)+initCapacity;
	base = new T[capacity];
	std::copy(pbegin,pend,base);
	size = pend-pbegin;
	int curIndex = size/2-1;
	while(curIndex >= 0)
		moveDown(base,curIndex--,size);
}
/**
 * 对范围指针内的内容进行堆排序 升序排列
 * 算法思想:
 * 1)构建大顶堆,共n个元素
 * 2)每次将根元素与最后一个元素i交换，然后对根元素调整为大顶堆
 * 3)重复2过程n-1次
 */
template<typename T,int initCapacity>
void  BiHeap<T,initCapacity>::sort(T* pbegin,T* pend) {
	// 构建初始大顶堆
	int count = pend-pbegin;
	int curIndex = count/2-1;
	while(curIndex >= 0)
		moveDown(pbegin,curIndex--,count);
	// n-1次交换
	for(int n = count-1; n > 0 ;--n) {
		 std::swap(pbegin[n],pbegin[0]);
		 std::cout << "move down： " << pbegin[0] << std::endl;
		 moveDown(pbegin,0,n);
	}
}
