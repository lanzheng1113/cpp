/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: wangdq
 */
#include "trie.h"
#include "trie.cpp"
#include <iostream>

int main() {
	TrieTree<int> trie;
    trie.insert("amy",56);
    trie.insert("ann",15);
    trie.insert("emma",30);
    trie.insert("rob",27);
    trie.insert("roger",52);
    trie.insert("a",100);
    trie.traverse();

   //trie.remove("roger");
   trie.traverse();

   trie.insert("a",200);
   trie.traverse();

    int value;
    bool ret = trie.search("emma",value);
    if(ret) std::cout<<"emma: "<<value<<std::endl;

	return 0;
}



