#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//��ʹ�þ���1-���ļ̳���
ostream & out(ostream& outstream,string &content)
{
   return outstream << content<<endl;
}
int main()
{
	ofstream outfile("sample.dat");
	string str("Sunny morning.");
	ostringstream strstram;

	if(!outfile)
	{
	   cout<<"could not open file for writing."<<endl;
	   exit(1);
	}
	
	out(cout,str);//write to console

    out(outfile,str);//write to file
	outfile.close();

    out(strstram,str);//write to string stream
	cout<<"content of stringsream:	"<<strstram.str()<<endl;
	
	return 0;
}
