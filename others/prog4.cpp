#include <iostream>
//const���const����
int main()
{
	const int iSize = 1024;
	int iCnt = 0;
	const int &iRefval = iSize;//ok
	int &iRef = iSize;//�������const���ð󶨵�const����
	const int &icRef = iCnt;//const���ÿ��԰󶨵���ֵ
	std::cout<<"iRefval:	"<<iRefval<<std::endl;
	std::cout<<"icRef:	"<<icRef<<std::endl;
	return 0;
}
