#include <iostream>
#include <string>
#include "bubble.h"

int main( /*int argc , char * argv[]*/ ) {
  std::ifstream infile;
  infile.open("../nanoccapped.xyz");
  Bubble first;
  while ( first.input(infile) ) {}
  //bubble.sort()
  //buble.print(std::cout)
  return 0;
}
