//读入未知数目的输入
#include <iostream>
int main()
{
	int sum = 0,value;
	//读入数据并计算其值，直到文件结束
	while(std::cin >> value)
	{
	      sum += value;
	}
    std::cout<<"Sum is:	"<<sum<<std::endl;
	return 0;
}