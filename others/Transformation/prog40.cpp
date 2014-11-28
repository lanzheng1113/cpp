#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <exception>

using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::make_pair;
using std::runtime_error;

//map使用举例-单词转换程序
//argv[1] argv[2]分别是转换表文件和源文件
ifstream& open_file(ifstream &in,const string &file)
{
	in.close();
	in.clear();
    in.open(file.c_str());
    return in;
}

int main(int argc, char *argv[])
{
	map<string,string> trans_map;//转换映射表
	string key,value;
	if(argc != 3)
		throw runtime_error("Wrong number of arguments");
    //open transformation file and check that open succeeded
	ifstream map_file;
	if(!open_file(map_file,argv[1]))
		throw runtime_error("no transformation file!");
	//build transformation map
	while(map_file >> key >> value)
		trans_map.insert(make_pair(key,value));
	ifstream input;
	if(!open_file(input,argv[2]))
		throw runtime_error("no input file!");
	string line;
	while(getline(input,line))
	{  
	   //process one line
	   istringstream stream(line);
	   string word;
	   bool firstword = true;
	   while(stream >> word)
	   {
		   map<string,string>::const_iterator map_it =
			   trans_map.find(word);
		   //if this word is in the transformation map
		   if(map_it != trans_map.end())
			   //replace it by the transformation value in the map
			   word = map_it->second;
		   if(firstword)
		   {
			   firstword = false;
		   }
		   else
		   {
			   cout<<" ";
		   }
		   cout << word;
	   }
	   cout << endl;//new line
	}
	return 0;
}
