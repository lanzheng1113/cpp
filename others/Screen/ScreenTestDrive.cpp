#include <iostream>
#include "Screen.h"
#include "Window_Mgr.h"

using std::cout;
using std::endl;

int main()
{
	Screen myScreen(5,5);
	const Screen blank(5,5);
    Window_Mgr winMgr;
    
	winMgr.relocate(1,2,myScreen);
	myScreen.set('$');
	myScreen.display(cout);//调用非const版本display
	cout << endl;

	//调用 const版本display
	blank.display(cout);
	return 0;
}
