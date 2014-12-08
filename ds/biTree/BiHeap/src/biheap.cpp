/*
 * biheap.cpp
 * 约定根节点在数组中索引为0
 *
 *  Created on: 2014年12月8日
 *  Author: wangdq
 */
#include "biheap.h"
#include <iostream>
#include <algorithm>

template<typename K,typename V,int initCapacity >
BiHeap<K,V,initCapacity>::BiHeap() {
	    capacity = initCapacity;
		data = new BiHeapNode<K,V>[capacity];
		size = 0;
}
template<typename K,typename V,int initCapacity >
BiHeap<K,V,initCapacity>::~BiHeap() {
	 delete[] data;
}

template<typename K,typename V,int initCapacity >
BiHeap<K,V,initCapacity>::BiHeap(BiHeapNode<K,V> *pbegin,BiHeapNode<K,V> *pend) {
	    if(pbegin != pend) {
	    	buildFromArrayBottom(pbegin,pend);	//自底向上构建堆
	    	//buildFromArrayTop(pbegin,pend);		// 自顶向下构建堆
	    }else {
	    	 capacity = initCapacity;
	    	 data = new BiHeapNode<K,V>[capacity];
	    	 size = 0;
	    }
}
/**
 * 对新插入节点，自底向上调整，构建堆
 */
template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::buildFromArrayTop(BiHeapNode<K,V> *pbegin,BiHeapNode<K,V> *pend){
	if(pbegin == pend)
		    return;
	capacity = pend-pbegin;
	size = capacity;
	data = new BiHeapNode<K,V>[capacity];
	int i = 0;
	while(pbegin != pend) {
		   data[i] = *pbegin++;
		   moveUp(i); // 对每个新加入的数据向上调整
		   ++i;
	}
}
/**
 * 从树的底部开始向上，逐个调整，构建堆
 * 从第一个非叶子节点开始，依次自顶向下调整
 */
template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::buildFromArrayBottom(BiHeapNode<K,V> *pbegin,BiHeapNode<K,V> *pend) {
	    if(pbegin == pend)
	    	  return;
	    //一次性填充数据
	    capacity = pend-pbegin;
		size = capacity;
		data = new BiHeapNode<K,V>[capacity];
		int i = 0;
		while(pbegin != pend)
				data[i++] = *pbegin++;
		//从最后一个非叶子节点开始,这个调整直至根节点
		int last = size /2-1;
		for( ; last >= 0;--last)
			moveDown(last);
}


template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::insert(const K&k,const V&v) {
	  //如果容量不够，成倍增加
	  if(size == capacity) {
		  capacity *= 2;
		  BiHeapNode<K,V>* p = new BiHeapNode<K,V>[capacity];
		  if(p == 0) {
			  std::cerr<<"insert error: out of memory"<<std::endl;
			  return;
		  }
		  std::copy(data,data+size,p);
		  delete[] data;
		  data = p;
	  }
	  data[size] = BiHeapNode<K,V>(k,v);
      moveUp(size); 	// 新插入节点，向上调整
      ++size;
}

template<typename K,typename V,int initCapacity >
bool BiHeap<K,V,initCapacity>::search(const K&k,V&v) {
	bool ret = false;
	 for(int i=0;i < size ;i++)
		   if(k ==data[i]->key ) {
			   	   ret = true;
		       	   v = data[i]->value;
		       	   break;
	 	   }

    return ret;
}
/**
 *  移除堆的顶部
 */
template<typename K,typename V,int initCapacity >
bool BiHeap<K,V,initCapacity>::removeTop(BiHeapNode<K,V> &node) {
	    if(size == 0)
	    	 return false;
	   node = data[0]; // 返回根节点
       if(size == 1 ) {
    	   size = 0;
       }
       else {
            data[0] = data[size-1];  	// 将最后一个节点复制到根节点
            size--;							// 移除最后一个节点
            moveDown(0);				// 自顶向下调整根节点
       }
       return true;
}
/**
 * 执行广度优先遍历
 */
template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::traverse() {
	  for(int i=0;i < size ;i++)
		  visit(&data[i]);
	  std::cout<<std::endl;
}

template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::visit(BiHeapNode<K,V>* p) {
		std::cout<<p->key<<"\t";
}
/**
 * 自顶向下调整元素index,使树满足堆属性
 * 向下调整直到它不存在后继，或者没有比它大的孩子节点为止
 */
template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::moveDown(int index) {
        int left = 2*index+1;
        int right = 2*index+2;
        int max = index;
        if(left < size && data[left] > data[max])
        	  max = left;
        if(right < size && data[right] > data[max])
        	  max = right;
        //存在孩子节点比index值大，则需要做出调整
        if(max != index) {
        	    std::cout<<"Swap: "<<data[index].key<<" "<<data[max].key<<std::endl;
        		std::swap(data[index],data[max]);
        		moveDown(max); 						//继续向下调整
        }
}
/**
 * 自底向上调整节点index,使树满足堆属性
 * 调整index节点直到其为根或者存在比它大的父节点为止
 * 非根index节点的父节点索引为[ (index-1) / 2 ]
 */
template<typename K,typename V,int initCapacity >
void BiHeap<K,V,initCapacity>::moveUp(int index) {
      while(index != 0 && data[ (index-1) / 2 ] < data[index]) {
    	        std::cout<<"Swap: "<<data[index].key<<" "<<data[ (index-1) / 2 ].key<<std::endl;
    	        std::swap(data[ (index-1) / 2 ],data[index]);
    	        index = (index-1) / 2;
      }
}

