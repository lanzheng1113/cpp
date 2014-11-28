#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::endl;
//const成员函数和重载举例

class Screen {
public:
	typedef std::string::size_type index;
	Screen(index ht = 0, index wd = 0): 
                  contents(ht * wd, ' '), cursor(0), 
                  height(ht), width(wd) { }
	Screen& set(char c){contents[cursor] = c;return *this;}
	//通过是否为const成员函数实现重载
	Screen& display(std::ostream &os)
		{do_display(os);return *this;}
    const Screen& display(std::ostream &os) const
		{do_display(os);return *this;}
private:
	void do_display(std::ostream &os) const
		{os<<contents;}
private:
	std::string	contents;
	index	cursor;
	index	height,width;
};
int main()
{
    Screen myScreen(1,2);
	const Screen blank(5,3);

    //调用非const版本display
	myScreen.display(cout).set('#').display(cout);
	cout << endl;

	//调用 const版本display
	blank.display(cout);
	return 0;
}