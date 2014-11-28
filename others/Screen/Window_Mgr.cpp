#include "Window_Mgr.h"
#include "Screen.h"

//友元类访问授予友元关系的类的非公有成员
Window_Mgr&  Window_Mgr::relocate(Screen::index r,
				Screen::index c ,Screen& s)
{
	s.height += r;
	s.width += c;
	return *this;
}