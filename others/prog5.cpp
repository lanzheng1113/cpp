#include <iostream>
//const���ð󶨵���ͬ��������͵Ķ���
int main()
{
	double dVal = 3.14;
	const int &ri = dVal;
	//int &ref = dVal;//error,�޷��ӡ�double��ת��Ϊ��int &��
	std::cout<<"ri:	"<<ri<<std::endl;//print 3
	std::cout<<"dVal:	"<<dVal<<std::endl;//print 3.14
	return 0;
}
