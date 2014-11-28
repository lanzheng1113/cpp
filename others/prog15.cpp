#include <iostream>
using std::cout;
//const_cast¾ÙÀı
void print (char * str)
{
  cout << str << '\n';
}
int main()
{
	const char * c = "sample text";
    print ( const_cast<char *> (c));//ÒÆ³ıconstĞÔÖÊ
	return 0;
}
