#include <iostream>
using std::cout;
//const_cast����
void print (char * str)
{
  cout << str << '\n';
}
int main()
{
	const char * c = "sample text";
    print ( const_cast<char *> (c));//�Ƴ�const����
	return 0;
}
