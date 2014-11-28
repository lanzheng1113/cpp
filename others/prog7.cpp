#include <iostream>
//字符数组的初始化
int main()
{
	char ca1[] = {'c','+','+'};
	char ca2[] = {'c','+','+','\0'};//显式包含空字符
	char ca3[] = "c++";//自动添加一个额外的空字符
	std::cout<<"sizeof(ca1):	"<<sizeof(ca1)<<std::endl;//print 3
	std::cout<<"sizeof(ca2):	"<<sizeof(ca2)<<std::endl;//print 4
	std::cout<<"sizeof(ca3):	"<<sizeof(ca3)<<std::endl;//print 4
	return 0;
}
