#include <iostream>
#include <string>
//注意利用标准库的配套类型
int main()
{
	std::string str("abcdef");
	std::string::size_type iPos = str.find("cd");
	if(iPos != std::string::npos)
		std::cout << "'cd' found at: " << iPos <<std::endl;
	return 0;
}
