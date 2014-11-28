#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
//流使用举例3-文件流与字符串流使用
int main()
{
	//文件流对象绑定到文件
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
		//按行处理
	   while(getline(infile,line))
		{   
		    istringstream stream(line);//构造字符串流
			//按单词处理
			while(stream>>word)
			{
			    cout<<word<<" ";
			}
	    }
	}
	return 0;
}
