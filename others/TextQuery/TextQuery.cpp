#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <exception>

class TextQuery {  
public:
    typedef std::set<int>::size_type size_type;
	typedef std::set<int>::const_iterator lineno_it;
    TextQuery(const std::string& filename)
	{
		init(filename);
    }
	//查询单词，并将结果输出到流中
    void query(std::ostream &os,const std::string& word)
	{   
		std::set<int> lineno_set = word_map[word];
        size_type cnt = lineno_set.size();
		if(cnt == 0)
		{
			os << "'" << word << "' not found!" << std::endl;
		}
		else 
		{   
			std::string suffix = cnt > 1 ? "times":"time";
			os << word << " occurs " << cnt<<" "<<suffix << std::endl;
			
			for(lineno_it beg = lineno_set.begin(),
				end = lineno_set.end(); beg != end;++beg )
		    {
			   os<< "(line" << *beg+1 <<") "
					 << content_inline[*beg]<<std::endl;
			}
		}
	}
private:
	void init(const std::string& filename)
	{
	  std::ifstream stream;
	  if(!open_file(stream,filename))
		  throw std::runtime_error("could not open file for reading.");
	  std::string line;
	  int linecnt = 0;
      while(getline(stream,line))
	  {
		content_inline.push_back(line);//存储行内容
        std::istringstream iss(line);
		std::string word;
		while(iss >> word)
		{  
		   word_map[word].insert(linecnt);//着重注意此行,存储行中单词
		}
		++linecnt;
	  }
	  stream.close();
    }
	std::ifstream& open_file(std::ifstream& stream,const std::string &filename)
	{
		
		stream.close();
	    stream.clear();

		stream.open(filename.c_str());
	    return stream;
	}
private:
	std::vector<std::string> content_inline;//按行存储的内容
	std::map<std::string,std::set<int>> word_map;//单词-行号集合映射表
};

int main(int argc, char *argv[])
{
   if(argc != 2)
	   throw std::runtime_error("illegal argument.");
   TextQuery txtQuery(argv[1]);
   std::cout << "input a word to query:	" << std::endl;
   std::string word;
   while(std::cin >> word)
   {
     txtQuery.query(std::cout,word);
   }
   return 0;
}

