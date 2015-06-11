#include<iostream>
using namespace std;
class Test{
private:

	int x;
	int y;
public:

	Test(int x = 0, int y = 0) { std::cout << "Called " << std::endl; this->x = x; this->y = y; }
	void setX(int a) { x = a; }
	void setY(int b) { y = b; }
	void destroy() {
		this ->y= 100; 
	   	std::cout << "address of this " << this << std::endl; 
	 	delete this;
	}
	void print() { cout << "x = " << x << " y = " << y << endl; }
	void testf() { cout << x << y << endl;}
};

int main()
{

	Test *obj = new Test;
	obj->setX(10);
	obj->print();
	std::cout << "address of obj " << obj << std::endl;
	obj->destroy();
	std::cout << "address of obj " << obj << std::endl;
	obj->print();
	std::cout << "address of obj " << obj << std::endl;
	obj->setX(10);
	obj->testf();
	return 0;

}
