#include <iostream>
#include <vector>
#include <stack>
using std::vector;
using std::stack;
using std::cout;

int main()
{
	stack<int ,vector<int>> istack;
	istack.push(2);
	istack.push(5);
	istack.push(7);
	cout<<istack;
	return 0;
}
