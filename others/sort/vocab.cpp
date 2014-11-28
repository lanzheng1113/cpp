#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

using std::string;
using std::runtime_error;
using std::ifstream;
using std::ostream_iterator;
using std::istringstream;
using std::cout;
using std::endl;
using std::vector;

//������ͯ���������õ���

//������������
bool isShorter(const string& s1,const string& s2)
{
   return s1.size() < s2.size();
}
bool GT6(const string& s)
{
   return s.size() >= 6;
}
//���ļ���
std::ifstream& open_file(std::ifstream& stream,const std::string &filename)
	{
		
		stream.close();
	    stream.clear();

		stream.open(filename.c_str());
	    return stream;
	}
//��ȡ�ļ��е���
void getWords(vector<string> &wordsVec,vector<string>& fileNames)
{   
     for(vector<string>::iterator beg =fileNames.begin(),
		 end = fileNames.end();beg != end; ++beg )
	 {
	      ifstream stream;
		  if(!open_file(stream,*beg))
			  throw runtime_error("could not open file for reading.");
		  string line;
	      while(getline(stream,line))
		  {   
			  istringstream iss(line);
			  string word;
			  while(iss >> word)
			  {
                wordsVec.push_back(word);
			  }
		 }
	 }
}
int main(int argc, char *argv[])
{
	if(argc < 2)
        throw runtime_error("illegal arguments.");
    vector<string> wordsVec;
    vector<string> filenames(argv+1,argv+argc);//ע���������Χ
	getWords(wordsVec,filenames);
	//ȥ���ظ�
	sort(wordsVec.begin(),wordsVec.end());//������
	vector<string>::iterator end_unique =
		   unique(wordsVec.begin(),wordsVec.end());
	wordsVec.erase(end_unique,wordsVec.end());//ɾ���ظ�Ԫ��
    
	//����������
	stable_sort(wordsVec.begin(),
		wordsVec.end(),isShorter);
    //�������ȴ���6�ĵ���
	vector<string>::size_type wc =count_if(
		wordsVec.begin(),wordsVec.end(),GT6);
	cout << wc << " "<< (wc >1 ? "words":"word")
		 << " 6 characters or longer." << endl;
	return 0;
}
