#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
//��ʹ�þ���3-�ļ������ַ�����ʹ��
int main()
{
	//�ļ�������󶨵��ļ�
	string strfileName("data.dat");
	ofstream outfile(strfileName.c_str());
    if (!outfile)
    {
        
        cerr << "Could not open file for writing!" << endl;
        exit(1);
    }
    outfile<<"The quick fox jump over the lazy dog."<<endl;
	ifstream infile;
	infile.open(strfileName.c_str());
	if(infile) 
	{  
	   string line,word;
		//���д���
	   while(getline(infile,line))
		{   
		    istringstream stream(line);//�����ַ�����
			//�����ʴ���
			while(stream>>word)
			{
			    cout<<word<<" ";
			}
	    }
	}
	return 0;
}
