#include <iostream>
//�ַ�����ĳ�ʼ��
int main()
{
	char ca1[] = {'c','+','+'};
	char ca2[] = {'c','+','+','\0'};//��ʽ�������ַ�
	char ca3[] = "c++";//�Զ����һ������Ŀ��ַ�
	std::cout<<"sizeof(ca1):	"<<sizeof(ca1)<<std::endl;//print 3
	std::cout<<"sizeof(ca2):	"<<sizeof(ca2)<<std::endl;//print 4
	std::cout<<"sizeof(ca3):	"<<sizeof(ca3)<<std::endl;//print 4
	return 0;
}
