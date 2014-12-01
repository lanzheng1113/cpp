# include <iostream>
# include <string>

int factr(int n);
int facti(int n);

int main(int argc,char ** argv)
{   
    if (argc != 3)
    {
      std::cout << "Usage: \t-i 5 //using iteration\n\t -r 5 //using recursion"<<std::endl;
      return 0;
    }
    int  n = std::stoi(argv[2]);
    if (std::string(argv[1]) == "-r" || std::string(argv[1]) == "-R")
    	std::cout << "Factorial of "<<n<<" : "<<factr(n)<<std::endl;
    else
    	std::cout << "Factorial of "<<n<<" : "<<facti(n)<<std::endl;
        
}

//using recursion
int factr(int n)
{
  if ( n ==0) return 1;
  return n*factr(n-1);
}

//using iteration
int facti(int n)
{
   int result = 1;
   for(int i = 1 ; i <= n;i++)
       result *= i;
   return result;
}
