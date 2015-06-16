#include <iostream>
#include <string>
using namespace std;

// Improperly declared function:  parameter should be const reference:
void print_me_bad( std::string& s ) {
  std::cout << s << std::endl;
}

// Properly declared function: function has no intent to modify s:
void print_me_good( const std::string& s ) {
  std::cout << s << std::endl;
}

int main() {

  std::string hello( "Hello" );

  print_me_bad( hello );  // Compiles ok; hello is not a temporary
  print_me_bad( std::string( "World" ) );  // Compile error; temporary object
  print_me_bad( "!" ); // Compile error; compiler wants to construct temporary
		       // std::string from const char*

  print_me_good( hello ); // Compiles ok
  print_me_good( std::string( "World" ) ); // Compiles ok
  print_me_good( "!" ); // Compiles ok
}
