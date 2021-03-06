// 利用stream buffer重定向cout(clog也可以)到文件
#include <iostream>     // std::streambuf, std::cout
#include <fstream>      // std::ofstream

int main () {
  std::streambuf *psbuf, *backup;
  std::ofstream filestr;
  filestr.open ("test.log");

  backup = std::cout.rdbuf();     // back up cout's streambuf

  psbuf = filestr.rdbuf();        // get file's streambuf
  std::cout.rdbuf(psbuf);         // assign streambuf to cout

  std::cout << "This is written to the file.";

  std::cout.rdbuf(backup);        // restore cout's original streambuf

  filestr.close();

  return 0;
}