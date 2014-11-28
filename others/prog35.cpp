#include <iostream>
#include <vector>
#include <exception>
using std::cout;
using std::vector;
using std::cerr;
using std::endl;

//容器元素访问
//使用越界的下标、或者调用空容器的front或者back函数
//都会出现严重的运行错误

int main()
{
	vector<int> svec;
	//cout << svec[0];//run-time -error
	try
	{
		cout << svec.at(0);//Error: invalid vector<T> subscript
	}
	catch(std::out_of_range or)  
	{  
		cerr << "Error: "<<or.what()<<endl;  
	}  
	catch (std::runtime_error err)  
	{    
		cerr << "Error: "<<err.what()<<endl;  
	}  
	catch(std::exception ex)  
	{  
		cerr << "Error: "<<ex.what()<<endl;  
	}
	return 0;
}
