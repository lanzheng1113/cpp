#include <iostream>
#include <string>
#include <vector>
using namespace std;

void permutation(string input,vector<string> &result);

int main(int argc,char** argv)
{ 
  vector<string> result;
  string input = "abc";
  if(argc == 2)
  {
     input = string(argv[1]);
  }
  permutation(input,result);
  std::cout<<"Permutation of: "<<input<<" ,kind: "<<result.size()<<std::endl;
  for(vector<string>::iterator it = result.begin();it != result.end();++it)
      std::cout<<*it<<std::endl;
}
// permutation the input string and save it to result
void permutation(string input,vector<string> &result)
{  
   if(input.length() == 1)
   {
      result.push_back(input);
      return;
   }
   for(string::size_type i= 0;i < input.length();++i)
   { 
        string leftPart = input;
        leftPart.erase(i,1);//get left part
        vector<string> strVec; 
        permutation(leftPart,strVec);// use  left part to permutate
        // add this char with left part result
        for(vector<string>::iterator it = strVec.begin();it != strVec.end();++it)
           result.push_back(input[i] + *it);   
   }
}
