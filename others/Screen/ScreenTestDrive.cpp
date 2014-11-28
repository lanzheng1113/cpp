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
	myScreen.display(cout);//���÷�const�汾display
	cout << endl;

	//���� const�汾display
	blank.display(cout);
	return 0;
}
