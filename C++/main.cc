#include <iostream>
#include <string>
#include "bubble.h"

int main( ) {
  std::ofstream out_data_file;
  out_data_file.open("atom.bond.data");
  out_data_file << 
  "# This file will contain the organized data for the molecule" << std::endl <<
  "# with the indeces of the closes bonding atoms and the central" << std::endl <<
  "# atom to which they bond to. This is done with the assumption" << std::endl <<
  "# of how many atoms will bond together. This will probably" << std::endl << 
  "# change to make the program more general." << std::endl <<
  "# The file format is as follows" << std::endl <<
  "#              | Bond atom " << std::endl <<
  "# Central atom | Bond atom " << std::endl <<
  "#              | Bond atom " << std::endl;
  out_data_file.close();
  unsigned int atom = 0 , size;
  Bubble bubble;
  std::ifstream infile;
  infile.open("../nanoccapped.xyz");
  bubble.input(infile);
  infile.close();
  size = bubble.file_size()-1;
  while ( atom < size ) {
    bubble.sort(atom);
    atom++;
  }
  //bubble.print(std::cout);
  return 0;
}
