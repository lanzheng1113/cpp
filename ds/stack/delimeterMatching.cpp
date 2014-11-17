#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

bool delimeterMatching(istream& in);
bool delimeterMatching2(istream& in);
void dealWithSlash(istream& in);

int main(int argc, char *argv[])
{   
	ifstream in("1.txt");
	if(!in)
	{
		std::cerr<<"could not open file for reading."<<std::endl;
		return 0;
	}
	std::cout<<"------source contents-----"<<std::endl;
	string line;
	while(getline(in,line))
		std::cout<<line<<std::endl;
    std::cout<<"-----analysis process -----"<<std::endl;
	in.clear();
	in.seekg(istream::beg);	//see std::basic_istream::seekg
	std::cout<<"dose it match ?: "<<
		(delimeterMatching2(in)?"Yes!":"No!")<<std::endl;
	return 0;
}
void dealWithSlash(istream& in)
{
	char next = in.peek();//see std::istream::peek
	char ch;
    if(next == '*')		// "match: /* and */"
    {  
	   in >> ch; //consume '*'
	   while(in >> ch)
	   {   
		   next = in.peek();
		   if(ch == '*' && next == '/') //successfully match 
		   {
			   in >> ch;	//consume '/'
			   std::cout<<"match: /* and */"<<std::endl;
			   return;  
		   }
	   }
	   //file end not match,then error
	   std::cout<<"unmatched: /* and */"<<std::endl;
    }
}
bool delimeterMatching2(istream& in)
{
    stack<char> stack;
    char ch;
	string leftPart("([{");
	string rigthPart(")]}");
	while(in >> ch)
	{   
		if(ch == '/')	// deal with '/'
		{
		   dealWithSlash(in);
		}else if(leftPart.find(ch) != std::string::npos) //one of left mark
		{
			stack.push(ch);
			std::cout<<"push: "<<ch<<std::endl;
		}else if(rigthPart.find(ch) != std::string::npos) // one of right mark
		{   
			if(!stack.empty() && 
				leftPart.find(stack.top()) == rigthPart.find(ch)) 
			{   
				std::cerr<<"match: "<<stack.top()<<" and "<<ch<<std::endl;
				stack.pop(); // right match the stack top ,then pop
			}else
			{   
				std::cerr<<"unexpected chracter: '"<<ch<<"'"<<std::endl;
				return false;// not match,return false
			}
		}
	}
    return stack.empty();
}
bool delimeterMatching(istream& in)
{   
    stack<char> stack;
    char ch;
	string leftPart("([{");
	string rigthPart(")]}");
	while(in >> ch)
	{   
		if(leftPart.find(ch) != std::string::npos)
		{
			stack.push(ch); // left part just push
		}else if(rigthPart.find(ch) != std::string::npos)
		{   
			if(!stack.empty() && 
				leftPart.find(stack.top()) == rigthPart.find(ch)) 
			{
				stack.pop(); // right match the stack top ,then pop
			}else
			{
				return false;// not match,return false
			}
		}
	}
    return stack.empty();
}
//http://en.cppreference.com/w/cpp/io/basic_istream/seekg
//http://www.cplusplus.com/reference/istream/istream/peek/