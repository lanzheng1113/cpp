#include <iostream>
//指向const对象的指针和const指针
int main()
{   
	const double pi = 3.14;
	double exp = 2.718;
	const double *cptr;//指向const对象的指针，在定义时不强制初始化
	cptr = &pi;
	std::cout<<*cptr<<std::endl;
	cptr = &exp;//允许重新绑定到另一个const对象
	std::cout<<*cptr<<std::endl;

	//double *ptr = &pi;//错误,无法从“const double *”转换为“double *”
	//void *pv = &pi;//错误,无法从“const double *”转换为“void *”
	const void *cpv = &pi;//使用const void*保存const对象的地址
	std::cout<<*((double*)cpv)<<std::endl;
    
    double *const cpd =&exp;//const指针
    *cpd = 2.7;//通过cosnt指针修改原对象的值
	std::cout<<exp<<std::endl;
	//cpd = &exp;//错误,不能给常量赋值
    
	const double *const cptr_cd = &pi;//指向const对象的const指针
    std::cout<<*cptr_cd<<std::endl;

	return 0;
}
