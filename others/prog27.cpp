#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::endl;
//const��Ա���������ؾ���

class Screen {
public:
	typedef std::string::size_type index;
	Screen(index ht = 0, index wd = 0): 
                  contents(ht * wd, ' '), cursor(0), 
                  height(ht), width(wd) { }
	Screen& set(char c){contents[cursor] = c;return *this;}
	//ͨ���Ƿ�Ϊconst��Ա����ʵ������
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

    //���÷�const�汾display
	myScreen.display(cout).set('#').display(cout);
	cout << endl;

	//���� const�汾display
	blank.display(cout);
	return 0;
}