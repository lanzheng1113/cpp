#include <iostream>
//const与非const引用
int main()
{
	const int iSize = 1024;
	int iCnt = 0;
	const int &iRefval = iSize;//ok
	int &iRef = iSize;//不允许非const引用绑定到const对象
	const int &icRef = iCnt;//const引用可以绑定到右值
	std::cout<<"iRefval:	"<<iRefval<<std::endl;
	std::cout<<"icRef:	"<<icRef<<std::endl;
	return 0;
}
