#include <iostream>
#include <string>
#include "bubble.h"

int main( /*int argc , char * argv[]*/ ) {
  std::ifstream infile;
  infile.open("../nanoccapped.xyz");
  Bubble bubble;
  bubble.input(infile)
  //bubble.sort()
  buble.print(std::cout)
  return 0;
}
