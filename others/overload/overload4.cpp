#include <iostream>
using namespace std;

int IntFunc() { return 0; }
char CharFunc() { return 0; }

void FuncFunc(int(*func)()) { cout << "int\n"; }
void FuncFunc(char(*func)()) { cout << "char\n"; }


int main()
{
    FuncFunc(&IntFunc); // calls void FuncFunc(int_func func)
    FuncFunc(&CharFunc); // calls void FuncFunc(char_func func)
}
