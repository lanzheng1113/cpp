#include "Screen.h"

Screen& Screen::set(char c)
{
	contents[cursor] = c;
	//this此处是一个指向非常量Screen指针
	//对其解引用来访问this所指向的对象
	return *this;
}
Screen& Screen::move(index r,index c)
{
	index row = r * width;
	cursor = row + c;
	return *this;
}
Screen& Screen::set(index r, index c, char ch)
{
    index row = r * width; 
    contents[row + c] = ch;
    return *this;
}

char Screen::get(index r, index c) const
{
    index row = r * width;
    return contents[row + c];
}