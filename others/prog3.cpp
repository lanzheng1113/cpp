#include <iostream>
//c++�ַ�������ֵ�Ĵ���
//���е��ַ�������ֵ���ɱ������Զ���ĩβ���һ�����ַ�
int main()
{
	char a = 'a';//�����ַ� 1 byte
	wchar_t wb = L'b';//�������ַ�2 byte
	char c[] = "c";//2 byte
	wchar_t wd[] = L"d";//4 byte
	std::cout<<"sizeof(\'a\'):	"<<sizeof(a)<<std::endl;
	std::cout<<"sizeof(L\'b\'):	"<<sizeof(wb)<<std::endl;
	std::cout<<"sizeof(\"c\"):	"<<sizeof(c)<<std::endl;
	std::cout<<"sizeof(L\"d\"):	"<<sizeof(wd)<<std::endl;
	return 0;
}
