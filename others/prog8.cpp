#include <iostream>
//ע�����ָ��
int main()
{
	
	int ival = 1024;
	int *pi = &ival;
	int **ppi = &pi;
	//��ַ
	std::cout<<"address of ival:	"<<&ival<<std::endl;
	std::cout<<"address of pi:	"<<&pi<<std::endl;
	std::cout<<"address value of ppi:	"<<*ppi<<std::endl;
	std::cout<<"address of ppi:	"<<&ppi<<std::endl;
	//������
	std::cout<<"direct value:	"<<ival<<std::endl;//ֱ��ֵ
	std::cout<<"indirect value:	"<<*pi<<std::endl;//һ�ν�����
	std::cout<<"double indirect value :	"<<**ppi<<std::endl;//���ν�����
	return 0;
}
