#include <iostream>
//c++字符串字面值的处理
//所有的字符串字面值都由编译器自动在末尾添加一个空字符
int main()
{
	char a = 'a';//单个字符 1 byte
	wchar_t wb = L'b';//单个宽字符2 byte
	char c[] = "c";//2 byte
	wchar_t wd[] = L"d";//4 byte
	std::cout<<"sizeof(\'a\'):	"<<sizeof(a)<<std::endl;
	std::cout<<"sizeof(L\'b\'):	"<<sizeof(wb)<<std::endl;
	std::cout<<"sizeof(\"c\"):	"<<sizeof(c)<<std::endl;
	std::cout<<"sizeof(L\"d\"):	"<<sizeof(wd)<<std::endl;
	return 0;
}
