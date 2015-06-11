/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: wangdq
 */
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void findNextV1(const string&p,vector<int>& next);
void findNextV2(const string&p,vector<int>& next);
int KMPMatch(const string&text,const string &p);
int btPrefixMatch(const string&text,const string&p);
int btSuffixMatch(const string& t,const string&p);
int HancartMatch(const string&text,const string&p);
int BMMatch(const string&t,const string&p);
void preComputeGs(const string&p,vector<int>& suffix,vector<int>& bmGs);
void computeSuffixV1(const string&p,vector<int>& suffix);
void computeSuffixV2(const string&p,vector<int>& suffix);
void printBMTables(const string& p,vector<int>& bmBc,vector<int>& suffix,vector<int>& bmGs);
void testCase0();
void testCase1();
void testCase2();
typedef int (*strMatchFunc)(const string&,const string&);


int main() {
	testCase1();
	return 0;
}
/**
 * 测试next函数
 */
void testCase0() {
	    string p("aaaab");
	    vector<int> next(p.length(),-1);
	    findNextV2(p,next);
	    copy(next.begin(),next.end(),ostream_iterator<int>(cout,"\t"));
	    cout<<endl;
}
/**
 * 测试字符串匹配
 */
void testCase1() {
	    string text = "abbadcababacab";
	    string pattern = "bac";
        vector<strMatchFunc> funcVec{btPrefixMatch,btSuffixMatch,KMPMatch,BMMatch};
        for(strMatchFunc func : funcVec) {
        	int i = func(text,pattern);
        	std::size_t found = text.find(pattern); 	// 利用系统函数验证结果
        	if(i != -1 && found != std::string::npos) {
        		 	 cout<< "found "<<pattern<<" in "<<text<<" from index: "<<i<<endl;
        	}else if( i == -1 && found == std::string::npos) {
        			cout<< "not found"<<pattern<<" in "<<text<<endl;
        	}else {
        			cerr<<"error occurred."<<endl;
        	}
        }
}
void testCase2() {
	 string text = "abcddefeghdedf";
	 string pattern = "bcababab";
	 BMMatch(text,pattern);
}
/**
 * 暴力前缀搜索法
 */
int btPrefixMatch(const string&text,const string&p) {
	  int i =0,j=0;
	  int tlen = text.length(),plen = p.length();
	  while (i < tlen && j < plen) {
		      if(text[i] == p[j]) {
		    	  ++i;
		    	  ++j;de
		      }else {
		    	   i = i-j+1; // 回溯到上次开始的下一个位置处继续逐个比较
		    	   j = 0; // 从0开始与text[i]字符比较
		      }
	  }
      if(j == plen)
    	  return i-j;
      else
    	  return -1;
}
/**
 * 暴力后缀搜索法
 */
int btSuffixMatch(const string& t,const string&p) {
	int i = 0,j = 0;
	int tlen = t.length(),plen = p.length();
	while( i <= tlen-plen) {
		 for(j = plen-1;j >= 0 && t[i+j] == p[j];--j);
		 if(j == -1)
			 return i;
		 else
			 i++;		// 重新开始搜索
	}
	return -1;
}
/**
 * Knuth-Morris-Pratt搜索算法
 * next函数表的作用  当主串与模式串失配时 下次与模式串中比较字符的索引
 */
int KMPMatch(const string&text,const string &p) {
	int i = 0,j = 0;
	int tlen = text.length(),plen = p.length();
	std::vector<int>  next(plen,0);
	findNextV2(p,next); // 计算next函数表
	while(i < tlen && j < plen) {
		   if(j == -1 || text[i] == p[j]) {	// 第一个字符不想等 或者text[i]与p[j] 对应字符相等
			    ++i;
			    ++j;
		   }else {
			   j = next[j];			// i保持不变  j更新为next[j]  等效于将模式串右移j-next[j]位
		   }
	}
	if(j == plen)
		return i-j;
	else
		return -1;
}
/**
 * 计算模式串p的next表
 *
 */
void findNextV1(const string&p,vector<int>& next) {
      int k = -1,j = 0;
      int plen = p.length();
      next[0] = -1;
      while(j < plen-1) {
    	   if(k == -1 || p[k] == p[j]) {   //比较p[j]与p[k]  计算next[j+1]
    		   ++j;
    		   next[j] = ++k;
    	   }else {
    		   k = next[k];	// k指向下一个索引 j保持不变
    	   }
      }
}
/**
 * 计算模式串p的next表
 *  注意 如果p[j] == p[ next[j] ] 则可以设定next[j] = next[ next[j] ]
 */
void findNextV2(const string&p,vector<int>& next) {
      int k = -1,j = 0;
      int plen = p.length();
      next[0] = -1;
      while(j < plen-1) {
    	   if(k == -1 || p[k] == p[j]) {   //比较p[j]与p[k]  计算next[j+1]
    		   ++j;
    		   ++k;	// 无论如何保持k更新
    		   if(p[k] == p[j])   // 如果p[j] == p[k] 则应该修正next[j]
    			   	   next[j] = next[k];
    		   else
    			   	   next[j] = k;
    	   }else {
    		   	   k = next[k];	// k指向下一个索引 j保持不变
    	   }
      }
}
/***
 * Hancart算法
 * 匹配顺序为p1,p2,...pn-1,p0
 * 分p0与p1相不相等两种情况讨论
 * 待完善....
 */
int HancartMatch(const string&text,const string&p) {
      return -1;
}
/*
 * Boyer-Moore 算法
 * 坏字符表针对失配时主串字符a在模式串中最右位置 从而计算右移距离(变量是字符a)
 * 好后缀表针对失配时模式串位置i处应该移动多少距离(变量是位置i)
 *
 */
int BMMatch(const string&t,const string&p) {
	 int i = 0,j = 0;
	 int plen = p.length(),tlen = t.length();
	 const int ALPHABET_SIZE = 256;
	 vector<int> bmBc(ALPHABET_SIZE,plen),bmGs(plen,plen),suffix(plen,0);	// 默认坏字符和好后缀都存储模式串长度

	 //计算坏字符表 最后一个字符如果之前没有出现则为plen
     for(int i = 0;i < plen-1 ;++i)
    	 	 	 bmBc[p[i]] = plen-1-i;

     //计算好后缀表
     preComputeGs(p,suffix,bmGs);
     //printBMTables(p,bmBc,suffix,bmGs); // 输出中间表信息

     //使用坏字符表和好后缀表开始匹配字符串
     while( j <= tlen-plen) {
    	     for(i = plen-1; i >= 0 && t[j+i] == p[i];--i);
    	     if( i == -1)
    	    	 return j;  // 已经成功匹配
    	     else
    	    	 j += std::max(bmGs[i],bmBc[t[j+i]]-plen+1+i); // 相当于移动模式串 继续匹配
     }
	 return -1;
}
/**
 * 计算好后缀表
 * 表中表存的是 当在模式串i位置失配时 模式串应当移动的距离
 */
void preComputeGs(const string&p,vector<int>& suffix,vector<int>& bmGs) {
	    int i = 0,j = 0;
	    int plen = p.length();
		computeSuffixV1(p,suffix);//计算后缀表
		//先计算部分匹配的前缀情况 suffix[i] = i+1
        for( i = plen-1;i >= 0;--i)
        	if(suffix[i] == i+1)
        		for(;j < plen-i-1;++j)
        			  if(bmGs[j] == plen)
        				  bmGs[j] = plen-1-i;	// 移动的距离 只设置一次
		//再计算完全匹配的情况
        for(int i = 0;i < plen-1;++i)
        	  bmGs[plen-1-suffix[i]] = plen-1-i;
}
/***
 * 未优化版本
 * 计算位置i处前缀和模式串后缀匹配的最大长度
 * 当存在p[i-k+1..i] = p[m-k..m-1]时 suffix[i] = k
 * 不存在时suffix[i] = 0
 */
void computeSuffixV1(const string&p,vector<int>& suffix) {
	 string::size_type m = p.length();
	 suffix[m-1] = m;
	 for(string::size_type i = 0,k=0;i < m-1;++i) {
		   for(k = 0; i-k >=0 && p[m-1-k] == p[i-k];++k);
		   suffix[i] = k;
	 }
}
/**
 * 优化版本
 * 计算位置i处前缀和模式串后缀匹配的最大长度
 */
void computeSuffixV2(const string&p,vector<int>& suffix) {

}
/***
 * BM算法  输出中间表信息包括 坏字符表 好后缀表和后缀表
 */
void printBMTables(const string& p,vector<int>& bmBc,vector<int>& suffix,vector<int>& bmGs) {
	cout<<"bad character: "<<endl;
	int plen = p.length();
	for(vector<int>::size_type i = 0; i< bmBc.size();++i)
		if(bmBc[i] != plen)
				cout<<char(i)<<"-"<<bmBc[i]<<"\t";
	cout<<endl;
	cout<<"suffix: "<<endl;
	copy(suffix.begin(),suffix.end(),ostream_iterator<int>(cout,"\t"));
	cout<<endl;
	cout<<"good suffix: "<<endl;
	copy(bmGs.begin(),bmGs.end(),ostream_iterator<int>(cout,"\t"));
	cout<<endl;
}
