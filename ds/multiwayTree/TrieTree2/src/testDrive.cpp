/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: wangdq
 */
#include "trie.h"
#include "trie.cpp"
#include <iostream>

void testCase0();
void testCase1();

int main() {
    testCase0();
	return 0;
}
void testCase0() {
	TrieTree<int> trie;
	trie.insert("amy",56);
	trie.insert("ann",15);
	trie.insert("emma",30);
	trie.insert("rob",27);
	trie.insert("roger",52);
	trie.insert("a",100);
	trie.traverse();

   trie.remove("roger");
   trie.traverse();

   trie.insert("a",200);
   trie.traverse();

	int value;
	bool ret = trie.search("emma",value);
	if(ret) std::cout<<"emma: "<<value<<std::endl;


}
void testCase1() {
	TrieTree<int> trie;
	std::string words[] = {
			"be","bee","bear","are","beer",
			"area","air","blue","arrange","array"
	};
    for(int i=0;i<10;i++)
	      trie.insert(words[i],words[i].length());
	std::vector<std::string> strVec;
	std::string key = "a";
	trie.findSimilar(key,strVec);
	std::cout<<"Find "<<strVec.size()<<" similar word contain: "<<key<<std::endl;
	for(std::vector<std::string>::iterator it = strVec.begin();it != strVec.end();++it)
		 std::cout<<*it<<std::endl;
}

