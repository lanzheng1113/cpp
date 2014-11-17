#include <iostream>
#include <string>
#include <stack>
#include <math.h>

using namespace std;

string decimalTo(int q,int desBase);
string toDecimal(string src,int base);

int main(int argc, char *argv[])
{   
	
	cout<<"1011(2) to decimal: "<<toDecimal("1011",2)<<endl;
	cout<<"7E(16) to decimal: "<<toDecimal("7E",16)<<endl;
	cout<<"124(8) to decimal: "<<toDecimal("124",8)<<endl;

	cout<<"45(10) to binary: "<<decimalTo(45,2)<<endl;
	cout<<"84(10) to octal: "<<decimalTo(84,8)<<endl;
	cout<<"99(10) to hexadecimal: "<<decimalTo(99,16)<<endl;
	return 0;
}
string decimalTo(int q,int desBase)
{
	stack<int> stack;
	string des;
	do
	{  
	   stack.push(q % desBase);// push remainder
       q = q / desBase; // update quotient
	}
	while (q > 0);
    while(!stack.empty())
	{
		des +=  std::to_string(stack.top());
        stack.pop();
	}
	return des;
}
string toDecimal(string src,int base)
{
	int n = src.length();
	int des = 0;
	while(n > 0)
	{  
	   // convert char to num according to base
	   // see  substr and std::stoi
	   string str = src.substr(src.length()-n,1);
       des += std::stoi(str,0,base)*pow(base,n-1);
	   n--;
	}
	return std::to_string(des);
}

