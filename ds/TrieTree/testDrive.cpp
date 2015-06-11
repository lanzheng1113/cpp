/*
 * testDrive.cpp
 *
 *  Created on: 2015年5月25日
 *      Author: wangdq
 */
#include <iostream>
#include <string>
#include "trie_array.h"
#include "trie_array.cpp"


int main() {
	TrieTree<int> trie;
	std::string keys[] = {"amy", "ann","emma", "rob", "roger"};
	int values[] = {56,15,30,27,52};
	for(int i=0;i < sizeof(values) / sizeof(int);++i) {
		std::cout << "put :" << values[i] << std::endl;
		trie.put(keys[i], values[i]);
		trie.traverse();
		std::cout << std::endl;
	}
	trie.traverse();
	std::cout << std::endl;
    int value = 0;
    bool ret = trie.search("emma",value);
    if(ret)
    	std::cout<<"emma: "<<value<<std::endl;
    std::cout << "remove value: rob" << std::endl;
    trie.remove("rob");
    trie.traverse();
    std::cout << std::endl;
    std::cout << "update value" << std::endl;
    trie.put("roger",48);		// update
    trie.put("amy",65);	// update
    trie.traverse();
	std::cout << std::endl;
	return 0;
}



