#include <iostream>
#include "global.h"	//include the global header file
int main()
{
	g_cnt++;
	std::cout<<"global variable g_cnt:	"<<g_cnt<<std::endl;
	std::cout<<"global const gc_PI:	"<<gc_PI<<std::endl;
	std::cout<<"circle Area of radius 1.0 is:	"<<calcArea(1.0)<<std::endl;
	return 0;
}
