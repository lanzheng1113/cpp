#include <iostream>
//ָ��const�����ָ���constָ��
int main()
{   
	const double pi = 3.14;
	double exp = 2.718;
	const double *cptr;//ָ��const�����ָ�룬�ڶ���ʱ��ǿ�Ƴ�ʼ��
	cptr = &pi;
	std::cout<<*cptr<<std::endl;
	cptr = &exp;//�������°󶨵���һ��const����
	std::cout<<*cptr<<std::endl;

	//double *ptr = &pi;//����,�޷��ӡ�const double *��ת��Ϊ��double *��
	//void *pv = &pi;//����,�޷��ӡ�const double *��ת��Ϊ��void *��
	const void *cpv = &pi;//ʹ��const void*����const����ĵ�ַ
	std::cout<<*((double*)cpv)<<std::endl;
    
    double *const cpd =&exp;//constָ��
    *cpd = 2.7;//ͨ��cosntָ���޸�ԭ�����ֵ
	std::cout<<exp<<std::endl;
	//cpd = &exp;//����,���ܸ�������ֵ
    
	const double *const cptr_cd = &pi;//ָ��const�����constָ��
    std::cout<<*cptr_cd<<std::endl;

	return 0;
}
