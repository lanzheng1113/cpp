#include <iostream>
//const引用绑定到不同但相关类型的对象
int main()
{
	double dVal = 3.14;
	const int &ri = dVal;
	//int &ref = dVal;//error,无法从“double”转换为“int &”
	std::cout<<"ri:	"<<ri<<std::endl;//print 3
	std::cout<<"dVal:	"<<dVal<<std::endl;//print 3.14
	return 0;
}
