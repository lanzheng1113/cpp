#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

//reinterpret_cast¾ÙÀı
int main(int argc, char *argv[])
{
	int ival = 12345600;
	int *ip = &ival;
	char *pc = reinterpret_cast<char*>(ip);
	string str(pc);
	cout<<*(pc+1)<<" "<<*(pc+2)<<endl;
    cout<<str<<endl;
	return 0;
}
