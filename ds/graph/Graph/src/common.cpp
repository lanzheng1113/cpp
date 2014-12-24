/*
 * common.cpp
 *
 *  Created on: 2014年12月24日
 *      Author: wangdq
 */
#include <iostream>
#include "common.h"

bool Util::skipStreamComment(std::istream & stream) {
	char next = stream.peek();//see std::istream::peek
	if(next != '/')
		   return true;
   char ch;
   stream >> ch; //consume '/'
   stream >> ch; //consume '*'
   while(stream >> ch)
	   if(ch == '*' && stream.peek() == '/') //successfully match
	   {
		   stream >> ch;	//consume '/'
		   return true;
	   }
   //file end not match,then error
   std::cerr<<"graph file format error,comment not matching."<<std::endl;
   return false;
}
