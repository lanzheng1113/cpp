#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//const�����βξ���
//��const�����β�ֻ������ȫͬ���͵ķ�const�������
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
	//����ֵ����Ϊconst���󣬵��ó���
	if(find_char("Hello, world.",'.') != string::npos)
	{
		cout<<"a sentence."<<endl;
	}
	return 0;
}
