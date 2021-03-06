#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

int getPred(char ch);
string infixToPostfix(string infix);
int evalPostfix(string postfix);
int evalInfix1(string infix);
int evalInfix2(string infix);
void evalTwoNumber(stack<int> &opdStack,stack<char> &oprStack);
int evalTwoNumber(int op1,int op2,char oper);

int main(int argc, char *argv[])
{   
	//------------evaluate postfix expr----------------
	string postfixArray[] = {
		"34-5*" //-5
	};
	for(string& postfix : postfixArray)
		std::cout<<"evaluate postfix "<<postfix
		<<" = "<<evalPostfix(postfix)<<std::endl;
	std::cout<<std::endl;
	//------------evaluate infix expr----------------
	string infixArray[] = {
		"5+((1 + 2)*4)-3"  //14
		, "2*3-8/4-4*5" //-16
		, "((2*4-6/3)*(3*5+8/4))-(2+3)" //97
	};
	for(string& infix :infixArray)
	{   
		std::cout<<"evaluate infix (convert to postfix) "<<infix
			<<" = "<<evalInfix1(infix)<<std::endl;
		std::cout<<"evaluate infix (one pass) "<<infix
			<<" = "<<evalInfix2(infix)<<std::endl;
	}
	return 0;
}
int getPred(char ch)
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
int evalTwoNumber(int op1,int op2,char oper)
{   
	int result = 0;
	switch(oper)
	{
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
		case '*':
			result = op1 * op2;
			break;
		case '/':
			result = op1 / op2;
			break;
	}
	return result;
}
void evalTwoNumber(stack<int> &opdStack,stack<char> &oprStack)
{   
	//get two number fron operand stack
	int op1 = opdStack.top();
	opdStack.pop();
	int op2 = opdStack.top();
	opdStack.pop();
    //get operator from operator stack
	char oper = oprStack.top();
	oprStack.pop();

	// mind the operand order
	opdStack.push(evalTwoNumber(op2,op1,oper));
}
int evalInfix2(string infix)
{
	stack<int>  opdStack;
    stack<char> oprStack;
    istringstream instream(infix);
	string opers = "+-*/";
	char ch;

	oprStack.push('#'); // push '#' as empty mark

	while(instream >> ch)
	{
		if(std::isdigit(ch)) //operand 
		{
			opdStack.push(ch-'0');
		}else if(ch == '(')	//opening brace
		{
             oprStack.push(ch);
		}else if(ch == ')') //closing brace
		{
			while(!oprStack.empty() && oprStack.top() != '(')
				evalTwoNumber(opdStack,oprStack);
            oprStack.pop(); // pop '('
		}else if(opers.find(ch) != std::string::npos) //operator
		{
			while(!oprStack.empty() && 
				getPred(oprStack.top()) >= getPred(ch))
				evalTwoNumber(opdStack,oprStack);
			oprStack.push(ch);//push operator
		}
	}
    while(oprStack.top() != '#')
		evalTwoNumber(opdStack,oprStack);
	return opdStack.top();
}
int evalInfix1(string infix)
{   
	return evalPostfix(infixToPostfix(infix));
}
int evalPostfix(string postfix)
{
	stack<int> stack;
	istringstream instream(postfix);
	char ch;
	string opers = "+-*/";
    while(instream >> ch)
	{
		if(opers.find(ch) != std::string::npos) //operator
		{
			int op1 = stack.top();
			stack.pop();
			int op2 = stack.top();
			stack.pop();
			stack.push(evalTwoNumber(op2,op1,ch)); // mind the operand order
		}else	// operand
		{   
			stack.push(ch-'0');
		}
	}
	return stack.top();
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
				while(getPred(stack.top()) >= getPred(ch))
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