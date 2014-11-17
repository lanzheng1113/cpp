#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

int pr(char ch);
string infixToPostfix(string infix);

int main(int argc, char *argv[])
{   
	//string infix("A+(B*C-(D/E-F)*G)*H");	//ABC*DE/F-G*-H*+
	//string infix("(3-4)*5");	//34-5*
	string infix("A * (B + C * D) + E");	//A B C D * + * E +
	cout<<"infix expr is: " <<infix<<endl;
	cout<<"postifx expr is: "<<infixToPostfix(infix)<<endl;
	return 0;
}
int pr(char ch)
{
	switch(ch)
	{
		case '#':
			return 0;
		case '(':
			 return 1;
		case '+':
		case '-':
			 return 2;
		case '*':
		case '/':
			 return 3;
	}
	return -1;
}
string infixToPostfix(string infix)
{
	stack<char> stack;
	istringstream instream(infix);
	ostringstream postfix;
	char ch;

	stack.push('#');//push '#' as stack empty mark

	while(instream >> ch)
	{
		if(std::isalnum(ch)) //if is operand
		{
			postfix << ch;
		}else	// if it is operator
		{
			if(ch == '(') 
			{
				stack.push(ch);
			}else if(ch == ')')	// pop until meet '('
			{
				while(stack.top() != '(' )
				{
					postfix << stack.top();
					stack.pop();
				}
				stack.pop();
			}else 
			{   
				while(pr(stack.top()) >= pr(ch))
				{
					postfix << stack.top();
					stack.pop();
				}
				stack.push(ch);
			}
		}
	}
	while(stack.top() != '#')
	{
		postfix << stack.top();
		stack.pop();
	}
    return postfix.str();
}