#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//const引用形参举例
//非const引用形参只能与完全同类型的非const对象关联
std::size_t find_char(string &s,char c)
{
   string::size_type i = 0;
   while(i != s.size() && s[i] != c)
	   ++i;
   if(i == s.size())
	   return string::npos;
   else
	   return i;
}
int main(int argc, char *argv[])
{   
	//字面值常量为const对象，调用出错
	if(find_char("Hello, world.",'.') != string::npos)
	{
		cout<<"a sentence."<<endl;
	}
	return 0;
}
