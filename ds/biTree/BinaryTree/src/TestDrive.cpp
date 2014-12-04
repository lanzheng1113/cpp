/*
 * TestDrive.cpp
 *
 *  Created on: 2014年12月2日
 *      Author: wangdq
 */
#include <iostream>
#include "bst.h"
#include "bst.cpp"
#include <stdlib.h>     /* srand, rand */

int main(int argc,char** argv) {
	  int elements[] = {13,10,25,2,12,20,31,29};
	 BST<int> bst;
	 for (int * begin = elements;begin != elements+8 ;++begin) {
		  bst.insert(*begin);
	 }
     bst.inorder();
     std::cout<<"\n\n";
     bst.findAndDeleteByCopying(25);
     std::cout<<"\n\n";
     bst.inorder();
	 return 0;
}
void testTraverse() {
	int time = 30;
		 for(int i = 0;i < time ;i++) {
			 int count = random() % 100+1;
			 int *elements = new int[count];
			 int last = -1;
			 for(int j = 0;j< count;j++) {
				int random = rand() % 100+1;
				while(last == random) {
					last = random;
					random = rand() % 100+1;
				}
				elements[j] = random;
			 }
			 BST<int> bst;
			 for (int * begin = elements;begin != elements+count ;++begin) {
				  bst.insert(*begin);
			 }
			 std::cout<<"\n\n";
			 bst.preorder();
			 std::cout<<"\n\n";
			 bst.inorder();
			 std::cout<<"\n\n";
			 bst.postorder();
			 std::cout<<"\n\n";
			 delete[] elements;
		 }
}
