#include <iostream>
//注意理解指针
int main()
{
	
	int ival = 1024;
	int *pi = &ival;
	int **ppi = &pi;
	//地址
	std::cout<<"address of ival:	"<<&ival<<std::endl;
	std::cout<<"address of pi:	"<<&pi<<std::endl;
	std::cout<<"address value of ppi:	"<<*ppi<<std::endl;
	std::cout<<"address of ppi:	"<<&ppi<<std::endl;
	//解引用
	std::cout<<"direct value:	"<<ival<<std::endl;//直接值
	std::cout<<"indirect value:	"<<*pi<<std::endl;//一次解引用
	std::cout<<"double indirect value :	"<<**ppi<<std::endl;//二次解引用
	return 0;
}
