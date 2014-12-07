/*
 * testDrive.cpp
 *
 *  Created on: 2014年12月3日
 *      Author: wangdq
 */
#include "biThreadedTree.h"
#include "biThreadedTree.cpp"

int main() {
    int elements[] = {13,10,25,2,12,20,31,29};
    BiThreadedTree<int> btt;
   for(int *begin = elements;begin != elements+8;++begin) {
    	btt.insert(*begin);
    }
    btt.inorder();
}


